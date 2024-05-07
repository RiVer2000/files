import sys

if len(sys.argv) > 1:
    integer = int(sys.argv[1])  # Convert input to integer

    # Only send the integer back to C++ if it's divisible by 6
    if integer % 6 == 0:
        sys.stdout.write(str(integer) + "\n")
        sys.stdout.flush()
