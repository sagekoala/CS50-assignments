// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // NOTE: Word is from text, the words stored in table[N] array are nodes storing the dictionary words
    // Checking if a word is correctly spelling means searching the hash_table to see if there is a match
    // All of the words in the hash_table (i.e. words from the dictionary) are lowercase
    // Copying word into a lower_word temporary variable
    char lower_word[LENGTH + 1];
    strcpy(lower_word, word);
    int len = strlen(lower_word);

    // Converting each character to lowercase (each word in the dictionary is lowercase)
    for (int j = 0; j < len + 1; j++)
    {
        lower_word[j] = tolower(lower_word[j]);
    }

    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            // Comparing lowercase word against the words at each node in the hash table
            if (strcmp(tmp->word, lower_word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    // Read strings from the file one at a time
    // Create a new node for each word
    // Hash word to obtain a hash value
    // Insert node into hash table at that value

    // Use fopen to open file, error check for null
    // fscanf to read strings from file
    // fscanf will return EOF once it reaches the end of the file
    int bucket = 0;
    char buffer[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fclose(file);
        return false;
    }
    else
    {
        while (fscanf(file, "%s", buffer) != EOF)
        {
            // Want to call the hash function to get the position of the buffer in the hash table
            bucket = hash(buffer);
            node *temp = malloc(sizeof(node));
            if (temp == NULL)
            {
                unload();
            }
            strcpy(temp->word, buffer);
            temp->next = table[bucket];
            table[bucket] = temp;
        }
        fclose(file);
        return true;
    }
    fclose(file);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    long count = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            count++;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor = NULL;
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
