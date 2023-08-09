from cs50 import get_int

# Implement a program that prints out a double half-pyramid of a specified height

# Setting up a do-while loop situation to force user input to be in range [1:8]
n = 0
while n not in range(1, 9):
    n = get_int("Height: ")

# Nested for loop, i for rows, j and k for columns
# Two spaces between the two half-pyramids
for i in range(n):
    for j in range(n):
        if j < (n - 1 - i):
            print(" ", end="")
        else:
            print("#", end="")

    print("  ", end="")

    for k in range(n):
        if k <= i:
            print("#", end="")
            
    print()

