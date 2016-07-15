import serial

def reading_serial():
    s=serial.Serial(port="/dev/ttyAMA0",baudrate=9600,timeout=0.0009)
    l=s.readline();
    if l=="":
        return [0,0,0,0]
    else:
        line=l.split(';')
        x=float(line[0])
        y=float(line[1])
        z=float(line[2])-1
        yaw=float(line[3])
        return [x,y,z,yaw]
