// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h> // which contain NULL
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// assuming that all maximum 45 letters in the word is 'z'
const unsigned int N = (LENGTH + 1) * 'z';

// Hash table
node *table[N];

//allocate memory to a new node


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0) // if matched
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // input: word; output: numerical index between 0 and N - 1, inclusive
    int sum = 0;
    int j = strlen(word);
    for (int i = 0; i < j; i++)
    {
        sum += tolower(word[i]); //
    }
    return (sum % N); // to make sure it does not go over bound
}

int totalnum = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // 1. open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    // 2. read strings from file one at time
    // file pointer; read a string; some place to read the word into
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF) //
    {
        // 3. creat a new node for each word
        node *new_node = malloc(sizeof(node));
        if (!new_node)
        {
            return false;
        }

        strcpy(new_node->word, word);
        new_node->next = NULL;

        // 4. hash word to obtain a hash value
        // use the hash fuction (function takes a string and returns an index)
        int index = hash(word);

        // 5. insert node to hash table at that location
        // takes a word as input
        // and outputs a number corrosponding to which "bucket" to store the word in
        if (!table[index])
        {
            table[index] = new_node;
        }
        else
        {
            // insert the word at the beginning
            // new_node's pointer points to the first word in hash table
            new_node->next = table[index];
            // then the the first word in hash[index] becomes the new word
            table[index] = new_node;
        }
        totalnum ++; //capture here
    }
    fclose(file); // 这里需要fclose这个文件
    return true; // 这里应该是true
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return totalnum;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true; // finished
}

//reference: https://www.youtube.com/watch?v=HsnjdbHMZO8