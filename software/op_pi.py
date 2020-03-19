import RPi.GPIO as GPIO
import time
from pythonosc import udp_client
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008


class Synth:
    def __init__(self, client, synthn):
        #Client for osc communication with supercollider
        self.client = client
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
        #Button wasn't pressed before then note on
        if(not note_state[input]):
            self.message("Note on: {}".format(input))
            self.client.send_message(self.synth_address+'/noteOn',input)
            note_state[input] = True
            time.sleep(0.2)
        #else note off
        else:
            self.message("Note off: {}".format(input))
            self.client.send_message(self.synth_address+'/noteOff',input)
            note_state[input] = False
    def message(self, s):
        print("LOG | SYNTH {}: ".format(self.synthn)+s)

class OP_Pi:

    def __init__(self):
        #General parameters
        self.max_synths = 2
        self.active_synthn = 0

        #OSC client
        self.client = udp_client.SimpleUDPClient("127.0.0.1", 57120)

        #Synths array
        self.synths = [Synth(self.client,i) for i in range(self.max_synths)]

        #Aux button
        self.aux_pin = 29
        #Keyboard buttons pins in order starting from C4 (60)
        button_pins = [37,35,33,31]
        #Indicates if note is on or off
        self.note_state = {i+60:False for i in range(len(button_pins))}

        self.gpio_setup(button_pins)
    def active_synth(self):
        return self.synths[self.active_synthn]
    def gpio_setup(self, button_pins):
        #GPIO setup
        GPIO.setmode(GPIO.BOARD)
        # Hardware SPI configuration for dials:
        SPI_PORT   = 0
        SPI_DEVICE = 0
        mcp = Adafruit_MCP3008.MCP3008(spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))
        #Setup keyboard buttons pins and interrupts
        for i,pin in enumerate(button_pins):
            GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
            GPIO.add_event_detect(pin, GPIO.BOTH, callback = lambda pin,i=i: self.active_synth().osc_note(i+60, self.note_state))

        #Aux button for testing
        GPIO.setup(self.aux_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.add_event_detect(self.aux_pin, GPIO.RISING, callback = lambda pin: self.active_synth().osc_preset('prophet'))


op_pi = OP_Pi()
while True:
    #Dial 1 amplitude
    #synths[active_synth].osc_amp(mcp.read_adc(0))
    #Dial 2 pitch
    #synths[active_synth].osc_pitch(mcp.read_adc(3))
    time.sleep(0.1)