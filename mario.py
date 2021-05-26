from cs50 import get_int

height = 0
# makes sure the input is valid
while (height < 1 or height > 8):
    height = get_int("What size should the pyramid be? ")

for i in range(height):
    # prints the first half of the line
    for h in range(height - i - 1):
        print(" ", end="")
    
    for k in range(i + 1):
        print("#", end="")
    
    # prints the gap
    print("  ", end="")
    
    # prints the second half of the line
    for j in range(i + 1):
        print("#", end="")
    print()
