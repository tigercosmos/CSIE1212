// Example of operator overloading
// http://www.cplusplus.com/doc/tutorial/templates/
#include <iostream>
using namespace std;

class cVec {
	public:
		float x, y;
		cVec () {};				// Why do we need to keep this line?
	//	cVec (int a,int b) : x(a), y(b) {}	// Constructor with member initialization
		cVec (int a,int b) {x=a; y=b;}
		cVec operator+(const cVec&);
		cVec operator-(const cVec&);
		cVec operator*(const cVec&);
		cVec operator/(const cVec&);
		void print(){cout<<"["<<x<<", "<<y<<"]\n";};
};

cVec cVec::operator+(const cVec& b) {
	cVec out;
	out.x=x+b.x;
	out.y=y+b.y;
	return out;
}

cVec cVec::operator-(const cVec& b) {
	cVec out;
	out.x=x-b.x;
	out.y=y-b.y;
	return out;
}

cVec cVec::operator*(const cVec& b) {
	cVec out;
	out.x=x*b.x-y*b.y;
	out.y=x*b.y+y*b.x;
	return out;
}

cVec cVec::operator/(const cVec& b) {
	cVec out;
	float denominator=b.x*b.x+b.y*b.y;
	out.x=(x*b.x+y*b.y)/denominator;
	out.y=(y*b.x-x*b.y)/denominator;
	return out;
}

int main () {
	cVec a(3,1);
	cVec b(1,2);
	cVec c;
	cout<<"a="; a.print();
	cout<<"b="; b.print();
	cout << "Operator overloading:" << endl;
	c=a+b; cout<<"a+b="; c.print();
	c=a-b; cout<<"a-b="; c.print();
	c=a*b; cout<<"a*b="; c.print();
	c=a/b; cout<<"a/b="; c.print();
	cout << "Old way to use the operators:" << endl;
	c=a.operator+(b); cout<<"a.operator+(b)="; c.print();
	c=a.operator-(b); cout<<"a.operator-(b)="; c.print();
	c=a.operator*(b); cout<<"a.operator*(b)="; c.print();
	c=a.operator/(b); cout<<"a.operator/(b)="; c.print();

	return 0;
}
