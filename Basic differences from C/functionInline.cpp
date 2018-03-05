// Inline functions: Faster, but make the executable bigger

#include <iostream>
using namespace std;

inline void hello() { 
	cout << "hello!" << endl;
}

int main() {
	hello(); //Call it like a normal function...
//	cin.get();
	return 0;
}
