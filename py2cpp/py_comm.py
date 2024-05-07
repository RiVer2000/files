import sys

if len(sys.argv) > 1:
    integer = int(sys.argv[1])  # Convert input to integer

    # Print the received integer
    print("Received integer:", integer)

    # Check if the integer is divisible by 6
    if integer % 6 == 0:
        # Send the integer back to cpp_comm.cpp using stdout
        sys.stdout.write(str(integer) + "\n")
        sys.stdout.flush()
