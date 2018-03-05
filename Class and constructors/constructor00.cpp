// overloading class constructors
#include <iostream>
using namespace std;

class Rectangle {
	private:					// Optional
		int width, height;		// Properties, or member variables
	public:
		Rectangle();			// Constructor (defined below, based on function overloading)
		Rectangle(int, int);	// Constructor (defined below, based on function overloading)
		~Rectangle(){}			// Destructor
		int area() {return (width*height);}		// Method, or member function
};

Rectangle::Rectangle() {
	width=5;
	height=5;
}

Rectangle::Rectangle(int a, int b) {
	width=a;
	height=b;
}

int main () {
	Rectangle A(3,4);
	Rectangle B;
	cout << "A's area: " << A.area() << endl;
	cout << "B's area: " << B.area() << endl;
	return 0;
}
