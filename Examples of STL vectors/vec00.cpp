// Basic use of STL vector
#include <iostream>
#include <vector>
using namespace std;
#define PRINT(x)	{cout << #x << " = " << x << endl;}

// Print a vec
template <class T>
void vecPrint(vector<T> vec, char *vecName){
	typename vector<T>::iterator i;
	cout << vecName << " = ";
	for (i=vec.begin(); i!=vec.end(); i++)
		cout << *i << " ";
	cout << endl;
}

int main(){
	// Create a vector, initialized by an array
	int cArray[] = {9,3,7,8,8,6,8,2,2,5};
	int vecLen = sizeof(cArray)/sizeof(int);
	PRINT(vecLen);
	vector<int> vec1(cArray, cArray+vecLen);
	vecPrint(vec1, "vec1");
	// Add more element
	vec1.push_back(10);
	vec1.push_back(20);
	vecPrint(vec1, "vec1");
	// Delete some elements
	vec1.resize(3);			// Keep the first 3 elements
	vecPrint(vec1, "vec1");

	vector<double> vec2;
	vec2.push_back(1.25);
	vec2.push_back(3.1415);
	vec2.push_back(2.718281828);
	vecPrint(vec2, "vec2");
	vec2.resize(6, 1.4);	// Expand to 5 elements, with the added elements being 1.4
	vecPrint(vec2, "vec2");
	return 0;
}