// http://www.cplusplus.com/doc/tutorial/classes/
// classes and uniform initialization
#include <iostream>
using namespace std;

class Circle {
	double radius;
	public:
		Circle(double r) { radius=r; }
		double circum() { return 2*3.14159265*radius; }
};

int main () {
	Circle A(10.0);		// functional form
	Circle B=10.0;		// assignment init.
	Circle C{10.0};		// uniform init. (To compile: g++ constructor01.cpp -std=c++11 -o constructor01.exe)
	Circle D={10.0};	// POD-like      (To compile: g++ constructor01.cpp -std=c++11 -o constructor01.exe)

	cout << "A's circumference: " << A.circum() << endl;
	cout << "B's circumference: " << B.circum() << endl;
	cout << "C's circumference: " << C.circum() << endl;
	cout << "D's circumference: " << D.circum() << endl;
	return 0;
}
