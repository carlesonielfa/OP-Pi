from time import sleep
from pythonosc import udp_client
import threading

import RPi.GPIO as GPIO
import OLED_Driver as OLED
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008
import wiringpi

from PIL  import Image, ImageDraw, ImageFont, ImageColor
class InputManager:

    def __init__(self,op_pi):
        self.op_pi = op_pi
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

    def input_loop(self):
        while(True):
            self.check_keys()
            self.check_potentiometer()
            sleep(1/self.poll_frequency)
    def check_keys(self):
        for col in self.cols:
            wiringpi.digitalWrite(col, 0)
            for row in self.rows:
                if(not wiringpi.digitalRead(row)):
                    print("Button pressed: {} {}".format(self.pins_order[row-self.pin_base-8], col-self.pin_base-7+4))
                    while(not wiringpi.digitalRead(row)):
                        pass
            wiringpi.digitalWrite(col, 1)

    def check_potentiometer(self):
        pot_value = round(self.mcp.read_adc(7)/1023*100) 
        #JUST TO TEST
        self.op_pi.volume = pot_value
        return pot_value

class ScreenManager:
    def __init__(self,op_pi):
        self.op_pi = op_pi
        OLED.Device_Init()
        self.test_text()
        self.refresh_rate = 60
    def screen_loop(self):
        while(True):
            self.test_text()
            sleep(1/self.refresh_rate)
    def test_text(self):
        image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
        draw = ImageDraw.Draw(image)
        font = ImageFont.truetype('fonts/ChakraPetch-Regular.ttf',18)

        draw.text((0, 0), 'Volume: {}'.format(self.op_pi.volume), fill = "BLUE", font = font)
        OLED.Display_Image(image)

class OP_Pi:
    #Main volume
    volume = 0
    #State of the device 0 - main menu
    state = 0
    def __init__(self):
        self.start_InputThread()
        self.start_ScreenThread()
        self.default_loop()
    def default_loop(self):
        while(True):
            sleep(1)
            pass
    def start_InputThread(self):
        im = InputManager(self)
        input_thread = threading.Thread(target=im.input_loop, args=(), daemon=True)
        input_thread.start()
    def start_ScreenThread(self):
        sm = ScreenManager(self)
        screen_thread = threading.Thread(target=sm.screen_loop, args=(), daemon=True)
        screen_thread.start()

OP_Pi()

