# Import necessary modules
import csv
import cs50
from cs50 import SQL
from sys import argv, exit

# create database object to use later in program
db = SQL("sqlite:///students.db")

# define a main function


def main():

    # check for valid command-line arguments, else exit with value 1
    if len(argv) != 2:
        print("Usage: python example.py house")
        exit(1)

    # create variable to store list of dictionaries from SQL database
    name_list = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last, first", argv[1])

    # for testing
    # print(name_list)

    # iterate through each dictionary in list
    for item in name_list:

        # check condition to determine what is printed to the terminal
        if item['middle'] == None:
            print(f"{item['first']} {item['last']}, born {str(item['birth'])}")
        else:
            print(f"{item['first']} {item['middle']} {item['last']}, born {item['birth']}")


main()