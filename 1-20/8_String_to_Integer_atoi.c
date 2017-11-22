#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int myAtoi(char* str) {
    char* s = str;
    while (isspace(*s)) {
        s++;
    }
    int hasSign = 0;
    int isNegative = 0;
    long number = 0;
    while (1){
        char ch = *s;
        if ((ch == '\0') || isspace(ch)){
            break;
        }
        s++;
        if ((ch == '+') || (ch == '-')){
            if (hasSign){
                return 0;
            }
            if (ch == '-'){
                isNegative = 1;
            }
            hasSign = 1;
            continue;
        }
        int ascilNum = ch - '0';
        //printf("ascilNum=%d ch=%c\n", ascilNum, ch);
        if ((ascilNum >= 0) && (ascilNum <= 9)){
            number = number * 10 + ascilNum;
            if (isNegative && number > 2147483648){
                return -2147483648;
            } else if (!isNegative && number >= 2147483648){
                return 2147483647;
            }
        } else {
            break;
        }
    }
    if (isNegative){
        number = -number;
    }
    return (int)number;
}

int main(){
    char* s1 = "102323";
    printf("ret=%d \n", myAtoi(s1));

    char* s2 = "1233230000";
    printf("ret=%d \n", myAtoi(s2));

    char* s3 = "    2147483648";
    printf("ret=%d \n", myAtoi(s3));

    char* s4 = "    -2147483648 fsf";
    printf("ret=%d \n", myAtoi(s4));

    char* s5 = "sdfds";
    printf("ret=%d \n", myAtoi(s5));

    char* s6 = "  -0012a42";
    printf("ret=%d \n", myAtoi(s6));
}