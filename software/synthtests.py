from pythonosc import udp_client


client = udp_client.SimpleUDPClient("127.0.0.1", 57120)

pressed = False
while(True):
    s = input("INPUT: ")
    if(s=="q"):
        break
    if(s=="a" and not pressed):
        client.send_message('/0/noteOn',60)
        pressed = True
    elif(s=="a" and pressed):
        client.send_message('/0/noteOff',60)
        pressed = False
