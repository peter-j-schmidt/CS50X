from cs50 import get_int

def main():
    height = get_height()
    print_pyramid(height)


def get_height():
    while True:
        n = get_int("Enter a number between 1 and 8\n")
        if (n >= 1 and n <= 8):
            break
    return n

def print_pyramid(n):

    for i in range(n):
        print(" " * (n - (i + 1)), end="")
        print("#" * (i + 1), end="")
        print("  ", end="")
        print("#" * (i + 1), end="\n")

main()