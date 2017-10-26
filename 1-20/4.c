#include <stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    //firstly, we can figure out the median's index by nums1Size and nums2Size
    int isOdd = (nums1Size + nums2Size) % 2;
    int medianIndexNumber = (nums1Size + nums2Size) / 2;
    int i = 0;
    int j = 0;
    int smallIndex = 0;
    int ret = 0;

    while (smallIndex <= medianIndexNumber){
    	//choose a number from two arrays
    	int chooceNum;
    	if (i < nums1Size){
    		chooceNum = *(nums1 + i);
    		if (j < nums2Size){
    			if (*(nums2 + j) < chooceNum){
    				chooceNum = *(nums2 + j);
    				j++;
    			} else {
    				i++;
    			}
    		} else{
    			i++;
    		}
    	} else {
    		chooceNum = *(nums2 + j);
    		j++;
    	}
    	if ((isOdd) && (smallIndex == medianIndexNumber)){
    		return (double)chooceNum;
    	} else if (!isOdd){
    		if (smallIndex == medianIndexNumber - 1){
    			ret = chooceNum;
    		}
    		if (smallIndex == medianIndexNumber){
    			return (((double)ret + (double)chooceNum) / 2);
    		}
    	}
    	smallIndex++;
    }
    return 0;
}

double min(int a, int b){
	if (a > b){
		return (double)b;
	} else {
		return (double)a;
	}
}

double max(int a, int b){
	if (a > b){
		return (double)a;
	} else {
		return (double)b;
	}
}

double findMedianSortedArray(int* nums, int numsSize){
	if (numsSize == 0){
		return 0;
	}
	int mid = numsSize / 2;
	if (numsSize % 2 ==0){
		return ((double)*(nums + mid - 1) + (double)*(nums + mid)) / 2;
	} else{
		return (double)*(nums + mid);
	}
}

double findMedianSortedArrays2(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	if (nums1Size == 0){
		return findMedianSortedArray(nums2, nums2Size);
	}
	if (nums2Size == 0){
		return findMedianSortedArray(nums1, nums1Size);
	}

	//binary search
	int leftSize = (nums1Size + nums2Size) / 2;
	int l = 0;
	if (leftSize - nums2Size > l) {
		l = leftSize - nums2Size;
	}
	int r = leftSize;
	if (nums1Size < r){
		r = nums1Size;
	}
	int nums1LeftSize;
	int nums2LeftSize;

	while (l <= r){
		nums1LeftSize = (l + r) / 2;
		nums2LeftSize = leftSize - nums1LeftSize;


		printf("Times: nums1LeftSize:%d nums2LeftSize:%d \n", nums1LeftSize, nums2LeftSize);


		if (nums1LeftSize != 0 && nums2LeftSize != nums2Size){
			if (*(nums1 + nums1LeftSize - 1) > *(nums2 + nums2LeftSize)){
				r = nums1LeftSize - 1;
				continue;
			}
		}

		if (nums1LeftSize == 0) {
			if (*(nums2 + nums2LeftSize - 1) > *(nums1 + nums1LeftSize)){
				l = nums1LeftSize + 1;
				continue;
			}
		}

		if (nums1LeftSize != nums1Size && nums2LeftSize != 0){
			if (*(nums2 + nums2LeftSize - 1) > *(nums1 + nums1LeftSize)){
				//turn right
				l = nums1LeftSize + 1;
				continue;
			}
		}

		if (nums2LeftSize == 0) {
			if (*(nums1 + nums1LeftSize - 1) > *(nums2 + nums2LeftSize)){
				r = nums1LeftSize - 1;
				continue;
			}
		}
		
		//printf("nums1LeftSize:%d \n", nums1LeftSize);
		break;
	}


	double rightMinValue;
	double leftMaxValue;

	if (nums1LeftSize == nums1Size){
		rightMinValue = (double)*(nums2 + nums2LeftSize);
	} else if (nums2LeftSize == nums2Size){
		rightMinValue = (double)*(nums1 + nums1LeftSize);
	} else {
		printf("nums2LeftSize:%d, value: %d\n", nums2LeftSize, *(nums2 + nums2LeftSize));
		rightMinValue = min(*(nums1 + nums1LeftSize), *(nums2 + nums2LeftSize));
	}
	printf("nums1LeftSize:%d nums2LeftSize:%d rightMinValue:%f \n", nums1LeftSize, nums2LeftSize, rightMinValue);


	if ((nums1Size + nums2Size) % 2 == 1){
		return rightMinValue;
	} else{
		if (nums1LeftSize == 0){
			leftMaxValue = (double)*(nums2 + nums2LeftSize - 1);
		} else if (nums2LeftSize == 0){
			leftMaxValue = (double)*(nums1 + nums1LeftSize - 1);
		} else {
			leftMaxValue = max(*(nums2 + nums2LeftSize - 1), *(nums1 + nums1LeftSize - 1));
		}
		return (leftMaxValue + rightMinValue) / 2;
	}

    return 0;
}



int main(){
	int nums1[2] = {1, 3};
	int nums2[1] = {2};
	printf("ret=%f \n", findMedianSortedArrays2(nums1, 2, nums2, 1));

	int nums3[2] = {1, 2};
	int nums4[2] = {3, 4};
	printf("ret=%f \n", findMedianSortedArrays2(nums3, 2, nums4, 2));

	int nums5[0] = {};
	int nums6[2] = {3, 4};
	printf("ret=%f \n", findMedianSortedArrays2(nums6, 2, nums5, 0));

	int nums7[5] = {1, 2, 3, 4, 5};
	int nums8[5] = {6, 7, 8, 9, 10};
	printf("ret=%f \n", findMedianSortedArrays2(nums7, 5, nums8, 5));

	int nums9[1] = {1};
	int nums10[2] = {2, 3};
	printf("ret=%f \n", findMedianSortedArrays2(nums9, 1, nums10, 2));

	int nums11[2] = {2, 3};
	int nums12[1] = {1};
	printf("ret=%f \n", findMedianSortedArrays2(nums11, 2, nums12, 1));

	int nums13[4] = {2, 3, 4, 5};
	int nums14[1] = {1};
	printf("ret=%f \n", findMedianSortedArrays2(nums13, 4, nums14, 1));
}