// Show how STL vectors perform memory allocation implicitly: capacity() is changed when the size of a vector is getting bigger.

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n=100;
	vector<int> v1, v2;
	vector<int>::size_type c;

	// Memory is reallocated  when the v1 grows bigger than its capacity
	cout << "Test on v1:" << endl;
	for (int i=0; i<2*n; i++) {
		c = v1.capacity();
		v1.push_back(i);
		if (c != v1.capacity()) {
			cout << "v1 grown from " << c << " to " << v1.capacity();
			cout << endl;
		}
	}

	// Reserve more contiguous memory for v2
	cout << "Test on v2:" << endl;
	v2.reserve(n);
	for (int i=0; i<4*n; i++) {
		c = v2.capacity();
		v2.push_back(i);
		if (c != v2.capacity()) {
			cout << "v2 grown from " << c << " to " << v2.capacity();
			cout << endl;
		}
	}

	return 0;
}