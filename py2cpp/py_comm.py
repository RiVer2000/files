# py_comm.py

import sys

number = int(sys.argv[1])
print("Listening", number)

if number % 42 == 0:
    print("bup bup", number)
