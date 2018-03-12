// bad_alloc standard exception
#include <iostream>
#include <exception>
using namespace std;

int main () {
	try {
		int* myarray;
		for (int i=0; i<10000; i++){
			cout << "i= " << i << endl;
			myarray=new int[100000000];
		}
	} catch (exception& e){
		cout << "Standard exception: " << e.what() << endl;
	}
	return 0;
}
