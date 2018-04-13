// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

const int SIZE = 27;

// node struct
typedef struct node
{
    bool is_word;
    struct node* children[SIZE];
}
node;

node *root = NULL;

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
    root = (struct node*)malloc(sizeof(struct node));
    node* trie = root;
    trie->is_word = false;

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    while(!feof(file))
    {
        char letter;
        int index = 0;

        letter = fgetc(file);



        printf("%d/", letter);
    }

    printf("%lu\n", sizeof(root));
    printf("%d", root->is_word);

    fclose(file);

    // TODO
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return true;
}
