import serial

print "import successful"

usbport = '/dev/ttyACM0'
ser = serial.Serial(usbport, 9600);
line = ""
mesg = "0";

while True:
  data = ser.read()
  if(data == "\r"):
    print "Received from sensor:" + line
    line = ""
    ser.write(mesg)
    if(mesg == "0"):
      mesg = "1"
    else:
      mesg = "0"

  else:
    line = line + data

