// Use of size(), capacity() and max_size()
#include <iostream>
#include <vector>
using namespace std;

int main (){
	vector<int> vec(1000);
	
	cout << "Originally:" << endl;
	cout << "\tsize: " << (int) vec.size() << '\n';
	cout << "\tcapacity: " << (int) vec.capacity() << '\n';
	cout << "\tmax_size: " << (int) vec.max_size() << '\n';

	// set some content in the vector:
	for (int i=0; i<100; i++) vec.push_back(i);
	cout << "After 100 push_back:" << endl;
	cout << "\tsize: " << (int) vec.size() << '\n';
	cout << "\tcapacity: " << (int) vec.capacity() << '\n';
	cout << "\tmax_size: " << (int) vec.max_size() << '\n';

	// Reserve some more space...
	vec.reserve(5000);
	cout << "After reserve 5000 elements:" << endl;
	cout << "\tsize: " << (int) vec.size() << '\n';
	cout << "\tcapacity: " << (int) vec.capacity() << '\n';
	cout << "\tmax_size: " << (int) vec.max_size() << '\n';

	// Reserve a lot more space...
	cout << "Error occurs if you want to reserve more than vec.max_size()..." << endl;
	vec.reserve(vec.max_size()+1);

	return 0;
}