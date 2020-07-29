import math
import threading
import time
import wiringpi
class RotaryEncoder:
    def __init__(self, a_pin, b_pin, callback=None):
        self.a_pin = a_pin
        self.b_pin = b_pin

        wiringpi.pinMode(self.a_pin, wiringpi.INPUT)
        wiringpi.pinMode(self.b_pin, wiringpi.INPUT)
        
        wiringpi.pullUpDnControl(self.a_pin, wiringpi.PUD_UP)
        wiringpi.pullUpDnControl(self.b_pin, wiringpi.PUD_UP)

        self.steps = 0
        self.last_delta = 0
        self.r_seq = self.rotation_sequence()

        # steps_per_cycle and self.remainder are only used in get_cycles which
        # returns a coarse-granularity step count.  By default
        # steps_per_cycle is 4 as there are 4 steps per
        # detent on my encoder, and get_cycles() will return a signed
        # count of full detent steps.
        self.steps_per_cycle = 4
        self.remainder = 0

    def rotation_sequence(self):
        a_state = wiringpi.digitalRead(self.a_pin)
        b_state = wiringpi.digitalRead(self.b_pin)
        r_seq = (a_state ^ b_state) | b_state << 1
        return r_seq

    def update(self):
        delta = 0
        r_seq = self.rotation_sequence()
        if r_seq != self.r_seq:
            delta = (r_seq - self.r_seq) % 4
            if delta == 3:
                delta = -1
            elif delta == 2:
                delta = int(math.copysign(delta, self.last_delta))  # same direction as previous, 2 steps

            self.last_delta = delta
            self.r_seq = r_seq
        self.steps += delta
        if(self.callback is not None):
            cycles = self.get_cycles()
            if(cycles != 0):
                self.callback(cycles)
            

    def get_steps(self):
        steps = self.steps
        self.steps = 0
        return steps

    # get_cycles returns a scaled down step count to match (for example)
    # the detents on an encoder switch.  If you have 4 delta steps between
    # each detent, and you want to count only full detent steps, use
    # get_cycles() instead of get_delta().  It returns -1, 0 or 1.  If
    # you have 2 steps per detent, set encoder.steps_per_cycle to 2
    # before you call this method.
    def get_cycles(self):
        # python negative integers do not behave like they do in C.
        #   -1 // 2 = -1 (not 0)
        #   -1 % 2 =  1 (not -1)
        # // is integer division operator.  Note the behaviour of the / operator
        # when used on integers changed between python 2 and 3.
        # See http://www.python.org/dev/peps/pep-0238/
        self.remainder += self.get_steps()
        cycles = self.remainder // self.steps_per_cycle
        self.remainder %= self.steps_per_cycle # remainder always remains positive
        return cycles