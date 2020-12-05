#include <stdio.h>
#include <cs50.h>

// The code below asks the user for their name, then prints a hello message to the user.
int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}