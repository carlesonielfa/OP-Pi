import RPi.GPIO as GPIO
import time
from pythonosc import udp_client
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008


button_pins = [37,35,33,31,29,15]
note_state = {i+60:False for i in range(len(button_pins))}

def osc_pitch(client, input, synth_n = 0, octave_range = 4):
    client.send_message('/pitchBend',((input-512)/512.0)*octave_range)
def osc_amp(client, input, synth_n = 0):
    client.send_message('/ampChange',input/1024.0)
def osc_note(client, input, synth_n=0):
    #Button wasn't pressed before
    if(not note_state[input]):
        print("Note on: {}".format(input))
        client.send_message('/noteOn',input)
        note_state[input] = True
        time.sleep(0.2)
    #Falling edge
    else:
        print("Note off: {}".format(input))
        client.send_message('/noteOff',input)
        note_state[input] = False

# Hardware SPI configuration:
SPI_PORT   = 0
SPI_DEVICE = 0
mcp = Adafruit_MCP3008.MCP3008(spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))

client = udp_client.SimpleUDPClient("127.0.0.1", 57120)
#pin list, first is notenumber 60


GPIO.setmode(GPIO.BOARD)
for i,pin in enumerate(button_pins):
    GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.add_event_detect(pin, GPIO.BOTH, callback = lambda f : osc_note(client, i+60))

while True:
    #Dial 1 amplitude
    osc_amp(client,mcp.read_adc(0))
    #Dial 2 pitch
    osc_pitch(client,mcp.read_adc(3))
    #Keyboard buttons
    '''for i,pin in enumerate(button_pins):
        button_state = GPIO.input(pin)
        if button_state == False:
            print ("Button {} pressed - Note {}".format(pin,i+60))
            osc_note(client,i+60)'''
    time.sleep(0.1)

