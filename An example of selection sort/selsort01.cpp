#include <iostream>
using namespace std;

int getMinPos(int arr[], int len){
	int minpos = 0;
	for(int i=1;i<len;i++){
		if (arr[i] < arr[minpos])
			minpos = i;
	}
	return minpos;
}

void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void selsort(int arr[], int len){
	for(int i=0;i<len;i++){
		int min = i + getMinPos(&arr[i], len-i);
		swap(&arr[i], &arr[min]);
	}
}

int main(){
	int arr[] = {3, 6, 2, 7, 5, 8, 9, 4, 10, 1};

	selsort(arr, 10);
	for(int i=0;i<10;i++)
		printf("%d ", arr[i]);
	printf("\n");
}
