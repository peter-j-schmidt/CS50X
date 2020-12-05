# import modules
import csv
from csv import reader
from csv import DictReader

from sys import argv, exit

import cs50

# write a loop that determines if correct command-line arguments were input

# if correct argument(csv) file was input:

# open csv file
# read file in 4 char chunks, looking for specific STR
# if target STR found, begin counting
# if target STR is repeated, update count
# else, count returns to zero, process restarted


def main():

    # check to see if correct number of args are given
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt.")
        exit(1)
    # print("Valid argument.")


    # for testing
    # print each argument and the index of the argument
    # for i in range(len(argv)):
        # print(argv[i])
        # print(i)

    # print(len(argv))


    # initialize a dictionary to store data from imported database
    db_dict = {}


    # open database csv in order to make dictionary
    with open(argv[1], 'r') as database_2:
        reader_2 = csv.reader(database_2)
        header = next(reader_2)

        # code to insert data into the database
        if header != None:
            for row in reader_2:
                db_dict[row[0]] = [int(item) for item in row[1:]]

        # for testing
        # print database
        # print(db_dict)

        # remove name variable from header
        header.remove('name')

        # for testing
        # print header
        # print(header)


    # dictionary to store STRs and their respective counts
    str_dict = {}
    # initialize dictionary with STRs as keys
    for item in header:
        str_dict[item] = {}



    # open dna string file
    sequence_file = open(argv[2])

    # read file into new variable
    dna_sequence = sequence_file.read()

    # for testing
    # print dna string
    # print(dna_sequence)

    # close files
    sequence_file.close()


    # function call to check for STRs in dna string
    check_sequence(dna_sequence, str_dict)

    # function call to find maximum values in the STR count dictionary
    find_max_values(str_dict)

    # initialize list to store max values from STR dictionary
    max_list = []
    for key in str_dict:
        max_list.append(str_dict[key])

        # for testing
        # print(str_dict[key])

    # for testing
    # print(max_list)

    answer = find_match(db_dict, max_list)

    print(answer)

    exit(0)



def check_sequence(string, dictionary):

    for key in dictionary:
        substring = key
        value = dictionary[key]
        # print(substring)
        # print(value)

        i = 0
        for i in range(len(string)):
            counter = 0
            result = compare(string, substring, i, counter)
            #print(result)
            value[i] = result
            i += 1

def compare(string, substring, index, counter):
    #print(string[index : index + (len(substring))])
    if string[index : index + (len(substring))] == substring:
        counter += 1
        #print(counter)
        index += len(substring)
        return compare(string, substring, index, counter)
    else:
        return counter


def find_max_values(dictionary):
    for key in dictionary:
        sub_dictionary = dictionary[key]
        max_value = max(sub_dictionary.values())
        dictionary[key] = max_value

def find_match(dictionary, list_item):
        # compare values of dictionary and list of max values
        # return the name of a match, if one exists
        for key in dictionary:
            if dictionary[key] == list_item:
                return key
            else:
                continue
        return "No match"


main()