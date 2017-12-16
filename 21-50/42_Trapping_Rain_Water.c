#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b){
    if (a < b){
        return a;
    } else {
        return b;
    }
}

int trap(int* height, int heightSize) {
	if (heightSize < 2){
		return 0;
	}
	int count = 0;

	//Find the first left bound
	int i = 0;
	int leftHeight = 0;
	while ((height[i] >= leftHeight) && (i < heightSize)){
        leftHeight = height[i];
		i++;
	}
    if (i == heightSize){
    	return 0;
    } else {
    	i--;
    }

    //Find the first right bound
    int j = heightSize - 1;
	int rightHeight = 0;
    //printf("i=%d, j=%d\n", i, j);
	while ((height[j] >= rightHeight) && (j > i)){
        rightHeight = height[j];
		j--;
	}
    if (j == i){
    	return 0;
    } else {
    	j++;
    }

    int total = 0;
   
    //Try to find right bound
    int k = i + 1;
    int tempContain = 0;
    while (k <= j){
        printf("i=%d, j=%d, k=%d, tempContain=%d\n", i, j, k, tempContain);
    	if (height[k] < height[i]){
    		tempContain += height[k];
    		k++;
    		continue;
    	} else {
    		//Sum the trapped water between [i + 1, k - 1]
    		total += (k - i - 1) * (height[i]) - tempContain;
    		tempContain = 0;
    		i = k;
    		k++;

    	}
    }

    //Try to find left bound
    k = j - 1;
    tempContain = 0;
    while (k >= i){
        printf("i=%d, j=%d, k=%d, tempContain=%d\n", i, j, k, tempContain);
        if (height[k] < height[j]){
            tempContain += height[k];
            k--;
            continue;
        } else {
            //Sum the trapped water between [k + 1, j - 1]
            total += (j - k - 1) * (height[j]) - tempContain;
            tempContain = 0;
            j = k;
            k--;
        }
    }
    return total;
}

int main(){
	int a[] = {1, 2, 1};
	printf("%d\n", trap(a, 3));

	int b[] = {5,4,1,2};
	printf("%d\n", trap(b, 4));

    int c[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    printf("%d\n", trap(c, 12));

    int d[] = {2, 0, 2};
    printf("%d\n", trap(d, 3));
}
