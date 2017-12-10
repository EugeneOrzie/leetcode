#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXIMUM_CAPACITY 100
#define STRING_LENGTH 10

struct entry{
	char* substring;
	struct entry* next;
	int count;
};

int getIndex(long hashValue){
	return (int)(hashValue % MAXIMUM_CAPACITY);
}

long getHashValue(char* key){
	long hashValue = 0;
	while (*key){
		hashValue = hashValue + (hashValue << 4) + (*key);
		key++;
	}
	return hashValue;
}

struct entry* get(struct entry** hashTable, char* key){
	int index = getIndex(getHashValue(key));
	struct entry* p = hashTable[index];
	while (p){
		if (p->substring == NULL){
			printf("p->substring is NULL\n");
		}
		printf("get string %s, entry[%d] = %s\n", key, index, p->substring);
		if (strcmp(p->substring, key) == 0){
			return p;
		} else {
			p = p->next;
		}
	}
	return 0;
}

int put(struct entry** hashTable, char* key){
	struct entry* q = get(hashTable, key);

	if (q){
		q->count = q->count + 1;	
		return q->count;
	}
	int index = getIndex(getHashValue(key));
	struct entry* p = (struct entry*)malloc(sizeof(struct entry));
	if (p == NULL){
		printf("can not malloc space for put\n");
		return -1;
	}
	p->substring = key;
	p->next = hashTable[index];
	p->count = 1;
	
	hashTable[index] = p;
	return 1;
}

int destroy(struct entry** hashTable){
	for (int i = 0; i < MAXIMUM_CAPACITY; i++){
		struct entry* ent = hashTable[i];
		struct entry* next = NULL;
		while (ent){
			next = ent->next;
			//free(ent->substring);
			free(ent);
			ent = next;
		}
	}
	free(hashTable);
	return 1;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findRepeatedDnaSequences(char* s, int* returnSize) {
	*returnSize = 0;
    struct entry** hashTable = (struct entry**)malloc(sizeof(struct entry*) * MAXIMUM_CAPACITY);
    if (hashTable == NULL){
    	printf("can not malloc space for hashTable\n");
    	return NULL;
    }
    for (int i = 0; i < MAXIMUM_CAPACITY; i++){
        hashTable[i] = NULL;
    }
    char* ss = s;
    int count = 0;
    while (*ss){
    	count++;
    	ss++;
    }
    char** ret = (char**)malloc(sizeof(char*) * count);
    if (ret == NULL){
    	printf("can not malloc space for ret\n");
    	return NULL;
    }
    printf("a %d\n", count);
    for (int i = 0; i < count - STRING_LENGTH + 1; i++){
    	char* substring = (char*)malloc(STRING_LENGTH + 1);
    	if (substring == NULL){
    		printf("can not malloc space for substring\n");
    		return NULL;
    	}
    	strncpy(substring, s + i, STRING_LENGTH);
    	substring[STRING_LENGTH] = '\0';
    	int happenTime = put(hashTable, substring);
    	printf("substring:%s happened:%d\n", substring, happenTime);
    	if (happenTime == 2){
    		ret[(*returnSize)++] = substring;
    	}
    }
    destroy(hashTable);
    return ret;
}

int main(){
	char** ss;
	
    char* a1 = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    int* a2 = (int*)malloc(sizeof(int*));
    ss = findRepeatedDnaSequences(a1, a2);
    for (int i = 0; i < *a2; i++){
    	printf("ret=%s \n", ss[i]);
    	free(ss[i]);
    }
    free(a2);
    if (ss){
    	free(ss);
    }

    char* b1 = "AAAAAAAAAAA";
    int* b2 = (int*)malloc(sizeof(int*));
    ss = findRepeatedDnaSequences(b1, b2);
    for (int i = 0; i < *b2; i++){
    	printf("ret=%s \n", ss[i]);
    	free(ss[i]);
    }
    free(b2);
    if (ss){
    	free(ss);
    }
}