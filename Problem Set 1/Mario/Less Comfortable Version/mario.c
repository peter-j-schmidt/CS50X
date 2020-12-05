#include <cs50.h>
#include <stdio.h>

// Asks user for a number between 1 and 8
int main(void)
{
    int n;
    do
    {
        n = get_int("Choose a height between 1 and 8: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // determines how many spaces to print before the #s.
            if (j == n - i - 1 || j > n - i - 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        // prints the next loop on a new line.
        printf("\n");
    }
}