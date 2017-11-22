#include <stdio.h>
#include <stdlib.h>

char* convert(char* s, int numRows) {
    if (numRows == 1){
        return s;
    }
    int length = 0;
    while (*(s + length) != '\0'){
        length++;
    }
    char* ret = (char *)malloc(length + 1);
    int internal = numRows * 2 - 2;
    int count = 0;
    for (int i = 0; i < numRows; i++){
        int j = 0;
        while (1){
            if (i + internal * j < length){
                ret[count] = *(s + i + internal * j);
                count++;
            } else {
                break;
            }

            if ((i != 0) && (i != numRows - 1)){
                int k = 2 * numRows - i - 2;
                if (k + internal * j < length){
                    ret[count] = *(s + k + internal * j);
                    count++;
                } else {
                    break;
                }
            }
            j++;
        }
    }
    ret[length] = '\0';
    return ret;
}

int main(){
    char* s1 = "PAYPALISHIRING";
    printf("ret=%s \n\n", convert(s1, 3));

    char* s0 = "A";
    printf("ret=%s \n\n", convert(s0, 3));

   
    char* s2 = "";
    printf("ret=%s \n\n", convert(s2, 3));

    /*
    char* s3 = "afkkkkkkkkf";
    printf("ret=%s \n\n", longestPalindromeByManacher(s3));

    char* s4 = "dddddddd";
    printf("ret=%s \n\n", longestPalindromeByManacher(s4));
    */
}