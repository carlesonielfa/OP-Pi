# Class to monitor a rotary encoder and update a value.  You can either read the value when you need it, by calling getValue(), or
# you can configure a callback which will be called whenever the value changes.

import RPi.GPIO as GPIO

class Encoder:

    def __init__(self, leftPin, rightPin, callback=None):
        self.leftPin = leftPin
        self.rightPin = rightPin
        self.value = 0
        self.state = 0
        self.direction = None
        self.callback = callback
        GPIO.setup(self.leftPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.setup(self.rightPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.add_event_detect(self.leftPin, GPIO.BOTH, callback=self.transitionOccurred)  
        GPIO.add_event_detect(self.rightPin, GPIO.BOTH, callback=self.transitionOccurred)  

    def transitionOccurred(self, channel):
        p1 = GPIO.input(self.leftPin)
        p2 = GPIO.input(self.rightPin)
        newState = 2*p1 + p2

        if self.state == 0: # Resting position
            if newState == 1: # Turned right 1
                self.direction = "R"
            elif newState == 2: # Turned left 1
                self.direction = "L"

        elif self.state == 1: # R1 or L3 position
            if newState == 3: # Turned right 1
                self.direction = "R"
            elif newState == 0: # Turned left 1
                if self.direction == "L":
                    self.value = self.value - 1
                    if self.callback is not None:
                        self.callback(self.value)

        elif self.state == 1: # R3 or L1
            if newState == 3: # Turned left 1
                self.direction = "L"
            elif newState == 0: # Turned right 1
                if self.direction == "R":
                    self.value = self.value + 1
                    if self.callback is not None:
                        self.callback(self.value)

        else: # self.state == "11"
            if newState == 1: # Turned left 1
                self.direction = "L"
            elif newState == 2: # Turned right 1
                self.direction = "R"
            elif newState == 0: # Skipped an intermediate 01 or 10 state, but if we know direction then a turn is complete
                if self.direction == "L":
                    self.value = self.value - 1
                    if self.callback is not None:
                        self.callback(self.value)
                elif self.direction == "R":
                    self.value = self.value + 1
                    if self.callback is not None:
                        self.callback(self.value)
                
        self.state = newState

    def getValue(self):
        return self.value

if __name__ == "__main__":
    import time
    import RPi.GPIO as GPIO

    def valueChanged(value):
        print("* New value: {}".format(value))

    GPIO.setmode(GPIO.BCM)

    #e1 = Encoder(19, 6, valueChanged)
    e1 = Encoder(4, 27, valueChanged)

    try:
        while True:
            time.sleep(5)
            print("Value is {}".format(e1.getValue()))
    except Exception:
        pass
    GPIO.cleanup()