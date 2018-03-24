// Default arguments are assigned by the compiler when the function is invoked without those arguments specified.
// Function may be defined with more than one default arguments.
// When arguments are omitted, they must be on the right-most side.
// Default arguments must be known by the compiler when the code is generated, which means the default arguments are usually presented in a header file.

#include <iostream>
using namespace std;

void showString(char *name, char *title="Mr."){
	cout << title << " " << name << endl;
}

int main(){
	showString("Obama");
	showString("Obama", "President");
	showString("Ouyang");
	showString("Ouyang", "Prof.");
	return 0;
}
