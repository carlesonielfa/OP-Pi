
functions = []
for i in range(5):
    
    #GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    functions.append( lambda : print(i))

for i in range(5):
    #GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    functions[i]()