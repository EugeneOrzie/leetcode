#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isMatch(char* s, char* p) {
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

    matchStr = s;
    patternStr = p;

    printf("length(s)=%d, length(p)=%d \n", matchLength, patternLength);

    if (patternLength == 0){
        if (matchLength != 0){
            return 0;
        } else {
            return 1;
        }
    }

    int f[patternLength + 1][matchLength + 1];
    memset(f, 0, (patternLength + 1) * (matchLength + 1) * 4);
    //border
    f[0][0] = 1;
    for (int i = 1; i <= patternLength; i++){
        if (*(patternStr + i - 1) == '*'){
            f[i][0] = 1;
        } else {
            break;
        }
    }
    for (int i = 1; i <= patternLength; i++){
        for (int j = 1; j <= matchLength; j++){
            if (*(patternStr + i - 1) != '*'){
                if ((*(patternStr + i - 1) == '?') || (*(patternStr + i - 1) == *(matchStr + j - 1))){
                    f[i][j] = f[i - 1][j - 1];
                }
            } else {
                if (f[i - 1][j]){
                    f[i][j] = 1;
                    continue;
                }
                int k = j;
                while (k > 0){
                    k--;
                    if (f[i - 1][k]){
                        f[i][j] = 1;
                        break;
                    }
                }
            }
            //printf("%d ", f[i][j]);
        }
        //printf("\n");
    }
    return f[patternLength][matchLength];
}

int isMatchOptimic(char* s, char* p) {
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

    matchStr = s;
    patternStr = p;

    char cutStr[patternLength];
    int cutPatternLength = 0;
    for (int i = 0; i < patternLength; i++){
    	//printf("s[%d]=%c", i, *(patternStr + i));
    	if ((i != 0) && (*(patternStr + i) == '*') && (*(patternStr + i - 1) == '*')){
    		continue;
    	} else {
    		cutStr[cutPatternLength] = *(patternStr + i);
    		cutPatternLength++;
    	}
    }
    patternStr = cutStr;
    patternLength = cutPatternLength;

    printf("length(s)=%d, length(p)=%d \n", matchLength, patternLength);

    if (patternLength == 0){
        if (matchLength != 0){
            return 0;
        } else {
            return 1;
        }
    }

    int f[patternLength + 1][matchLength + 1];
    memset(f, 0, (patternLength + 1) * (matchLength + 1) * 4);
    //border
    f[0][0] = 1;
    for (int i = 1; i <= patternLength; i++){
        if (*(patternStr + i - 1) == '*'){
            f[i][0] = 1;
        } else {
            break;
        }
    }
    for (int i = 1; i <= patternLength; i++){
        for (int j = 1; j <= matchLength; j++){
            if (*(patternStr + i - 1) != '*'){
                if ((*(patternStr + i - 1) == '?') || (*(patternStr + i - 1) == *(matchStr + j - 1))){
                    f[i][j] = f[i - 1][j - 1];
                }
            } else {
                if (f[i - 1][j]){
                    f[i][j] = 1;
                    continue;
                }
                int k = j;
                while (k > 0){
                    k--;
                    if (f[i - 1][k]){
                        f[i][j] = 1;
                        break;
                    }
                }
            }
            //printf("%d ", f[i][j]);
        }
        //printf("\n");
    }
    return f[patternLength][matchLength];
}

int isMatchOptimic2(char* s, char* p) {
    int hasStar = 0;
    char* pp = p;
    char* ss = s;
    while (*s){
        //printf("s=%c, p=%c\n", *s, *p);
        //printf("sp=%p, pp=%p\n", s, p);
        if ((*s == *p) || (*p == '?')){
            s++;
            p++;
            continue;
        }

        if (*p == '*'){
            pp = p + 1;
            hasStar = 1;
            ss = s;
            p++;
            continue;
        }

        if (hasStar){
            p = pp;
            ss++;
            s = ss;
            continue;
        }
        return 0;
    }
    while (*p){
        if (*p != '*'){
            return 0;
        }
        p++;
    }
    return 1;
}

int main(){

    char* a1 = "aa";
    char* a2 = "a";
    printf("ret=%d \n\n", isMatchOptimic2(a1, a2));

    char* b1 = "aa";
    char* b2 = "a*";
    printf("ret=%d \n\n", isMatchOptimic2(b1, b2)); 

    char* c1 = "aab";
    char* c2 = "?*a*b";
    printf("ret=%d \n\n", isMatchOptimic2(c1, c2)); 

    char* d1 = "aa";
    char* d2 = "a?";
    printf("ret=%d \n\n", isMatchOptimic2(d1, d2)); 

    char* e1 = "dklsafjldskfjlsdkfj";
    char* e2 = "d*k*";
    printf("ret=%d \n\n", isMatchOptimic2(e1, e2)); 

    char* f1 = "";
    char* f2 = "";
    printf("ret=%d \n\n", isMatchOptimic2(f1, f2)); 

    char* g1 = "asdfsdfd";
    char* g2 = "a*********************************************";
    printf("ret=%d \n\n", isMatchOptimic2(g1, g2)); 

    char* h1 = "aaaa";
    char* h2 = "***a";
    printf("ret=%d \n\n", isMatchOptimic2(h1, h2)); 
}