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

// word counter
unsigned int numWords = 0;

// returns a new initialized node pointer
struct node* makeNode(void)
{
    // allocate space for and create a new node
    struct node *newNode =(struct node*)malloc(sizeof(struct node));

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

void deleteTrie(node* trie)
{
    if(!trie)
    {
        return;
    }

    // recursive case (go to end of trie)
    for (int i = 0; i < SIZE; i++)
    {
       deleteTrie(trie->children[i]);
    }

    // base case
    free(trie);
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // copy of root to iterate through trie
    node* trie = root;

    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == '\'')
        {
            if (!trie->children[SIZE - 1])
            {
                return false;
            }
            else
            {
                trie = trie->children[SIZE - 1];
            }
        }
        else
        {
            if (!trie->children[tolower(word[i]) - 'a'])
            {
                return false;
            }
            else
            {
                trie = trie->children[tolower(word[i]) - 'a'];
            }
        }
    }

    if (!trie->is_word)
    {
        return false;
    }

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
            // if
            if (word[index] == '\'')
            {
                if (!trie->children[SIZE - 1])
                {
                    trie->children[SIZE - 1] = makeNode();
                }

                trie = trie->children[SIZE - 1];
            }
            else
            {
                //printf("%c", c[index]);
                if (!trie->children[word[index] - 'a'])
                {
                    trie->children[word[index] - 'a'] = makeNode();
                }

                trie = trie->children[word[index] - 'a'];
            }

            index++;
        }

        trie->is_word = true;
        numWords++;
    }

    fclose(file);

    // TODO
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return numWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    deleteTrie(root);
    return true;
}
