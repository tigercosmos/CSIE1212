// Out-of-bound array access

#include <cstdlib>
#include <iostream>
using namespace std;		// makes std:: available

int main(){
	int n=10;
	int *myVec=new int[n];
	for (int i=0; i<10000; i++){	// Infinite loop
		myVec[i]=i*i;
		cout << "i=" << i << endl;
	}
	delete [] myVec;
	return EXIT_SUCCESS;
}
