// Example of memory leak in a function (which crashes soon)

#include <cstdlib>
#include <iostream>
using namespace std;		// makes std:: available

void func(){
	int n=100000000;
	int *myVec=new int[n];	// if n is too big, myVec is NULL
	for (int i=0; i<n; i++)
		myVec[i]=i*i;
//	delete [] myVec;
}

int main(){
	for (int i=0; i<20; i++){
		func();
		cout << "i=" << i << endl;
	}
	return EXIT_SUCCESS;
}
