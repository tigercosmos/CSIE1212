#include <cstdlib>
#include <iostream>
using namespace std;
#include <string>
using std::string;

int main(){
	string author="Confucious";
	cout << "author = " << author << endl;
	string& penName=author;
	penName="James bond";
	cout << "author = " << author << endl;
	return EXIT_SUCCESS;
}
