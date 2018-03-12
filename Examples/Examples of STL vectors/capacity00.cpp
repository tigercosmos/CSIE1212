// Show how STL vectors perform memory allocation implicitly.
// capacity() is changed when the size of a vector is getting bigger.
// Note that different compilers will generate different execution results.

#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> vec;
	vec.reserve(100);		// Initial capacity is 100
	cout << "The capacity of vec is " << vec.capacity() << endl;
	cout << "The size of vec is " << vec.size() << endl;
	
	int currentCapacity=vec.capacity();
	for (int i=0; i<1000; i++){
		vec.push_back(i);
		if (vec.capacity()!=currentCapacity){
			cout << "Capacity changed from " << currentCapacity << " to " << vec.capacity() << " when i=" << i << ", size()=" << vec.size() << endl;
			currentCapacity=vec.capacity();
		}
	}
	cout << "The final capacity of vec is " << vec.capacity() << endl;
	
	return 0;
}