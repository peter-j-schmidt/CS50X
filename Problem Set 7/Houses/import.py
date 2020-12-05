# Import necessary modules

import csv
import cs50
from cs50 import SQL
from csv import reader

from sys import argv, exit

# create db object for use further in program.
db = SQL("sqlite:///students.db")


# define main function
def main():

    # checks for correct number of command-line arguments.
    if len(argv) != 2:
        print("Usage: python import.py example.csv")
        exit(1)

    # for testing
    # print(argv[1])

    # open csv file from command line as DictReader object
    with open(argv[1], 'r') as student_db:
        student_reader = csv.DictReader(student_db, delimiter=",")

        # iterate over each dictionary in DictReader object
        for row in student_reader:

            # for testing
            # print(counter)
            # counter += 1

            # for testing
            # print(row['name'])
            # print(row['house'])
            # print(row["birth"])

            # variable to store the name value
            txt = row['name']

            # split name value by ' ' character
            name_list = txt.split()

            # for testing
            # print(name_list)
            # print(len(name_list))

            # condition to determine what to insert into students.db
            if len(name_list) == 3:
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                           name_list[0], name_list[1], name_list[2], row['house'], row['birth'])
            elif len(name_list) == 2:
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                           name_list[0], None, name_list[1], row['house'], row['birth'])


main()