#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


const char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, string argv[])
{
    if (argc != 2) //Checks for a command-line input from user
    {
        printf("Usage: ./ceasar key\n");
        return (1);
    }
    else if (argc == 2)
    {
        // Check key for validity

        const int key = atoi(argv[1]); // converts string into an integer

        int key_length = strlen(argv[1]); //stores the length of the key input

        bool valid_key = true; // Boolean value used to check validity

        for (int i = 0; i < key_length; i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                valid_key = false;
                printf("Usage: ./caesar key\n");
                i = key_length;
                return 1;
            }
        }
        if (valid_key)
        {
            string input = get_string("plaintext: ");

            int input_length = strlen(input);

            for (int i = 0; i < input_length; i++) // iterates through each item in the string
            {
               if (isupper(input[i])) // checks whether the input at i is an upper case letter
               // checks for length of key and, if it is longer that the length of the alphabet, converts it to a usable key length
                {
                    if (input[i] + key > 'Z')
                    {
                        int remainder = input[i] + key - 'Z';
                        if (remainder > 'Z' - 'A')
                        {
                            while (remainder >= 'Z' - 'A')
                            {
                                remainder = remainder - (26); //converts key length to a usable length
                            }
                            if (input[i] + remainder > 'Z')
                            {
                                remainder = input[i] + key - 'Z';

                                input[i] = 'A' + remainder - 1; //encrypts the string item at i
                            }
                            else
                            {
                                input[i] = 'A' + remainder - 1;
                            }
                        }
                        else
                        {
                            input[i] = 'A' + remainder - 1;
                        }
                    }
                    else if (input[i] + key <= 'Z') // if the length of the key is usable, encrypts the user input at i
                    {
                        input[i] = input[i] + key;
                    }
                }
                if (islower(input[i])) // checks if the input at i is a lower case letter
                {
                    if (input[i] + key > 'z')
                    {
                        int remainder = input[i] + key - 'z';
                        if (remainder > 'z' - 'a')
                        {
                            while (remainder >= 'z' - 'a')
                            {
                                remainder = remainder - (26);
                            }
                            if (input[i] + remainder > 'z')
                            {
                                remainder = remainder - 'z';
                                input[i] = 'a' + remainder - 1;
                            }
                            else
                            {
                                input[i] = 'a' + remainder - 1;
                            }
                        }
                        else
                        {
                            input[i] = 'a' + remainder - 1;
                        }
                    }
                    else if (input[i] + key <= 'z')
                    {
                        input[i] = input[i] + key;
                    }
                }
            }
            printf("ciphertext: %s\n", input);
            // prints the ciphertext after iterating through the user imput and encrypting the string, with a new line afterwards
        }
    }
}