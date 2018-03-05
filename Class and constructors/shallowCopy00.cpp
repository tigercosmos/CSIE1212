// Demo of shallow copy 
#include <cstdlib>
#include <iostream>
using namespace std;

class myVec {
	public:
		myVec(int n){size=n; data=new int[size];};
		myVec(){size=10; data=new int[size];};
		~myVec(){delete [] data;};
		void print();	// Print data
		int *data;
		int size;
};

// You need to uncomment the following lines (and change line 10) to make the program error-free!
//myVec::~myVec(){
//	if (data!=NULL){
//		delete [] data;
//		data=NULL;
//	}
//};

void myVec::print(){
	cout << "[";
	for (int i=0; i<size; i++)
		cout << data[i] << " ";
	cout << "]" << endl;
}

int main(){
	myVec a(5);
	myVec b=a;

	cout << "Address of a.data: " << a.data << endl;
	cout << "Address of b.data: " << b.data << endl;
	a.data[0]=2;
	cout << "a.data[0]=2 ==>" << endl; 
	cout << "a: "; a.print();
	cout << "b: "; b.print();
	b.data[1]=4;
	cout << "b.data[1]=4 ==>" << endl;
	cout << "a: "; a.print();
	cout << "b: "; b.print();

	cout << "Last line of code..." << endl;
	return EXIT_SUCCESS;
}
