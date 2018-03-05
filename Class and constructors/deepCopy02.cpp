// How to avoid shallow copy 
#include <cstdlib>
#include <iostream>
using namespace std;

class myVec {
	public:
		myVec(int n){size=n; data=new int[size];};
		myVec(){size=10; data=new int[size];};
		myVec(const myVec& a);		// copy constructor from a
		~myVec(){delete [] data;};
		myVec& operator=(const myVec& a);	// assignment operator from a
		void print();	// Print data
		int *data;
		int size;
};

void myVec::print(){
	cout << "[";
	for (int i=0; i<size; i++)
		cout << data[i] << " ";
	cout << "]" << endl;
}

// Copy constructor
myVec::myVec(const myVec& a) {	// copy constructor from a
	size = a.size;				// copy sizes
	data = new int[size];		// allocate new array
	for (int i=0; i<size; i++)	// copy the vector contents
		data[i]=a.data[i];
}

// Assignment operator
myVec& myVec::operator=(const myVec& a) {	// assignment operator from a
	if (this != &a) {						// avoid self-assignment
		delete [] data;						// delete old array
		size = a.size;						// set new size
		data = new int[size];				// allocate new array
		for (int i=0; i<size; i++)			// copy the vector contents
			data[i]=a.data[i];
	}
	return *this;
}

int main(){
	myVec a(5);
	myVec b=a;	// Copy constructor, same as "myVec b=myVec(a);"
	myVec c;
	c=a;		// Assignment operator
	a.data[0]=2;
	b.data[1]=4;
	c.data[2]=6;
	cout << "a: "; a.print();
	cout << "b: "; b.print();
	cout << "c: "; c.print();
	cout << a.data << endl;
	cout << b.data << endl;
	cout << c.data << endl;
	return EXIT_SUCCESS;
}
