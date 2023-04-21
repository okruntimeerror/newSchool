#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    int count;
    struct Trie *children[ALPHABET_SIZE];
};

struct Trie *createNode(void) {
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insert(struct Trie **ppTrie, char *word) {
    if (*ppTrie == NULL)
        *ppTrie = createNode();

    struct Trie *current = *ppTrie;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            current->children[index] = createNode();
        current = current->children[index];
    }

    current->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            return 0;
        current = current->children[index];
    }

    return current->count;
}

void freeTrie(struct Trie *pTrie) {
    if (pTrie == NULL)
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        freeTrie(pTrie->children[i]);

    free(pTrie);
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    freeTrie(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;

    // Read the number of words in the dictionary
    // Parse line by line, and insert each word into the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int numWords = sizeof(pWords) / sizeof(pWords[0]);

    for (int i = 0; i < numWords; i++)
        insert(&trie, pWords[i]);

    for (int i = 0; i < numWords; i++)
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));

    trie = deallocateTrie(trie);

    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}
