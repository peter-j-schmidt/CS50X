#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

float letter_count(int n, string s);
float word_count(int n, string s);
float sentence_count(int n, string s);
float lc;
float wc;
float sc;

int main(void)
{
    string s = get_string("Input: "); // gets user input.
    //printf("%s\n", s); // prints user input
    int n = strlen(s); // calculates length of string
    lc = letter_count(n, s);
    //printf("Letters: %.0f\n", lc); // prints the letter count
    wc = word_count(n, s);
    //printf("Words: %.0f\n", wc);
    sc = sentence_count(n, s);
    //printf("Sentences: %.0f\n", sc);
    float L = lc / (wc / 100);
    float S = sc / (wc / 100);
    float grade_level = 0.0588 * L - 0.296 * S - 15.8; // computes the grade level of the passage.
    if (grade_level < 1) // a loop that prints out the grade level of the passage, according to the assignment parameters.
    {
        printf("Before Grade 1\n");
    }
    else if (grade_level > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", grade_level);
    }
}

float letter_count(int n, string s) // counts the letters in a passage.
{
    for (int i = 0; i < n; i++)
    {
        if (isalpha(s[i]) != 0)
        {
            lc += 1;
        }
    }
    return lc;
}

float word_count(int n, string s) // counts the words in a passage.
{
    for (int i = 0; i < n; i++)
    {
        if (isblank(s[i]) != 0)
        {
            wc += 1;
        }
    }
    return wc + 1;
}

float sentence_count(int n, string s) // counts the number of sentences in a passage.
{
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sc += 1;
        }
    }
    return sc;
}