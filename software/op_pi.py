import RPi.GPIO as GPIO
import time
from pythonosc import udp_client
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008
import wiringpi


class Synth:
    def __init__(self, client, synthn):
        #Client for osc communication with supercollider
        self.client = client
        #current octave
        self.octave = -1
        self.synthn = synthn
        self.synth_address = '/'+str(synthn)
        self.preset = 'organ'

    def osc_preset(self,new_preset):
        self.message("Preset from {} to {}".format(self.preset, new_preset))
        self.preset = new_preset
        self.client.send_message(self.synth_address+'/presetChange',new_preset)

    def osc_pitch(self,input, octave_range = 4):
        #From 0 - 1024 to -octave_range - octave_range
        corrected_input = ((input-512)/512.0)*octave_range
        self.client.send_message(self.synth_address+'/pitchBend',corrected_input)

    def osc_amp(self,input):
        #From 0-1024 to 0-1
        corrected_input = input/1024.0
        self.client.send_message(self.synth_address+'/ampChange', corrected_input)

    def osc_note(self,input, note_state):
        note_number = input+12*self.octave
        #Button wasn't pressed before then note on
        if(not note_state[input]):
            self.message("Note on: {}".format(input))
            self.client.send_message(self.synth_address+'/noteOn',note_number)
            note_state[input] = True
            time.sleep(0.2)
        #else note off
        else:
            self.message("Note off: {}".format(input))
            self.client.send_message(self.synth_address+'/noteOff',note_number)
            note_state[input] = False
            
    def message(self, s):
        print("LOG | SYNTH {}: ".format(self.synthn)+s)

class InputManager:
    #Manages inputs

    def __init__(self,op_pi):
        #Button pins for configuring interrupts
        self.button_pins = []

        self.gpio_setup()
        self.mcp23017_setup()

        #Actions for the buttons
        self.button_actions = [lambda i=i:self.default_action(i) for i in range(self.n_buttons)]
        self.button_actions[0] = [lambda : op_pi.play_note(60)]

        #Store the dial values for notifying changes
        self.n_dials = 4
        self.dial_values = [self.mcp.read_adc(i) for i in range(self.n_dials)]
        self.dial_actions = [lambda i=i: self.op_pi.dial_change(i,self.dial_values[i]) for i in range(self.n_dials)]

    def input_loop(self,op_pi):
        while True:
            self.check_buttons()
            self.check_dials()
            
            time.sleep(0.1)
    def check_dials(self):
        #If the value changed more than this, we notify it
        #TODO call actions in main thread
        noise_threshold = 2
        for i in range(self.n_dials):
            if(abs(self.dial_values[i]+noise_threshold - self.mcp.read_adc(i)) > noise_threshold):
                self.dial_values[i] = self.mcp.read_adc(i)
                try:
                    self.dial_actions[i]()
                except:
                    print("ERROR | INPUT MANAGER: Exception when calling dial {} function".format(i))
        

    def check_buttons(self):
        for i in range(self.n_buttons):
            #If the button is pressed, trigger action on main thread
            if(not wiringpi.digitalRead(i+pin_base)):
                try:
                    #TODO call actions in main thread
                    self.button_actions[i]()
                except:
                    print("ERROR | INPUT MANAGER: Exception when calling button {} function".format(i))
    def mcp23017_setup(self):
        #MCP23017 setup
        self.pin_base = 65
        mcp23017_addr = [0x20,0x21]
        self.n_buttons = len(mcp23017_addr)*18

        wiringpi.wiringPiSetup()
        #Setup all mcp23017
        for i,addr in enumerate(mcp23017_addr):
            wiringpi.mcp23017Setup(self.pin_base+18*i,addr)

        #Setup all pins as input with pull up
        for i in  range(self.pin_base, self.pin_base+self.n_buttons):
            wiringpi.pinMode(i, wiringpi.INPUT)
            wiringpi.pullUpDnControl(i, wiringpi.PUD_UP)

    def gpio_setup(self):
        #GPIO setup
        GPIO.setmode(GPIO.BOARD)
        # Hardware SPI configuration for dials:
        SPI_PORT   = 0
        SPI_DEVICE = 0
        self.mcp = Adafruit_MCP3008.MCP3008(spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))
        #Setup keyboard buttons pins and interrupts
        for i,pin in enumerate(self.button_pins):
            GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    def default_action(self,i):
        print("LOG | INPUT MANAGER: Button action not defined for button {}".format(i))


class OP_Pi:

    def __init__(self):
        #General parameters
        self.max_synths = 2
        self.active_synthn = 0

        #OSC client
        self.client = udp_client.SimpleUDPClient("127.0.0.1", 57120)

        #Synths array
        self.synths = [Synth(self.client,i) for i in range(self.max_synths)]

        #Input Manager
        self.input_manager = InputManager(self)
        #TODO: Start input loop in another thread

        #Indicates if note is on or off
        self.note_state = {i+60:False for i in range(self.input_manager.n_buttons)}     

        self.main_loop()
    def play_note(self, note_number):
        self.active_synth().osc_note(i+note_number, self.note_state)
    def active_synth(self):
        return self.synths[self.active_synthn]
    def dial_change(self,i,value):
        pass
    def main_loop(self):
        pass
        

op_pi = OP_Pi()
