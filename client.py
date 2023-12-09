import socket
from enum import IntFlag

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

# keys = Keys(3)
# print("\033c", end="")
# for key in keys:
#     print(key.name)
# exit(0)

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('192.168.1.99', 8000)
print('connecting to 3DS on at {}:{}'.format(*server_address))
sock.connect(server_address)

try:
    # Receive data from the 3DS server
    while True:
        data = sock.recv(4)
        if not data:
            break
        int_data = int.from_bytes(data, byteorder='little', signed=False)
        keys = Keys(int_data)
        print("\033c", end="")
        print(keys)
        for key in keys:
            print(key.name)
finally:
    print('closing socket')
    sock.close()
