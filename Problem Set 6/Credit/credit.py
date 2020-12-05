# use dictionaries to determine credit card brand

# card types:
# Amex = 34 or 37
# Visa = starts with a 4
# Mastercard = 51, 52, 53, 54, 55
# INVALID = does not pass check sum

# Luhs Algorithm

# Multiply every other number, starting with second-to-last digit, by 2. Then add those digits together.
# Add that sum to the sum of the digits NOT multiplied by 2
# If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid

from cs50 import get_int
from cs50 import get_string

amex = ["34", "37"]
mastercard = ["51", "52", "53", "54", "55"]
visa = ["4"]


def main():
    card = get_card()
    if card == 0:
        print("INVALID")
    else:
        # check_validity(card)
        brand = get_card_type(card)
        print(brand)


def get_card():
    n = get_string("Number: ")
    if len(n) >= 13 and len(n) <= 16:
        return n
    else:
        return 0


def get_card_type(string):
    card_id = string[0] + string[1]
    if card_id[0] in visa:
        return "VISA"
    elif card_id in amex:
        return "AMEX"
    elif card_id in mastercard:
        return "MASTERCARD"

# This function is an implementation of Luhn's Algorithm.
# However, this doesn't seem to matter in this problem set


def check_validity(string):
    luhns_sum = 0
    other_sum = 0
    new_string = [i for i in string[::-1]]
    for i in new_string:
        print(i)
    for j in new_string[1::2]:
        print(j)
        luhns_sum += 2 * int(j)
        print(luhns_sum)
    for k in new_string[::2]:
        print(k)
        other_sum += int(k)
        print(other_sum)
    total = luhns_sum + other_sum
    result = total % 10
    if result == 0:
        return "VALID"
    else:
        return "INVALID"


main()