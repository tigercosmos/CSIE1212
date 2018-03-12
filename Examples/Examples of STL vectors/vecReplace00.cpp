#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void main(){
	ostream_iterator<string> output(cout, " ");
	vector<string> fruits;
	fruits.push_back("cherry");
	fruits.push_back("apple");
	fruits.push_back("peach");
	fruits.push_back("plum");
	fruits.push_back("apple");

	cout << "Before:" << endl;
	copy(fruits.begin(), fruits.end(), output); cout<<endl;
	replace(fruits.begin(), fruits.end(), string("apple"), string("orange"));
	cout << "After:" << endl;
	copy(fruits.begin(), fruits.end(), output); cout<<endl;
}