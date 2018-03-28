// http://www.cplusplus.com/doc/tutorial/classes/
// member initialization
#include <iostream>
using namespace std;

class Circle {
		double radius;
	public:
		Circle(double r){radius=r;} 
		double area() {return radius*radius*3.14159265;}
};

class Cylinder {
		Circle base;
		double height;
	public:
		Cylinder(double r, double h): base(r), height(h) {}	// initializer list, see page 39 of the textbook
		double volume() {return base.area()*height;}
};

int main () {
	Circle A(10);
	cout << "A's area: " << A.area() << endl;
	Cylinder B(10,20);
	cout << "B's volume: " << B.volume() << endl;
	return 0;
}
