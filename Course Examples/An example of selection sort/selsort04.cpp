#include <iostream>
using namespace std;

typedef struct {
	int hw1;
	int hw2;
} record;

bool smaller(record& first, record& second){
	return (first.hw1 < second.hw1);
}

int getMinPos1(record arr[], int len){
	int minpos = 0;
	for(int i=1;i<len;i++){
		if (smaller(arr[i], arr[minpos]))
			minpos = i;
	}
	return minpos;
}

void swap(record& a, record& b){
	record tmp = a;
	a = b;
	b = tmp;
}

void selsort1(record arr[], int len){
	for(int i=0;i<len;i++){
		int min = i + getMinPos1(&arr[i], len-i);
		swap(arr[i], arr[min]);
	}
}

int main(){
	record arr[] = {{3, 6}, {2, 7}, {5, 8}, {9, 4}, {10, 1}};

	selsort1(arr, 5);
	for(int i=0;i<5;i++)
		printf("{%d, %d} ", arr[i].hw1, arr[i].hw2);
	printf("\n");
}
