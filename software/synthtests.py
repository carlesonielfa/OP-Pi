from pythonosc import udp_client
from time import sleep

client = udp_client.SimpleUDPClient("127.0.0.1", 57120)


while(True):
    s = input("INPUT: ")
    if(s=="q"):
        break
    if(s=="a"):
        client.send_message('/0/noteOn',60)
        sleep(0.2)
        client.send_message('/0/noteOff',60)
    if(s=="s"):
        client.send_message('/1/noteOn',60)
        sleep(0.2)
        client.send_message('/1/noteOff',60)

