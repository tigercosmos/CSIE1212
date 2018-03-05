#include <iostream>
using namespace std;

// This is wrong way to swap a and b
void swap00(int a, int b){
	int tmp = a;
	a = b;
	b = tmp;
}

// C function to swap a and b
void swap01(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// C++ function to swap a and b
void swap02(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}

int main(){
	int x=3, y=5;
	printf("Originally, x=%d, y=%d\n", x, y);
	swap00(x, y);
	printf("After calling swap00(x, y), x=%d, y=%d.\n", x, y);
	swap01(&x, &y);
	printf("After calling swap01(&x, &y), x=%d, y=%d.\n", x, y);
	swap02(x, y);
	printf("After calling swap02(x, y), x=%d, y=%d.\n", x, y);
}
