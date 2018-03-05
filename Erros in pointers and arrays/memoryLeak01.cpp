// Example of memory leak in a function (which doesn't crash)

#include <cstdlib>
#include <iostream>
using namespace std;		// makes std:: available

int func(){
	int *myVar=new int(26);
	return(*myVar);
	// No delete at all!
}

int main(){
	int x;
	for (int i=0; i<10; i++){
		x=func();
		cout << "x = " << x << endl;
	}
	return EXIT_SUCCESS;
}
