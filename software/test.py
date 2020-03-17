
from psonic import *
from pynput.keyboard import Key, Listener, KeyCode
from sonic_pi_tool import Server

server = Server('127.0.0.1',4557,4559)

def on_press(key):
    letters = ['a','s','d','f','g','h','j']
    print('{0} pressed'.format(key))
    key_char = str(key)[1:-1]
    if(key_char in letters):
        #play(60+letters.index(str(key)[1:-1]))
        server.run_code("play("+str(48+letters.index(str(key)[1:-1]))+")")
    
def on_release(key):
    if key == Key.esc:
        # Stop listener
        return False

# Collect events until released
with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()