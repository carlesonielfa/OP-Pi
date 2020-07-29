#MCP address 111b (27)
#Rotary 1. A - A7 H - A6 B - A5
#Rotary 2. A - B0 H - B1 B - B2
#Rotary 3. A - B3 H - B4 B - B5

import wiringpi
from time import sleep

class RotaryEncoder:
    def __init__(self, a_pin, b_pin, sw_pin):
        self.a_pin = a_pin
        self.b_pin = b_pin
        self.sw_pin = sw_pin

        wiringpi.pinMode(self.a_pin, wiringpi.INPUT)
        wiringpi.pinMode(self.b_pin, wiringpi.INPUT)
        wiringpi.pinMode(self.sw_pin, wiringpi.INPUT)
    
        wiringpi.pullUpDnControl(self.a_pin, wiringpi.PUD_UP)
        wiringpi.pullUpDnControl(self.b_pin, wiringpi.PUD_UP)
        wiringpi.pullUpDnControl(self.sw_pin, wiringpi.PUD_UP)

        self.a_last_value = 0

    def get_rotation(self):
        a_state = wiringpi.digitalRead(self.a_pin)
        b_state = wiringpi.digitalRead(self.b_pin)

        rotation = 0
        if self.a_last_value == 1 and a_state == 0:
            if b_state == 0:
                rotation = -1
            else:
                rotation = 1

        self.a_last_value = a_state
        return rotation

    def get_switch(self):
        return not wiringpi.digitalRead(self.sw_pin)


mcp23017_addr2 = 0x27

base = 65+16
wiringpi.wiringPiSetup()
wiringpi.mcp23017Setup(base,mcp23017_addr2)

switches = [base+6,base+9,base+12]
rotary1 = RotaryEncoder(base+7,base+6,base+5)
while(True):
    rotation = rotary1.get_rotation()
    if(rotation!=0):
        print(rotation)
    sleep(0.01)

