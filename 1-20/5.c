#include <stdio.h>
#include <stdlib.h>

char* longestPalindrome(char* s) {
	int is_palindromic[1000][1000];
	//Firstly, we need to get the length of s
	int length = 0;
	while (*(s + length) != '\0'){
		length++;
	}

	if (length == 0){
		return s;
	}

	//Initial
	for (int i = 0; i < length; i++){
		for (int j = i; j < length; j++){
			if (j == i){
				is_palindromic[i][j] = 1;
			} else {
				is_palindromic[i][j] = 0;
			}
		}
	}

	int max_length = 0;
	//Calculate is_palindromic[i][j]
	for (int l = 1; l < length; l++){
		int has_palindrome = 0;
		for (int i = 0; i < length; i++){

			int j = i + l;
			if (j >= length){
				break;
			}
			if (j == i + 1){
				is_palindromic[i][j] = (*(s + i) == *(s + j));
			} else {
				is_palindromic[i][j] = is_palindromic[i + 1][j - 1] & (*(s + i) == *(s + j));
			}
			if (is_palindromic[i][j]){
				has_palindrome = 1;
			}
		}
		//printf("length=%d and has_palindrome=%d \n", l, has_palindrome);
		if (has_palindrome){
			max_length = l;
		} 
	}

	//Find the max
	for (int i = 0; i < length; i++){
		int j = i + max_length;
		if (j > length){
			break;
		}
		if (is_palindromic[i][j]){
			//find one, then return
			char * ret_str = (char *)malloc(max_length + 2);
			for (int k = 0; k < max_length + 1; k++){
				ret_str[k] = *(s + i + k);
			}
			ret_str[max_length + 1] = '\0';
			return ret_str;
		}
	}

	return "Something Wrong";
}

int main(){
	char* s1 = "babad";
	printf("ret=%s \n", longestPalindrome(s1));

	char* s2 = "cbbd";
	printf("ret=%s \n", longestPalindrome(s2));

	char* s3 = "";
	printf("ret=%s \n", longestPalindrome(s3));

	char* s4 = "dddddddd";
	printf("ret=%s \n", longestPalindrome(s4));
}