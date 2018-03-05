#include <stdio.h>
#include <iostream>	// A "preprocessor" directive that tells the compiler to put code from the header "iostream" into our program before creating the executable
using namespace std;	// To use a group of functions that are part of the standard library "std".
 
int main() {
	int x=100;
	printf("This printing is based on C-style printf()!\n");
	cout << "This printing is based on C++ iostream!\n";
	cout << x << endl;
}
