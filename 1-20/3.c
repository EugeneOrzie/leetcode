#include<stdio.h>

int lengthOfLongestSubstring(char* s);

int main(){
	char* a = "abcabcbb";
	printf("ret=%d \n", lengthOfLongestSubstring(a));

	char* b = "bbbbb";
	printf("ret=%d \n", lengthOfLongestSubstring(b));

	char* c = "pwwkew";
	printf("ret=%d \n", lengthOfLongestSubstring(c));
}

int lengthOfLongestSubstring(char* s) {
    //Ok, Let's do it
    int MAX_CHAR_NUMBER = 256;
    int isAppeared[MAX_CHAR_NUMBER];
    for (int i = 0; i < MAX_CHAR_NUMBER; i++){
    	isAppeared[i] = 0;
    }

    int i = 0;
    int j = 0;
    int ret = 0;
    while (1) {
    	char ch = *(s + i);
    	//printf("ch=%c i=%d j=%d \n", ch, i, j);
    	if (ch == '\0'){
    		break;
    	}
    	
    	//printf("ch=%c index=%d appeared=%d \n", ch, ch - 0, isAppeared[ch - 0]);
    	if (isAppeared[ch - 0]){
    		
    		for (int k = j; k < i; k++){
    			if (*(s + k) == ch){
    				//printf("k=%d j=%d \n", k, j);
    				j = k + 1;
    				break;
    			} else {
    				isAppeared[*(s + k) - 0] = 0;
    			}
    		}
    	} else{
    		isAppeared[ch - 0] = 1;
    		if (i - j + 1 > ret){
    			ret = i - j + 1;
    		}
    	}
    	i++;
    }
    
    return ret;
}