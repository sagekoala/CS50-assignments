from cs50 import get_string
import sys
import re
import math

''' Implement a program that determines whether a provided credit card number is valid according to Luhn's Algorithm:
    AE start 34 or 37, 15-digit number
    MC start with 51-55, 16-digit number
    Visa start with a 4, 13- or 16-digit number

    Luhn's Algorithm
    - Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    - Add the sum to the sum of the digits that weren’t multiplied by 2.
    - If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
'''

# Defining a dictionary to store cc number, cc type
dict = {
    "n": "000000000000000",
    "l": 0
}

# Defining some strings for the Redex
visa_string = "^4"
amex_string = "^[34,37]{2}"
mc_string = "^[5]{1}[1-5]{1}"

dict["n"] = get_string("Number: ")
dict["l"] = len(dict["n"])


def credit_type(dict):

    if (dict["l"]) == 13:
        v_matching(dict)

    elif (dict["l"]) == 15:
        amex_matching(dict)

    elif (dict["l"]) == 16:
        if dict["n"][0] == "4":
            v_matching(dict)
        else:
            master_matching(dict)
    else:
        print("INVALID")


def luhn(dict):

    digits = []
    # Multiply every other digit by 2, then add digits together starting w penultimate
    m, mod, floor, c_int = 0, 0, 0, 0
    for char in dict["n"][len(dict["n"]) - 2::-2]:
        c_int = (2 * int(char))
        if c_int >= 10:
            mod = ((c_int) % 10)
            floor = math.floor(c_int / 10)
            digits.append(str(mod))
            digits.append(str(floor))
        else:
            digits.append(str(c_int))

    # Looping through digits list and summing each digit to the variable m
    for i in range(len(digits)):
        m += int(digits[i])

    # Step 2: Add the sum of the digits that weren't multiplied by 2
    # Looping backwards through string at dict["n"] 2 steps at a time
    summ = 0
    for char in dict["n"][::-2]:
        summ += int(char)

    # Step 3, if %10 is 0, the number passes Luhn test
    if (m + summ) % 10 == 0:
        return True
    else:
        return False


def v_matching(dict):

    if (re.match(visa_string, dict["n"])):
        print("VISA")
    else:
        print("INVALID")


def amex_matching(dict):

    if (re.match(amex_string, dict["n"])):
        print("AMEX")
    else:
        print("INVALID")


def master_matching(dict):
    if (re.match(mc_string, dict["n"])):
        print("MASTERCARD")
    else:
        print("INVALID")


if luhn(dict):
    credit_type(dict)
else:
    print("INVALID")
