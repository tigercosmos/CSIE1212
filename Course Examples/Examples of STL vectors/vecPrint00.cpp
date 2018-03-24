// Vec print using ostream_iterator
#include <iostream>     // std::cout
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
using namespace std;

int main () {
	vector<int> myvector;
	for (int i=0; i<10; ++i) myvector.push_back(i);

	ostream_iterator<int> vecOutput(cout, " ");
	copy(myvector.begin(), myvector.end(), vecOutput); cout<<endl;

	return 0;
}