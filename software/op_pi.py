
import time
from pythonosc import udp_client

import RPi.GPIO as GPIO
import OLED_Driver as OLED
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008
import wiringpi

from PIL  import Image, ImageDraw, ImageFont, ImageColor

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

        print("INPUT TEST MODE")
        self.input_loop()
    def input_loop(self):
        while True:
            input_recieved = self.check_queue()
            if(input_recieved):
                self.sm.refresh_screen()
                
    def start_input_thread(self):
        self.input_queue = Queue()
        im = InputManager()
        input_thread = Process(target=im.input_loop, args=(self.input_queue,), daemon=True)
        input_thread.start()
    def start_client(self):
        self.max_synths = 2
        self.active_synthn = 0

        #OSC client
        self.client = udp_client.SimpleUDPClient("127.0.0.1", 57120)

        #Synths array
        self.synths = [Synth(self.client,i) for i in range(self.max_synths)]
    def check_queue(self):
        action_recieved = False
        while(not self.input_queue.empty()):
            action_recieved = True
            action = self.input_queue.get()
            self.last_action = str(action[0]) + " | " + str(action[1])
            print("OP_Pi | Action recieved: {} {}".format(action[0],action[1]))
            if(action[0]==ACTION_VOLUME):
                self.volume = action[1]
            elif(action[0]==ACTION_KEYBOARD):
                self.synths[self.active_synthn].osc_note(action[1])
            elif(action[0]==ACTION_BUTTON):
                if(action[1]==4):
                    self.state = 0
                elif(action[1]==5):
                    self.state = 1
            else:
                print("OP_Pi ERROR unrecognized action")
        return action_recieved

OP_Pi()

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
