// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

const int SIZE = 27;

// node struct for a trie
typedef struct node
{
    bool is_word;
    struct node* children[SIZE];
}
node;

// trie root node
node *root;

// word counter for dictionary
unsigned int numWords = 0;

/*Helper functions for dictionary.c*/

// Returns a new initialized node pointer
struct node* makeNode(void)
{
    // allocate space for and create a new node
    struct node* newNode =(struct node*)malloc(sizeof(struct node));

    if (newNode != NULL)
    {
        // initialize is_word to false
        newNode->is_word = false;

        // insert NULL into children array
        for (int i = 0; i < SIZE; i++)
        {
            newNode->children[i] = NULL;
        }
    }

    return newNode;
}


// Deletes trie from the bottom up
void deleteTrie(node* trie)
{
    // if no trie return
    if(!trie)
    {
        return;
    }

    // using recursion go to last node of trie
    for (int i = 0; i < SIZE; i++)
    {
       deleteTrie(trie->children[i]);
    }

    // remove node
    free(trie);
}

/*Main functions for dictionary.c*/

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // copy of root to iterate through trie
    node* trie = root;

    // for each letter of word
    for (int i = 0; i < strlen(word); i++)
    {
        // if apostrophe char
        if (word[i] == '\'')
        {
            // check last index of children
            // if false word not in dictionary
            if (!trie->children[SIZE - 1])
            {
                return false;
            }
            // else move to next node
            else
            {
                trie = trie->children[SIZE - 1];
            }
        }
        // if alpha char
        else
        {
            // check chars index in children array
            // if false word not in dictionary
            if (!trie->children[tolower(word[i]) - 'a'])
            {
                return false;
            }
            // else move to next node
            else
            {
                trie = trie->children[tolower(word[i]) - 'a'];
            }
        }
    }

    // if at the end of word
    // and is_word is false
    // word not in dictionary
    if (!trie->is_word)
    {
        return false;
    }

    // word found
    return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // make a new node at root
    root = makeNode();

    // open and check dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    // array to store words from dictionary file
    char word[47];


    // get each word row by row from dictionary file
    // while checking for the files end
    while(fgets(word, sizeof(word), file) != NULL)
    {
        // index for each letter of word
        int index = 0;
        // copy root node to return to top of trie
        node* trie = root;

        // while not at the end of a word
        // iterate through each letter
        while (word[index] != '\n')
        {
            // if apostrophe char
            // insert node in the last index
            if (word[index] == '\'')
            {
                // if no node exists make a new one
                if (!trie->children[SIZE - 1])
                {
                    trie->children[SIZE - 1] = makeNode();
                }

                // point to the current node in trie
                trie = trie->children[SIZE - 1];
            }
            // if alpha char
            // insert node at chars alphabetic position in the children array
            else
            {
                // if no node exists make a new one
                if (!trie->children[word[index] - 'a'])
                {
                    trie->children[word[index] - 'a'] = makeNode();
                }

                 // point to the current node in trie
                trie = trie->children[word[index] - 'a'];
            }

            // next letter of word
            index++;
        }

        // set is_word to true
        trie->is_word = true;
        // increment number of words in dictionary
        numWords++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    deleteTrie(root);
    return true;
}
