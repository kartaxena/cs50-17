/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;
node *root;
unsigned int words;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    node *current = root;
    
    for(int ch = 0; word[ch] != '\0'; ch++)
    {
        int w_ch = word[ch];
        if (w_ch == '\'')
        {
            w_ch = 26;
        }
         else
        {
            w_ch = tolower(w_ch) % 'a';
        }
        
        if (current->children[w_ch] == NULL)
        {
            return false;
        }
        else
        {
            current = current->children[w_ch];
        }
    }

    return current->is_word;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    words = 0;
    root = malloc(sizeof(node));
    // TODO
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Can't open %s\n", dictionary);
        return false;
    }
    int ch;
    node *current = root;
    while((ch = fgetc(dic)) != EOF)
    {
        
        if (ch == '\n')
        {
            current->is_word = true;
            words++;
            current = root;
            
        }
        else 
        {
            if (ch == '\'')
            {
                ch = 26;
                //printf("%c", ch);
            }
            else
            {
                ch = tolower(ch) % 'a';
            }
            if (current->children[ch] == NULL)
            {
                current->children[ch] = malloc(sizeof(node));
            }
            
            current = current->children[ch];
            
        }
    }
    fclose(dic);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    if (words > 0)
    {
        return words;
    }
    return false;
}

bool clear_memory(node *current)
{
    for(int i = 0; i <27; i++)
    {
        if (current->children[i] != NULL)
        {
            clear_memory(current->children[i]);
        }
    }
    
    free(current);
    return true;
    
}
/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return clear_memory(root);
}
