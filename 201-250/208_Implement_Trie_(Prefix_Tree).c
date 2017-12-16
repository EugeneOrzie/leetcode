#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CHARACTER_NUMBER 26

struct Node{
	int exist;
	struct Node** childs;
} ;

struct Node* nodeCreate(int exist) {
	struct Node* n = malloc(sizeof(struct Node));
	if (n == NULL){
		return NULL;
	}
	n->exist = exist;
	n->childs = malloc(sizeof(struct Node) * CHARACTER_NUMBER);
	if (n->childs == NULL){
		return NULL;
	}
	for (int i = 0; i < CHARACTER_NUMBER; i++){
		n->childs[i] = NULL;
	}
	return n;
}

int addWord(struct Node* node, char* word){
	if (node == NULL){
		return 0;
	}

	if (*word == '\0'){
    	node->exist = 1;
    	return 1;
    }

    int index = (*word - 'a');
    printf("word:%s, index:%d, char:%c\n", word, index, *word);
    if ((index < 0) || (index >= CHARACTER_NUMBER)){
    	return 0;
    }
    if (node->childs[index] == NULL){
    	node->childs[index] = nodeCreate(0);
    }
    return addWord(node->childs[index], word + 1);
}

int searchWord(struct Node* node, char* word){
	if (node == NULL){
		return 0; 
	}

	if (*word == '\0'){
    	return node->exist;
    }

    if (*word == '.'){
    	for (int i = 0; i < CHARACTER_NUMBER; i++){
    		if (node->childs[i]){
    			if (searchWord(node->childs[i], word + 1)){
    				return 1;
    			}
    		}
    	}
    } else {
    	int index = (*word - 'a');
    	if ((index < 0) || (index >= CHARACTER_NUMBER)){
    		return 0;
    	}
    	if (node->childs[index] == NULL){
    		return 0;
    	}
    	return searchWord(node->childs[index], word + 1);
    }
    return 0;
}

int searchStartsWith(struct Node* node, char* word){
    if (node == NULL){
        return 0; 
    }

    if (*word == '\0'){
        return 1;
    }

    if (*word == '.'){
        for (int i = 0; i < CHARACTER_NUMBER; i++){
            if (node->childs[i]){
                if (searchStartsWith(node->childs[i], word + 1)){
                    return 1;
                }
            }
        }
    } else {
        int index = (*word - 'a');
        if ((index < 0) || (index >= CHARACTER_NUMBER)){
            return 0;
        }
        if (node->childs[index] == NULL){
            return 0;
        }
        return searchStartsWith(node->childs[index], word + 1);
    }
    return 0;
}

void freeWord(struct Node* node){
	if (node == NULL){
		return; 
	}

	for (int i = 0; i < CHARACTER_NUMBER; i++){
		if (node->childs[i]){
			freeWord(node->childs[i]);
		}
	}

	free(node);
}


typedef struct {
    struct Node* root;
} Trie;

/** Initialize your data structure here. */
Trie* trieCreate() {
    Trie* wd = malloc(sizeof(Trie));
    if (wd == NULL){
        return NULL;
    }
    wd->root = nodeCreate(1); // this place may be handled more elegant
    if (wd->root == NULL){
        free(wd);
        return NULL;
    }
    return wd;
}

/** Adds a word into the data structure. */
//return should be some value;
void trieInsert(Trie* obj, char* word) {
	//Dictionary is NULL, can not add word.
    if (obj == NULL){
    	return;
    }

    //Word is NULL, do not need to add.
    if (*word == '\0'){
    	return;
    }

    //AddWord using Recursion
    int ret = addWord(obj->root, word);
    if (ret){
    	printf("Add %s success\n", word);
    } else {
    	printf("Add %s failed\n", word);
    }
    return;
}

/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
bool trieSearch(Trie* obj, char* word) {
    if (obj == NULL){
    	return 0;
    }

    if (*word == '\0'){
    	return 0;
    }

    return searchWord(obj->root, word);
}

bool trieStartsWith(Trie* obj, char* prefix) {
    return searchStartsWith(obj->root, prefix);
}

void trieFree(Trie* obj) {
    freeWord(obj->root);
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * struct WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);
 * bool param_2 = wordDictionarySearch(obj, word);
 * wordDictionaryFree(obj);
 */

int main(){
	Trie* obj = trieCreate();
	trieInsert(obj, "abcd");
	trieInsert(obj, "abc");
	trieInsert(obj, "");
	trieInsert(obj, "xzysdflkjasldfjksldafjksldfjk");
	trieInsert(obj, "ddslfjksldjflskadf13@#@#jlsdkfjlsakdfjlsdkjflskdjflskdjfldkkkkkkkkk.");
	trieInsert(NULL, "ddslfjksldjflskadf13@#@#jlsdkfjlsakdfjlsdkjflskdjflskdjfldkkkkkkkkk.");
	int param_1 = trieSearch(obj, "abcd");
	printf("Find %s, ret:%d\n", "abcd", param_1);
	int param_2 = trieSearch(obj, "abc");
	printf("Find %s, ret:%d\n", "abc", param_2);
	int param_3 = trieSearch(obj, "abcde");
	printf("Find %s, ret:%d\n", "abcde", param_3);
	int param_4 = trieSearch(obj, "xzysdflkjasldfjksldafjksldfjk");
	printf("Find %s, ret:%d\n", "xzysdflkjasldfjksldafjksldfjk", param_4);
    int param_11 = trieStartsWith(obj, "ab");
    printf("Find %s, ret:%d\n", "abcd", param_11);
    int param_21 = trieStartsWith(obj, "abc");
    printf("Find %s, ret:%d\n", "abc", param_21);
    int param_31 = trieStartsWith(obj, "abcde");
    printf("Find %s, ret:%d\n", "abcde", param_31);
    int param_41 = trieStartsWith(obj, "xzysdflkjasldfjksldafjk");
    printf("Find %s, ret:%d\n", "xzysdflkjasldfjksldafjk", param_41);
	trieFree(obj);
}