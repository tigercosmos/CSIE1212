// C++ allows generic functions (or function templates)

#include <iostream>
using namespace std;

template <class T>
void show(T value){
	cout << "Input: " << value << endl;
}

int main(){
	show(12);
	show(3.1415);
	show("Hello World!\n");
	return (0);
}
