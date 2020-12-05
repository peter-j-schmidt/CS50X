#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // initialize a number of int and float values needed for the program.
    float change;
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    do
    {
        // Asks the user for the amount of change due, so long as a positive integer is given.
        change = get_float("Please enter the amount of change owed, without the dollar sign: ");
    }
    while (change < 0);
    // Converts the amount given to a rounded whole number.
    int coins = round(change * 100);
    // A count of coins used in making change.
    int coin_count = 0;
    // Uses loops to find the amount of coins needed, using a greedy algorithm that utilizes larger coins first.
    do
    {
        if (coins >= 25)
        {
            coins -= quarter;
            coin_count += 1;
        }
        else if (coins < 25 && coins >= 10)
        {
            coins -= dime;
            coin_count += 1;
        }
        else if (coins < 10 && coins >= 5)
        {
            coins -= nickel;
            coin_count += 1;
        }
        else if (coins < 5 && coins > 0)
        {
            coins -= penny;
            coin_count += 1;
        }
    }
    while (coins > 0);
    printf("%i\n", coin_count);
}