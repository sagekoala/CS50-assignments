#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Error, missing command-line argument.\n");
        return 1;
    }

    char alphabet_upper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char alphabet_lower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    // Converting string to integer with atoi() function so that we have the key as a number for our program
    // If argument count is not two, returning non-zero value to main as exit-code and printing error statement
    int key = atoi(argv[1]);


    // If the provided "key" is not a positive integer, returning non-zero value to main as exit-code and printing error message
    // that displays the necessary format for the command-line argument in order for the program to run.
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (48 > argv[1][i] || argv [1][i] > 57)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Getting a plain text string from the user.
    // Converting the string to a ciphercode based on the key that was provided. That is,
    // each character is being rotated by a value equal to the key provided, then the cipher code is printed.
    string plaintext = get_string("Plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (65 <= plaintext[i] && plaintext[i] <= 90)
        {
            printf("%c", ((alphabet_upper[(plaintext[i] - 65 + key) % 26])));
        }
        else if (97 <= plaintext[i] && plaintext[i] <= 122)
        {
            printf("%c", ((alphabet_lower[(plaintext[i] - 97 + key) % 26])));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}