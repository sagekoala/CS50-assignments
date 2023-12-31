#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner

    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 == score2)
    {
        printf("Tie!");
    }
    else
    {
        printf("Player 2 wins!");
    }
}


int compute_score(string word)
{
    // TODO: Compute and return score for string
    // My idea is to write a loop to print each letter and the corresponding score
    // Loop converts each character of string word into uppper case (i.e. a letter with ASCII value between 65 and 90)
    // Sum then adds the corresponding amount of points stored at the index of the POINTS[] array;
    int sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char steps = word[i];
        char upper = toupper(steps);
        sum += POINTS[upper - 65];
    }
    return sum;
}
