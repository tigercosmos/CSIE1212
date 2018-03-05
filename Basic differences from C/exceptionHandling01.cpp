#include <iostream>
using namespace std;

double division(int a, int b){
	if (b==0)
		throw "Division by zero in division()!";
	return a/b;
}

int main (){
	int x = 2;
	int y = 0;
	try {
		double z = division(x, y);
		cout << z << endl;
	} catch (const char* msg) {
		cerr << "My error message: " << msg << endl;
	}
	return 0;
}
