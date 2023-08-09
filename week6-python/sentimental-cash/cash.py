from cs50 import get_float
import math

''' Write a program that first asks the user how much change is owed, then displays
the minimum number of coins with which said change can be made '''

# Declaring a dictionary to track the remainder and the number of coins
dict = {
    "r": 0,
    "c": 0
}

# Getting a positive value input from user
owed = 0
while owed <= 0:
    owed = get_float("Change owed: ")

# Converting user-input float into whole number int and storing value in dict
dict["r"] = int(owed * 100)

# Functions


def coins(dict):

    quarters(dict)
    dimes(dict)
    nickels(dict)
    pennies(dict)
    coins = dict["c"]
    return int(coins)


def quarters(dict):
    c = 0
    if dict["r"] == 0:
        return dict
    elif dict["r"] >= 25:
        c = (math.floor(dict["r"] / 25))
        dict["c"] += c
        dict["r"] -= c * 25
        return dict
    else:
        return dict


def dimes(dict):
    c = 0
    if dict["r"] == 0:
        return dict
    elif dict["r"] >= 10:
        c = (math.floor(dict["r"] / 10))
        dict["c"] += c
        dict["r"] -= c * 10
        return dict
    else:
        return dict


def nickels(dict):
    c = 0
    if dict["r"] == 0:
        return dict
    elif dict["r"] >= 5:
        c = (math.floor(dict["r"] / 5))
        dict["c"] += c
        dict["r"] -= c * 5
        return dict
    else:
        return dict


def pennies(dict):
    if dict["r"] == 0:
        return dict
    elif dict["r"] >= 1:
        dict["c"] += dict["r"]
        dict["r"] = 0
        return dict
    else:
        return dict


amount = coins(dict)
print(amount)