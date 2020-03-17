from pynput.keyboard import Key, Listener, KeyCode
from pythonosc import udp_client


client = udp_client.SimpleUDPClient("127.0.0.1", 57120)
letters =  ['a','s','d','f','g','h','j']
letters_dict = {i:False for i in letters}

def on_press(key):
    key_char = str(key)[1:-1]
    if(key_char in letters and not letters_dict[key_char]):
        letters_dict[key_char] = True
        print('{0} on'.format(key))
        note = 60+letters.index(key_char)
        client.send_message('/noteOn',note)
        
    
def on_release(key):
    if key == Key.esc:
        # Stop listener
        return False
    
    print('{0} off'.format(key))
    key_char = str(key)[1:-1]
    if(key_char in letters):
        note = 60+letters.index(key_char)
        client.send_message('/noteOff',note)
        letters_dict[key_char] = False
    

# Collect events until released
with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()