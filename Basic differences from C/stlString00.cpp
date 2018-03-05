#include <cstdlib>	// For EXIT_SUCCESS, etc
#include <iostream>
using namespace std;
#include <string>
using std::string;

int main(){
	string p="to be";
	string q="not "+p;
	string r = p + " or " + q;
	if (p>q)
		cout << r << std::endl;
	return EXIT_SUCCESS;
}
