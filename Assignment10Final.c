#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 26

struct TrieNode
{
    struct TrieNode* children[MAXNAME];
    int count; // To store the number of occurrences of the word
};

// Creates a new trie node
struct TrieNode* createnode()
{
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode)
    {
        newNode->count = 0;
        for (int i = 0; i < MAXNAME; i++)
            newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(struct TrieNode* root, char* word)
{
    struct TrieNode* node = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (node->children[index] == NULL)
            node->children[index] = createnode();

        node = node->children[index];
    }
    node->count++;
}

int numberOfOccurrences(struct TrieNode* root, char* word)
{
    struct TrieNode* node = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (node->children[index] == NULL)
            return 0;

        node = node->children[index];
    }
    return node->count;
}

void deallocateTrie(struct TrieNode* root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < MAXNAME; i++)
    {
        if (root->children[i] != NULL)
            deallocateTrie(root->children[i]);
    }

    free(root);
}

struct TrieNode* createTrie()
{
    return createnode();
}

// Reads the dictionary file and returns the number of words
int readDictionary(char* filename, char** pInWords)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Error opening the dictionary file");
        exit(EXIT_FAILURE);
    }

    int numWords = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character from the word
        pInWords[numWords] = strdup(buffer); // Store the word in the array
        numWords++;
    }

    fclose(fp);
    return numWords;
}

int main(void)
{
    char* inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode* pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // Words to check the number of occurrences
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    deallocateTrie(pTrie);
    return 0;
}
