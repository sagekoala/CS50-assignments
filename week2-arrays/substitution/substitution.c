#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    char upper_alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char lower_alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int sum = 0;
    int value = 0;

    // Checking to make sure key was provided. argc stands for number of command arguments, i.e. the file name ./substitution being one,
    // the user provided key in the command-line being the second

    if (argc != 2)
    {
        printf("Error, command-line argument required.\n");
        return 1;
    }

    // Checking to see if length of the provided key is 26 characters exactly
    if (strlen(argv[1]) != 26)
    {
        printf("The key provided was not 26 characters.\n");
        return 1;
    }

    // Checking the characters to make sure they are ASCII alphabetical characters
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Non-alphabetical character incorrectly provided in command-line argument.\n");
            return 1;
        }
    }

    // Checking for duplicate values.
    // Sum should go to 0 after looping through
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isupper(argv[1][i]) != 0)
        {
            sum += (argv[1][i] - (65 + i));
        }
        else
        {
            sum += (argv[1][i] - 32 - (65 + i));
        }
    }

    // If sum not zero, it means there was a duplicate provided in the key
    if (sum != 0)
    {
        printf("Error: Duplicate values entered in command-line code\n");
        return 1;
    }


    // For loop to rotate each character of the upper and lower alphabet character arrays to create the repository that we will pull
    // our cipher text from
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isupper(argv[1][i]) != 0)
        {
            upper_alphabet[i] += argv[1][i] - (65 + i);
            lower_alphabet[i] += argv[1][i] + 32 - (97 + i);
        }
        else
        {
            lower_alphabet[i] += argv[1][i] - (97 + i);
            upper_alphabet[i] += argv[1][i] - 32 - (65 + i);
        }
    }

    // Get user string, adjust upper and lower alphabets according to the corresponding ASCII values.
    // Accounting for uppercase and lowercase (each of those functions also ensures value is within ASCII range of alphabetical characters),
    // otherwise, printing the user-provided characters as is (such as '!' or ' ').
    string plaintext = get_string("Plain text: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            printf("%c", upper_alphabet[(plaintext[i] - (65))]);
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", lower_alphabet[(plaintext[i] - (97))]);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}