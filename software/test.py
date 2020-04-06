# Turns on each pin of an mcp23017 on address 0x20 ( quick2wire IO expander )
import wiringpi
import time

pin_base = 65
mcp23017_addr1 = 0x20

wiringpi.wiringPiSetup()
wiringpi.mcp23017Setup(pin_base,mcp23017_addr1)

for i in range(16):
    wiringpi.pinMode(pin_base, wiringpi.INPUT)
    wiringpi.pullUpDnControl(pin_base, wiringpi.PUD_UP)



print("Pin setup done")
while True:
    for i in range(16):
        if(not wiringpi.digitalRead(i+pin_base)):
            print("Button {} Pressed".format(i))
    time.sleep(0.2)
    