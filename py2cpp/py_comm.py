import sys

# def receive_integer():
# Read the integer from stdin
integer = sys.argv[1]

# Print the received integer
print("Received integer:", integer)

# Check if the integer is divisible by 6
if integer % 6 == 0:
    # Send the integer back to cpp_comm.cpp using stdout
    sys.stdout.write(str(integer) + "\n")
    sys.stdout.flush()

# Call the receive_integer function
# receive_integer()