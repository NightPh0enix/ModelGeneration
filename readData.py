import serial
import time
import subprocess

LINUX = 1

output = subprocess.check_output("python -m serial.tools.list_ports", shell=True) # sending command to terminal 
output = output.decode('utf-8') # the output is of type b'somestring' This removes that
output = output.splitlines() # so we can access the COM part

if LINUX :
    temp = output[0].split()
    port = temp[0]
else:
    port =  output[0]
   
data = open("Input.txt", "w")

ser = serial.Serial(port, 115200, timeout=30)
print("Serial Port opened on : " + ser.name)

ser.write(b'M564 S0 H0\r\n')
time.sleep (0.02)
ser.write(b'M111 S1 P6\r\n')
time.sleep (0.02)
ser.write(b'M111 S1 P4\r\n')

counter = 0
while (1):
    response = ser.readline().decode('utf-8')
    print(response)
    data.write(response)
    if response == "":
        break

time.sleep(1)
data.close()
