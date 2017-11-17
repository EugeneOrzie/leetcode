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

/*
* preprocess s by inserting #
*/
char* preprocess(char* s, int length, int plength){
	char * ps = (char *)malloc(plength + 1);
	int i = 0;
	while (i < length){
		*(ps + i * 2) = '#';
		*(ps + i * 2 + 1) = *(s + i);
		i++;
	}
	*(ps + plength - 1) = '#';
	*(ps + plength) = '\0';
	return ps;
}

char* longestPalindromeByManacher(char* s) {
	int length = 0;
	int plength = 0;
	while (*(s + length) != '\0'){
		length++;
	}

	if (length == 0){
		return s;
	}

	plength = length * 2 + 1;
	char* ps = preprocess(s, length, plength);

	int p[plength];
	p[0] = 0;
	int m = 0;
	int r = 0;
	int maxIndex = 0;
	int maxLength = 0;

	for (int i = 1; i < plength; i++){
		//core code in Manacher's Algorithm
		if (i > r){
			//surpass the right border, recalculate the match
			int j = 0;
			while ((i - j >= 0) && (i + j < plength) && *(ps + i + j) == *(ps + i - j)){
				j++;
			}
			j--;
			p[i] = j;
			printf("j=%d p[%d]=%d\n", j, i, p[i]);
		} else {
			int mirrorIndex = 2 * m - i;
			if (p[mirrorIndex] < r - i){
				p[i] = p[mirrorIndex];
				continue;
			} else {
				int j = r - i;
				while ((i - j >= 0) && (i + j < plength) && *(ps + i + j) == *(ps + i - j)){
					j++;
				}
				j--;
				p[i] = j;
			}
		}

		if (p[i] > maxLength){
			maxLength = p[i];
			maxIndex = i;
		}
		if (i + p[i] > r){
			m = i;
			r = i + p[i];
		}
		printf("m=%d r=%d p[%d]=%d\n", m, r, i, p[i]);
	}
	printf("ps=%s maxIndex=%d maxLength=%d\n", ps, maxIndex, maxLength);

	int realIndex = (maxIndex - maxLength) / 2;
	char* retStr = (char*)malloc(maxLength + 1);
	for (int i = 0; i < maxLength; i++){
		*(retStr + i) = *(s + realIndex + i);
	}
	*(retStr + maxLength) = '\0';
	return retStr;
}

int main(){
	char* s0 = "babadada";
	printf("ret=%s \n\n", longestPalindromeByManacher(s0));

	char* s1 = "esbtzjaaijqkgmtaajpsdfiqtvxsgfvijpxrvxgfumsuprzlyvhclgkhccmcnquukivlpnjlfteljvykbddtrpmxzcrdqinsnlsteonhcegtkoszzonkwjevlasgjlcquzuhdmmkhfniozhuphcfkeobturbuoefhmtgcvhlsezvkpgfebbdbhiuwdcftenihseorykdguoqotqyscwymtjejpdzqepjkadtftzwebxwyuqwyeegwxhroaaymusddwnjkvsvrwwsmolmidoybsotaqufhepinkkxicvzrgbgsarmizugbvtzfxghkhthzpuetufqvigmyhmlsgfaaqmmlblxbqxpluhaawqkdluwfirfngbhdkjjyfsxglsnakskcbsyafqpwmwmoxjwlhjduayqyzmpkmrjhbqyhongfdxmuwaqgjkcpatgbrqdllbzodnrifvhcfvgbixbwywanivsdjnbrgskyifgvksadvgzzzuogzcukskjxbohofdimkmyqypyuexypwnjlrfpbtkqyngvxjcwvngmilgwbpcsseoywetatfjijsbcekaixvqreelnlmdonknmxerjjhvmqiztsgjkijjtcyetuygqgsikxctvpxrqtuhxreidhwcklkkjayvqdzqqapgdqaapefzjfngdvjsiiivnkfimqkkucltgavwlakcfyhnpgmqxgfyjziliyqhugphhjtlllgtlcsibfdktzhcfuallqlonbsgyyvvyarvaxmchtyrtkgekkmhejwvsuumhcfcyncgeqtltfmhtlsfswaqpmwpjwgvksvazhwyrzwhyjjdbphhjcmurdcgtbvpkhbkpirhysrpcrntetacyfvgjivhaxgpqhbjahruuejdmaghoaquhiafjqaionbrjbjksxaezosxqmncejjptcksnoq";
	printf("ret=%s \n\n", longestPalindromeByManacher(s1));

	char* s2 = "cbbd";
	printf("ret=%s \n\n", longestPalindromeByManacher(s2));

	char* s3 = "afkkkkkkkkf";
	printf("ret=%s \n\n", longestPalindromeByManacher(s3));

	char* s4 = "dddddddd";
	printf("ret=%s \n\n", longestPalindromeByManacher(s4));
}