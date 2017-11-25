#include <stdio.h>
#include <stdlib.h>

int reverse(int x) {
    int record[32];
    int isNegative = 0;
    if (x < 0){
        isNegative = 1;
        x = -x;
    }

    int index = 0;
    while ((x != 0) && (x % 10 == 0)){
        x = x / 10;       
    }
    if (x == 0){
        return 0;
    }
    while (x != 0){
        int remain = x % 10;
        if (remain < 0){
            remain = -remain;
        }
        record[index] = remain;
        index++;
        x = x / 10;
    }
    //printf("index=%d \n", index);
    long ret = 0;
    for (int i = 0; i < index; i++){
        ret = ret * 10 + record[i];
        //printf("record[%d]=%d, ret=%ld \n", i, record[i], ret);
    }
    //printf("ret=%ld \n", ret);

    if (ret > (2147483647)){
        return 0;
    }
    if (isNegative){
        ret = -ret;
    }

    return (int)ret;
}

int isPalindrome(int x) {
    if (x < 0){
        return 0;
    }
    int y = reverse(x);
    printf("x=%d and reverse(x)=%d \n", x, y);
    if (x == y){
        return 1;
    } else {
        return 0;
    }
}

int main(){
    int s1 = 0;
    printf("ret=%d \n", isPalindrome(s1));

    int s2 = 1233230000;
    printf("ret=%d \n", isPalindrome(s2));

    int s3 = 123454321;
    printf("ret=%d \n", isPalindrome(s3));

    int s4 = -2147447412;
    printf("ret=%d \n", isPalindrome(s4));

    int s5 = 121;
    printf("ret=%d \n", isPalindrome(s5));
}