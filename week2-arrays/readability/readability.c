#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string user_text);
int count_words(string user_input);
int count_sentences(string user_words);
int reading_level(int letters, int sentences, int words);
void print_grade_level(int level);


int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int readinglevel = reading_level(letters, sentences, words);
    print_grade_level(readinglevel);
}

// Counting the number of letters
int count_letters(string user_text)
{
    int letter_sum = 0;
    // Declaring sum which will track number of letters
    for (int i = 0, n = strlen(user_text); i < n; i++)
    {
        // Creating a character variable to break down the string into individual characters
        char steps = user_text[i];

        // Creating a conditional so I can count characters (letters in this case) that have an ASCII interger within
        // the range for capital letters, or an ASCII integer within the range of lowercase letters. Punctuation and space
        // will not be recorded in this count.
        if (((steps >= 65) && (steps <= 90)) || ((steps >= 97) && (steps <= 122)))
        {
            letter_sum += 1;
        }
    }
    return letter_sum;
}

int count_words(string user_input)
{
    int word_sum = 1;
    // Count the number of words.
    // Assumptions: Sentence will not begin or end with space, a sentence will not have multiple spaces in a row. Therefore,
    // every ocurrence of a space would represent a word that has been written.
    for (int i = 0, n = strlen(user_input); i < n; i++)
    {
        char characters = user_input[i];
        if (characters == ' ')
        {
            word_sum += 1;
        }
    }
    return word_sum;
}


// The definition for a sentence taken to be any sequence of characters that ends in: '.', '!', or '?'
// The below conditional evaluates each character of the string and updates the sentencesum variable for every occurrence
// of the above punctuation.
int count_sentences(string user_words)
{
    int sentence_sum = 0;
    for (int i = 0, n = strlen(user_words); i < n; i++)
    {
        char character_list = user_words[i];
        if ((character_list == '.') || (character_list == '!') || (character_list == '?'))
        {
            sentence_sum += 1;
        }
    }
    return sentence_sum;
}

// Creating a function to calculate the Coleman-Liau index
int reading_level(int letters, int sentences, int words)
{
    // Where avg_letters equals the average number of letters per 100 words.
    // avg_sentences equals the average number of sentences per 100 words.

    float avg_letters = (100 * ((float) letters / (float) words));
    float avg_sentences = (100 * ((float) sentences / (float) words));

    float float_index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;
    double rounding = round(float_index);
    return (int) rounding;
}

// Can use a void function to provide a console output
// Note there is no return statement, therefore this is a void function.
// A void function is used to do something (not to calculate something) such as printing
// A void function is a function that is designed for a task like this, in general, wouldn't want to use print statements in
// other functions that are designed to calculate things and return a value.
void print_grade_level(int level)
{
    if (level >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", level);
    }
}