// C implementation of search and insert operations on Trie
// http://www.geeksforgeeks.org/trie-insert-and-search/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26)		// Alphabet size (# of symbols)
#define CHAR_TO_INDEX(c) ((int)c-(int)'a')	// Converts alphabet into index, using only 'a' through 'z'

// trie node
struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	bool isLeaf;	// isLeaf is true if the node represents end of a word
};
 
// Returns a new trie node
struct TrieNode *getNode(void){
	struct TrieNode *pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
	if (pNode){
		pNode->isLeaf = false;
		for (int i = 0; i < ALPHABET_SIZE; i++)
			pNode->children[i] = NULL;
	} else {
		// Error messages!!!
	}
	return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key){
	int index, length = strlen(key);
	struct TrieNode *p = root;
 
	for (int level = 0; level < length; level++) {
		index = CHAR_TO_INDEX(key[level]);
		if (!p->children[index])
			p->children[index] = getNode();
		p = p->children[index];
	}
	p->isLeaf = true;	// mark last node as leaf
}
 
// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key){
	int index, length = strlen(key);
	struct TrieNode *p = root;
 
	for (int level = 0; level < length; level++){
		index = CHAR_TO_INDEX(key[level]);
		if (!p->children[index])
			return false;
		p = p->children[index];
	}
//	return (p != NULL && p->isLeaf);
	return (p->isLeaf);
}

// Main program
int main(){
	// Input keys (use only 'a' through 'z' and lower case)
	char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
	char output[][32] = {"Not in trie", "In trie"};
 
	struct TrieNode *root = getNode();
	// Construct trie
	for (int i=0; i<ARRAY_SIZE(keys); i++)
		insert(root, keys[i]);
 
	// Search for different keys
	printf("%s --- %s\n", "the", output[search(root, "the")] );
	printf("%s --- %s\n", "these", output[search(root, "these")] );
	printf("%s --- %s\n", "their", output[search(root, "their")] );
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );
 
 	// Free memory here!!!

	return 0;
}
