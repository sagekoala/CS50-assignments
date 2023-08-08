#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Defining variable n as integer
    // Setting up do-while loop to force range of n to [1:8]
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Left pyramid construction
    // Parameter for rows
    for (int i = 1; i < n + 1; i++)
    {
        // Paramater for columns
        for (int j = n; j > 0; j--)
        {
            // Conditional to offset the structure to the right
            if (j > i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        // Escape sequence to go to new line at the end of each cycle of the outer loop
        printf("\n");
    }
}