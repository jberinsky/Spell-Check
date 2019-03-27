// Jason Berinsky
// CS 50 Problem Set 4
// Implements a dictionary's functionality for use in a spell checker via a trie

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Counter for number of words in dictionary
unsigned int count = 0;

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root = NULL;

// Creates a new node in the trie initialized to NULL
struct node *make_node(void)
{
    struct node *new_node = NULL;
    new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node)
    {
        new_node->is_word = false;
        for (int i = 0; i < N; i++)
        {
            new_node->children[i] = NULL;
        }
    }
    return new_node;
}

// Recursively unloads from memory a trie down from a passed node
void unload_node(node *current_node)
{
    for (int i = 0; i < N; i++)
    {
        if (current_node->children[i] != NULL)
        {
            unload_node(current_node->children[i]);
        }
    }
    free(current_node);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        struct node *current_node = root;
        int index;
        for (int i = 0, n = strlen(word); i < n; i++)
        {
            // Provides node index for current letter of the word being entered into the trie
            if (word[i] == '\'')
            {
                index = 26;
            }
            else if (word[i] >= 'A' && word[i] <= 'Z')
            {
                index = (int) word[i] - 65;
            }
            else
            {
                index = (int) word[i] - 97;
            }

            if (!current_node->children[index])
            {
                current_node->children[index] = make_node();
            }
            current_node = current_node->children[index];
        }
        current_node->is_word = true;
        count++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index;
    struct node *current_node = root;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        if (word[i] == '\'')
        {
            index = 26;
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            index = (int) word[i] - 65;
        }
        else
        {
            index = (int) word[i] - 97;
        }
        if (!current_node->children[index])
        {
            return false;
        }
        current_node = current_node->children[index];
    }
    if (current_node != NULL && current_node->is_word)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (!root)
    {
        return false;
    }

    unload_node(root);
    return true;
}