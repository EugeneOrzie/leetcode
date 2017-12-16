#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b){
	if (a > b){
		return b;
	} else {
		return a;
	}
}

int maxArea(int* height, int heightSize) {
	if (heightSize < 2){
		return 0;
	}
    int maxContainer = 0;

    for (int i = 0; i < heightSize; i++){
    	for (int j = i + 1; j < heightSize; j++){
    		int temp = (j - i) * min(height[i], height[j]);
    		if (temp > maxContainer){
    			maxContainer = temp;
    		}
    	}
    }
    return maxContainer;
}

int maxArea1(int* height, int heightSize) {
	if (heightSize < 2){
		return 0;
	}
    int maxContainer = 0;
    int i = 0;
    int j = heightSize - 1;
    while (i < j){
    	int temp = (j - i) * min(height[i], height[j]);
    	if (temp > maxContainer){
    		maxContainer = temp;
    	}
    	if (height[i] > height[j]){
    		j--;
    	} else {
    		i++;
    	}
    }
    return maxContainer;
}

int main(){
	int a[] = {1, 2, 1};
	printf("%d\n", maxArea1(a, 3));

	int b[] = {1, 2, 4, 3};
	printf("%d\n", maxArea1(b, 4));
}