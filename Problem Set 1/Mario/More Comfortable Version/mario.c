#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        // prompts user for an input height.
        n = get_int("Choose a height between 1 and 8: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == n - 1)
            {
                // prints below character if the above condition is met.
                printf("#  #");
                for (int k = 0; k < i; k++)
                {
                    // prints after the first print statement.
                    printf("#");
                }
            }
            else if (j < n - 1 && j >= n - 1 - i)
            {
                // prints when the first condition fails.
                printf("#");
            }
            else
            {
                // prints when both conditions above fail.
                printf(" ");
            }
        }
        // prints a new line after the for loop above
        printf("\n");
    }
}