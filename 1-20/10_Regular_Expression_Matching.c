#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Wrong Answer
int isMatch(char* s, char* p) {
    char* patternStr = p;
    char* matchStr = s;
    while (*patternStr != '\0'){
        char block_char = *patternStr;
        int block_number_count = 0;
        int unlimited = 0;

        //find a block
        while (*patternStr != '\0'){
            if (block_char == *patternStr){
                patternStr++;
                if (*patternStr != '*'){
                    block_number_count++;
                } else {
                    unlimited = 1;
                    patternStr++;
                }
            } else {
                break;
            }
        }
        printf("block_char=%c, number=%d, unlimited=%d \n", block_char, block_number_count, unlimited); 

        //try to match with block
        while (*matchStr != '\0'){
            printf("matchStr=%c, number=%d \n", *matchStr, block_number_count); 
            if ((block_char != '.') && (block_char != *matchStr)){
                if (block_number_count != 0){
                    return 0;
                } else {
                    break;
                }
            }

            if (block_number_count > 0){
                block_number_count--;
                matchStr++;
                continue;
            }

            if (block_number_count == 0){
                if (unlimited){
                    matchStr++;
                    continue;
                } else {
                    break;
                }
            }
        }

        if ((*matchStr == '\0') && (block_number_count == 0)){
            continue;
        }
    }

    if (*matchStr == '\0'){
        return 1;
    } else {
        return 0;
    }
}

struct block{
    char ch;
    int limited;
};

int isMatchDynamicProgramming(char* s, char* p) {
    //Calculate the length
    char* matchStr = s;
    char* patternStr = p;
    int matchLength = 0;
    while (*matchStr != '\0'){
        matchStr++;
        matchLength++;
    }
    int patternLength = 0;
    while (*patternStr != '\0'){
        patternStr++;
        patternLength++;
    }

    printf("length(s)=%d, length(p)=%d \n", matchLength, patternLength);

    if (patternLength == 0){
        if (matchLength != 0){
            return 0;
        } else {
            return 1;
        }
    }
    
    //Preprocess s to block
    struct block blocks[patternLength];
    int blockLength = 0;
    matchStr = s;
    patternStr = p;
    while (*patternStr != '\0'){
        struct block newBlock;
        newBlock.ch = *patternStr;
        patternStr++;
        if (*patternStr == '*'){
            newBlock.limited = 0;
            patternStr++;
        } else {
            newBlock.limited = 1;
        }
        blocks[blockLength] = newBlock;
        blockLength++;
    }

    //Calculate f[i][j], which means whether the first (i - 1)'s block can match the first (j-1)'s str; f[blockLength + 1][matchStr + 1] is the answer
    int f[blockLength + 1][matchLength + 1];
    printf("blockLength=%d, sizeof(f)=%ld \n", blockLength, sizeof(f));
    memset(f, 0, (blockLength + 1) * (matchLength + 1) * 4);
    //border
    f[0][0] = 1;
    for (int i = 1; i <= blockLength; i++){
        if (!blocks[i - 1].limited){
            f[i][0] = 1;
        } else {
            break;
        }
    }
    for (int i = 1; i <= blockLength; i++){
        for (int j = 1; j <= matchLength; j++){
            if (blocks[i - 1].limited){
                if ((blocks[i - 1].ch == '.') || (blocks[i - 1].ch == *(matchStr + j - 1))){
                    f[i][j] = f[i - 1][j - 1];
                }
            } else {
                if (f[i - 1][j]){
                    f[i][j] = 1;
                    continue;
                }
                int k = j;
                while ((k > 0) && ((blocks[i - 1].ch == *(matchStr + k - 1)) || (blocks[i - 1].ch == '.'))){
                    k--;
                    if (f[i - 1][k]){
                        f[i][j] = 1;
                        break;
                    }
                }
            }
            printf("%d ", f[i][j]);
        }
        printf("\n");
    }
    return f[blockLength][matchLength];
}

int main(){

    char* a1 = "aa";
    char* a2 = "a";
    printf("ret=%d \n\n", isMatchDynamicProgramming(a1, a2));

    char* b1 = "aa";
    char* b2 = "a*";
    printf("ret=%d \n\n", isMatchDynamicProgramming(b1, b2)); 

    char* c1 = "aab";
    char* c2 = "c*a*b";
    printf("ret=%d \n\n", isMatchDynamicProgramming(c1, c2)); 

    char* d1 = "aa";
    char* d2 = "a.";
    printf("ret=%d \n\n", isMatchDynamicProgramming(d1, d2)); 

    char* e1 = "dklsafjldskfjlsdkfj";
    char* e2 = "a*k*";
    printf("ret=%d \n\n", isMatchDynamicProgramming(e1, e2)); 

    char* f1 = "";
    char* f2 = "";
    printf("ret=%d \n\n", isMatchDynamicProgramming(f1, f2)); 

    char* g1 = "a";
    char* g2 = "";
    printf("ret=%d \n\n", isMatchDynamicProgramming(g1, g2)); 
}