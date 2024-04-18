#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie *child[26];
    int count;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *newTrie = (struct Trie*)malloc(sizeof(struct Trie));
    for(int i = 0; i < 26; i++) {
        newTrie->child[i] = NULL;
    }
    newTrie->count = 0;

    return newTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;

    for(int i = 0; i < strlen(word); i++) {
        if(current->child[word[i] - 'a'] == NULL)
            current->child[word[i] - 'a'] = createTrie();
        current = current->child[word[i] - 'a'];
    }
    current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    for(int i = 0; i < strlen(word); i++) {
        if(current->child[word[i] - 'a'] == NULL)  
            return 0;
        current = current->child[word[i] - 'a'];
    }
    return current->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL) {
        return pTrie;
    }
    for(int i = 0; i < 26; i++) {
        if(pTrie->child[i] != NULL) {
            return deallocateTrie(pTrie->child[i]);
            free(pTrie);
        }
    }
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* inFile = fopen(filename, "r");

    int numWords;
    char word[256];
    fscanf(inFile, "%d", &numWords);
    for (int i=0;i<numWords;++i)
	{
		fscanf(inFile, "%s", word);
        pInWords[i] = (char*)malloc(sizeof(char)*256);
        if(pInWords[i] == NULL) exit(0);
        strcpy(pInWords[i], word);
	}
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}