from time import sleep
from pythonosc import udp_client
#import threading
from multiprocessing import Process, Queue
import RPi.GPIO as GPIO
import OLED_Driver as OLED
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008
import wiringpi

from PIL  import Image, ImageDraw, ImageFont, ImageColor
class InputManager:

    def __init__(self):
        self.init_keys()
        self.init_pot()
        #Poll 100 times a second
        self.poll_frequency = 100

    def init_keys(self):
        self.pin_base = 65
        self.pins_order = {0:0,2:1,3:2,1:3,5:4,4:5}
        self.cols = range(7+self.pin_base,7-5+self.pin_base,-1)
        self.rows = range(8+self.pin_base,8+6+self.pin_base)
        mcp23017_addr1 = 0x20

        wiringpi.wiringPiSetup()
        wiringpi.mcp23017Setup(self.pin_base,mcp23017_addr1)

        for i in self.cols:
            wiringpi.pinMode(i, wiringpi.OUTPUT)
            wiringpi.digitalWrite(i, 1)

        for i in self.rows:
            wiringpi.pinMode(i, wiringpi.INPUT)
            wiringpi.pullUpDnControl(i, wiringpi.PUD_UP)
        print("Keys setup done")

    def init_pot(self):
        # Hardware SPI configuration:
        SPI_PORT   = 0
        SPI_DEVICE = 1
        self.mcp = Adafruit_MCP3008.MCP3008(spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))
        self.previous_pot_value = 0
    def input_loop(self, queue):
        while(True):
            self.check_keys(queue)
            self.check_potentiometer(queue)
            sleep(1/self.poll_frequency)
    def check_keys(self, queue):
        for col in self.cols:
            wiringpi.digitalWrite(col, 0)
            for row in self.rows:
                if(not wiringpi.digitalRead(row)):
                    r = self.pins_order[row-self.pin_base-8]
                    c = col-self.pin_base-7+4
                    #print("Button pressed: {}".format(r+6*c))
                    button_n = r+6*c
                    if(button_n <= 19 and button_n >= 6):
                        queue.put([KEYBOARD_PRESS, button_n-6])
                    else:
                        queue.put([BUTTON_PRESS, button_n])
                    while(not wiringpi.digitalRead(row)):
                        pass
            wiringpi.digitalWrite(col, 1)

    def check_potentiometer(self, queue):
        pot_value = self.mcp.read_adc(7)
        if(abs(pot_value-self.previous_pot_value)>5):
            self.previous_pot_value = pot_value
            pot_value = round(pot_value/1023*100) 
            #JUST TO TEST
            queue.put((VOLUME_CHANGE, pot_value))

class ScreenManager:
    def __init__(self, op_pi):
        self.op_pi=op_pi
        OLED.Device_Init()
        self.test_text()
        self.refresh_rate = 60
    def refresh_screen(self):
        self.test_text()
    def test_text(self):
        image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
        draw = ImageDraw.Draw(image)
        font = ImageFont.truetype('fonts/ChakraPetch-Regular.ttf',18)

        draw.text((0, 0), 'Volume: {}'.format(self.op_pi.volume), fill = "BLUE", font = font)
        OLED.Display_Image(image)


#Actions
VOLUME_CHANGE = 0
KEYBOARD_PRESS = 1
BUTTON_PRESS = 2
DIAL_CHANGE = 3

class OP_Pi:
    #Main volume
    volume = 0
    #State of the device 0 - main menu
    state = 0
    def __init__(self):
        self.start_InputThread()
        self.sm = ScreenManager(self)
        self.default_loop()
    def default_loop(self):
        while True:
            self.check_queue()
            self.sm.refresh_screen()
    def start_InputThread(self):
        self.input_queue = Queue()
        im = InputManager()
        input_thread = Process(target=im.input_loop, args=(self.input_queue,), daemon=True)
        input_thread.start()
    def check_queue(self):
        while(not self.input_queue.empty()):
            action = self.input_queue.get()
            print("OP_Pi | Action recieved: {} {}".format(action[0],action[1]))
            if(action[0]==VOLUME_CHANGE):
                self.volume = action[1]
            elif(action[0]==KEYBOARD_PRESS):
                pass
            elif(action[0]==BUTTON_PRESS):
                pass
            else:
                print("OP_Pi ERROR unrecognized action")

OP_Pi()

