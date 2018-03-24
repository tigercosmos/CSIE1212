// Example of memory leak (which doesn't crash)

#include <cstdlib>
#include <iostream>
using namespace std;		// makes std:: available

int main(){
	int *x=new int;
	cout << "x=" << x << endl;
	cout << "*x=" << *x << endl;
	*x=100;
	cout << "*x=" << *x << endl;
	x=0;	// The original value of x cannot be retrieved!
	// ...
	return EXIT_SUCCESS;
}
