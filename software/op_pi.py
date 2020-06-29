from time import sleep
from pythonosc import udp_client
from multiprocessing import Process, Queue
from screen_manager import ScreenManager
from input_manager import InputManager, ACTION_BUTTON, ACTION_KEYBOARD, ACTION_VOLUME

class Effect:
    def __init__(self, track):
        self.enabled = False
        self.parameters = []
class Reverb(Effect):
    def __init__(self, track):
        super().__init__(track)
        self.parameters = [['W',45],['D',5], ['S',99]]
class Equalizer(Effect):
    def __init__(self, track):
        super().__init__(track)
        self.parameters = [['L',99],['M',99], ['L',50]]
class Distortion(Effect):
    def __init__(self, track):
        super().__init__(track)
        self.parameters = [['L',99],['M',99], ['L',50]]
class Track:
    def __init__(self, name):
        self.name = name
        self.inputs = []
        self.volume = 0.7
        self.effects = [Reverb(self), Equalizer(self),Distortion(self)]
        #Just to test display
        self.effects[0].enabled=True
        self.effects[2].enabled=True
    def empty(self):
        return len(self.inputs)==0
    
class Synth:
    def __init__(self, client, synthn):
        #Client for osc communication with supercollider
        self.client = client
        #current octave
        self.octave = 0
        self.synthn = synthn
        self.synth_address = '/'+str(synthn)
        self.preset = 'organ'
        #self.track = "NONE"

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

    def osc_note(self,input):
        note_number = 60+input+12*self.octave
        '''#Button wasn't pressed before then note on
        if(not note_state[input]):
            self.message("Note on: {}".format(input))
            self.client.send_message(self.synth_address+'/noteOn',note_number)
            note_state[input] = True
            time.sleep(0.2)
        #else note off
        else:
            self.message("Note off: {}".format(input))
            self.client.send_message(self.synth_address+'/noteOff',note_number)
            note_state[input] = False'''
        self.message("Note on: {}".format(note_number))
        self.client.send_message(self.synth_address+'/noteOn',note_number)
        sleep(0.5)
        self.client.send_message(self.synth_address+'/noteOff',note_number)
            
    def message(self, s):
        print("LOG | SYNTH {}: ".format(self.synthn)+s)


class OP_Pi:  
    #Main volume
    volume = 0
    #State of the device 0 - mixerview 1 - trackview
    state = 1
    last_action = ""
    bpm = 128

    def __init__(self):
        self.start_input_thread()
        self.sm = ScreenManager(self)
        self.start_client()
        track_letters = ('A','B','C','D','E','F','G','H','I')
        self.tracks = [Track(letter) for letter in track_letters]
        self.default_loop()
    def default_loop(self):
        while True:
            self.check_queue()
            self.sm.refresh_screen()


OP_Pi()

