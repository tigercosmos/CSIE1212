// C++ allows us to define several functions with the same name, but with different argument lists, to perform different actions.

#include <iostream>
using namespace std;

void show(int value){
	cout << "Integer: " << value << endl;
}

void show(double value){
	cout << "Double: " << value << endl;
}

void show(const char *value){
	cout << "String: " << value << endl;
}

int main(){
	show(12);
	show(3.1415);
	show("Hello World!\n");
	return (0);
}
