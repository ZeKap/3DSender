import socket
from enum import IntFlag
import ctypes as ct

class Keys(IntFlag):
    KEY_A = 2**0
    KEY_B = 2**1
    KEY_SELECT = 2**2
    KEY_START = 2**3
    KEY_DRIGHT = 2**4
    KEY_DLEFT = 2**5
    KEY_DUP = 2**6
    KEY_DDOWN = 2**7
    KEY_R = 2**8
    KEY_L = 2**9
    KEY_X = 2**10
    KEY_Y = 2**11
    KEY_ZL = 2**14
    KEY_ZR = 2**15
    KEY_TOUCH = 2**20
    KEY_CSTICK_RIGHT = 2**24
    KEY_CSTICK_LEFT = 2**25
    KEY_CSTICK_UP = 2**26
    KEY_CSTICK_DOWN = 2**27
    KEY_CPAD_RIGHT = 2**28
    KEY_CPAD_LEFT = 2**29
    KEY_CPAD_UP = 2**30
    KEY_CPAD_DOWN = 2**31

# https://gist.github.com/iTrooz/07200f67b3252015222e04044076596e
def binattrs(cls):
    cls._fields_ = tuple(cls.__annotations__.items())
    return cls

@binattrs
class CirclePosition(ct.LittleEndianStructure):
    _pack_ = 1
    dx: ct.c_int16
    dy: ct.c_int16

@binattrs
class AccelVector(ct.LittleEndianStructure):
    _pack_ = 1
    x: ct.c_int16
    y: ct.c_int16
    z: ct.c_int16

@binattrs
class AngularRate(ct.LittleEndianStructure):
    _pack_ = 1
    x: ct.c_int16
    y: ct.c_int16
    z: ct.c_int16

@binattrs
class InputData(ct.LittleEndianStructure):
    _pack_ = 1
    buttons: ct.c_uint32
    circlePad: CirclePosition
    accelerometer: AccelVector
    gyro: AngularRate

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('192.168.1.99', 8000)
print('connecting to 3DS on at {}:{}'.format(*server_address))
sock.connect(server_address)

try:
    # Receive data from the 3DS server
    while True:
        data = sock.recv(4+2*2+2*3+2*3, socket.MSG_WAITALL)
        if not data:
            break
        
        parsed_data = InputData.from_buffer_copy(data)
        keys = Keys(parsed_data.buttons)
        print("\033c", end="")
        print("circle pad: x=%s,y=%s" % (parsed_data.circlePad.dx, parsed_data.circlePad.dy))
        print("accel: x=%s,y=%s z=%s" % (parsed_data.accelerometer.x, parsed_data.accelerometer.y, parsed_data.accelerometer.z))
        print("gyro: x=%s,y=%s z=%s" % (parsed_data.gyro.x, parsed_data.gyro.y, parsed_data.gyro.z))
        for key in keys:
            print(key.name)
finally:
    print('closing socket')
    sock.close()
