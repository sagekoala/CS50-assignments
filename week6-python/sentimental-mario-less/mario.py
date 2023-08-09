from cs50 import get_int

# Implement a program that prints out a half-pyramid of a specified height

n = 0
# Collect user input
while n not in range(1, 9):
    n = get_int("Height: ")

# Nested for loop i for rows, j for columns
for i in range(n):
    for j in range(n):
        if j < (n - 1 - i):
            print(" ", end="")
        else:
            print("#", end="")
    print()
