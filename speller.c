// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
int wordCount = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int wordIndex = hash(word);

    node *cursor = table[wordIndex];
    while (cursor != NULL) 
    {
        if (strcasecmp(word, cursor->word) == 0) 
        {
            return true;
        };
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Return the first letter of the word as the bucket
    int firstLetter = word[0];
    firstLetter = toupper(firstLetter);
    firstLetter -= 65;
    return firstLetter;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens the given dictionary and checks if there is enough memory
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        free(dict);
        return false;
    }

    // The newWord is a placeholder for the word that is currently loaded
    char newWord[LENGTH + 1];
    while (fscanf(dict, "%s", newWord) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL) 
        {
            free(n);
            return false;
        }
        strcpy(n->word, newWord);
        // Set the word at the head of the linked list at that index, then set the pointer to the rest of the list
        int wordIndex = hash(newWord);
        n->next = table[wordIndex];
        table[wordIndex] = n;
        wordCount++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL) 
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
