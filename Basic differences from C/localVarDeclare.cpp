// In C++, local variables can be created at any position in the code.
// Defining local variables when they are needed tends to produce more readable code than defining them at the beginning of a function.

#include <iostream>
using namespace std;

int main() {
	for (int i=0; i<5; i++)
	//	printf("%d\n", i);
		cout << i << endl;
	return (0);
}
