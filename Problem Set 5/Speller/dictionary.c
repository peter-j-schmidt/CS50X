// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// initialize value to count # of words in dictionary
int counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    // initialize int to use as index
    int hash_index = hash(word);

    //set equal to indexed linked list
    node* cursor = table[hash_index];

    while(cursor != NULL)
    {
        // compare the two words.
        if((strcasecmp(cursor->word, word)) == 0)
        {
            // set cursor to NULL before freeing memory
            cursor = NULL;
            free(cursor);
            return true;
        }


        // move cursor down list if not the correct word
        cursor = cursor->next;

    }

    //free remaining memory
    free(cursor);

    return false;
}


// This is the djb2 hash function by dan bernstein from cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    char *copy = malloc((LENGTH+1) * (sizeof(char)));

    strcpy(copy, word);

    char *lower = copy;

    for (int i = 0; i < strlen(copy); i++)
    {
        lower[i] = tolower(copy[i]);
    }

    unsigned long hash = 5381;
    int c;

    while ((c = *lower++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    free(copy);
    return hash % N;
}


// The code for this hash function is based on an online discussion.
// I haven't been able to find an author for this function
//If someone has already written this (I'm sure someone has), I will give them credit.

/*
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // create result variable to store lowercase word
    char result = tolower(word[0]);
    int w = result - 'a';
    // print the hash index for testing
    //printf("%i\n", w);
    // return result of ASCII arithmetic
    return w;
}
*/


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

    int hash_index;

    // open file to be read
    FILE* file = fopen(dictionary, "r");

    if (file == NULL)
    {
        // if file is empty, return false and stop program
        return false;
    }

    // initialize variable to store a string from dictionary
    char word[LENGTH + 1];

    while ((fscanf(file, "%s", word)) != EOF)
    {
        // find hash index
        hash_index = hash(word);


        // create a new node
        node* n = malloc(sizeof(node));
        if (n == NULL)
        {
            // if memory is used up, end program
            return false;
        }

        // copy word into new node
        strcpy(n->word, word);

        // set index to point to newly inserted node
        if (table[hash_index] == NULL)
        {

            // set table index to initial node
            table[hash_index] = n;

            // set node pointer to NULL
            n->next = NULL;
        }
        else
        {
            // set node pointer to what table index points to
            n->next = table[hash_index];

            // set table index to point to new node
            table[hash_index] = n;
        }

        // update counter value
        counter++;

    }

    // close the file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    // initialize a cursor and temp value, per Brian Yu suggestion
    node* cursor = NULL;
    node* temp = NULL;

    // iterate through each linked list in the hash table, using its index
    for(int i = 0; i < N; i++)
    {
        // initialize a cursor and a temp value that is repeatedly set equal to cursor
        cursor = table[i];
        temp = cursor;

        // iterate through each word in the linked list
        // set cursor equal to the next word and freeing the temp value
        while(cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }

    }

    // free remaining memory
    free(cursor);
    free(temp);

    return true;
}