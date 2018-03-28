#include <cstdlib>	// For EXIT_SUCCESS, etc
#include <iostream>
using namespace std;

int main(){
	double d1=3.2;
	double d2=3.99999;
	int i1 = static_cast<int>(d1);	// What's the difference between static_cast and dynnamic_cast?
	int i2 = static_cast<int>(d2);

	cout << "i1=" << i1 << endl;
	cout << "i2=" << i2 << endl;

	return EXIT_SUCCESS;
}
