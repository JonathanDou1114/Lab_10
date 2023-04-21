#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie 
{
    struct Trie* children[ALPHABET_SIZE];
    int count;
    int isEndOfWord;
};

void insert(struct Trie** ppTrie, char* word) 
{
    struct Trie* current = *ppTrie;
    if (current == NULL) 
    {
        current = (struct Trie*)malloc(sizeof(struct Trie));
        current->count = 0;
        current->isEndOfWord = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) 
        {
            current->children[i] = NULL;
        }
        *ppTrie = current;
    }
    for (int i = 0; i < strlen(word); i++) 
    {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) 
        {
            current->children[index] = (struct Trie*)malloc(sizeof(struct Trie));
            current->children[index]->count = 0;
            current->children[index]->isEndOfWord = 0;
            for (int j = 0; j < ALPHABET_SIZE; j++) 
            {
                current->children[index]->children[j] = NULL;
            }
        }
        current = current->children[index];
    }
    current->count++;
    current->isEndOfWord = 1;
}

int numberOfOccurrences(struct Trie* pTrie, char* word) 
{
    struct Trie* current = pTrie;
    for (int i = 0; i < strlen(word); i++) 
    {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) 
        {
            return 0;
        }
        current = current->children[index];
    }
    if (current != NULL && current->isEndOfWord) 
    {
        return current->count;
    }
    return 0;
}

struct Trie* deallocateTrie(struct Trie* pTrie) 
{
    if (pTrie != NULL) {
        for (int i = 0; i < ALPHABET_SIZE; i++) 
        {
            deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

int main(void) 
{
    struct Trie* trie = NULL;

    // read the number of the words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    insert(&trie, "notaword");
    insert(&trie, "ucf");
    insert(&trie, "no");
    insert(&trie, "note");
    insert(&trie, "corg");

    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) 
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) 
    {
        printf("There is an error in this program\n");
    }
    return 0;
}
