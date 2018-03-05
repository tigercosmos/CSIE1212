#include <iostream>
using namespace std;

class record {
public: 
	int hw1;
	int hw2;

	bool operator<(const record& second){
		return (hw1 < second.hw1);	// same as (*this).hw1 < second.hw1
	}
};

template <class T>
int getMinPos(T arr[], int len){
	int minpos = 0;
	for(int i=1;i<len;i++){
		if (arr[i] < arr[minpos])
			minpos = i;
	}
	return minpos;
}

template <class T>
void swap(T& a, T& b){
	T tmp = a;
	a = b;
	b = tmp;
}

template <class T>
void selsort(T arr[], int len){
	for(int i=0;i<len;i++){
		int min = i + getMinPos(&arr[i], len-i);
		swap(arr[i], arr[min]);
	}
}

int main(){
	record arr[] = {{3, 6}, {2, 7}, {5, 8}, {9, 4}, {10, 1}};

	selsort(arr, 5);

	for(int i=0;i<5;i++)
		printf("{%d, %d} ", arr[i].hw1, arr[i].hw2);
	printf("\n");

	int arrint[] = {3, 6, 2, 7, 5, 8, 9, 4, 10, 1};

	selsort(arrint, 10);

	for(int i=0;i<10;i++)
		printf("%d ", arrint[i]);
	printf("\n");

}
