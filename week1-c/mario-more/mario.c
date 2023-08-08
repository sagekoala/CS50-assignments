#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Defining variable n and creating do-while loop to prompt user to provide a height
    // The do-while loop forces user to provide value between range [1:8] before the program continues
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Paramater for the rows
    for (int i = 1; i < n + 1; i++)
    {
        // Paramater for the columns of left pyramid
        for (int j = n; j > 0; j--)
        {
            // Conditional statement to offset the hashes to the right side of pyramid
            if (j > i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        // Printing the gap between the left pyramid
        printf("  ");

        // Nested loop for columns of right pyramid
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        // Escape sequence for to move to new line
        printf("\n");
    }
}