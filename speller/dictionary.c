// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("%s ", word);
    // TODO
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
    char letters[47];


    // get each word row by row from dictionary file
    // while checking for the files end
    while(fgets(letters, sizeof(letters), file) != NULL)
    {
        // index for each letter of word
        int index = 0;
        // copy root node to return to top of trie
        node* trie = root;

        // while not at the end of a word
        // (10 being the decimal value of a new line character)
        // iterate through each letter
        while (letters[index] != 10)
        {
            // if
            if (letters[index] == 39)
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
                if (!trie->children[letters[index] - 97])
                {
                    trie->children[letters[index] - 97] = makeNode();
                }

                trie = trie->children[letters[index] - 97];
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
