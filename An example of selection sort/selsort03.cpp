#include <iostream>
using namespace std;

typedef struct {
	int hw1;
	int hw2;
} HW;

int getMinPos1(HW arr[], int len){
	int minpos = 0;
	for(int i=1;i<len;i++){
		if (arr[i].hw1 < arr[minpos].hw1)
			minpos = i;
	}
	return minpos;
}

void swap(HW &a, HW &b){
	HW tmp = a;
	a = b;
	b = tmp;
}

void selsort1(HW arr[], int len){
	for(int i=0;i<len;i++){
		int min = i + getMinPos1(&arr[i], len-i);
		swap(arr[i], arr[min]);
	}
}

int main(){
	HW arr[] = {{3, 6}, {2, 7}, {5, 8}, {9, 4}, {10, 1}};

	selsort1(arr, 5);
	for(int i=0;i<5;i++)
		printf("{%d, %d} ", arr[i].hw1, arr[i].hw2);
	printf("\n");
}
