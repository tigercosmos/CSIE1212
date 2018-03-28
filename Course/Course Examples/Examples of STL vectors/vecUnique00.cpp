// Show the use of sort(), unique(), and erase()
// http://www.cplusplus.com/reference/algorithm/unique/?kw=unique

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Print a vec
template <class T>
void vecPrint(vector<T> vec, char *vecName){
	vector<T>::iterator iter;
	cout << vecName << " = ";
	for (iter=vec.begin(); iter!=vec.end(); iter++)
		cout << *iter << " ";
	cout << endl;
}

int main(){
	vector<string> x;
	x.push_back("ab");
	x.push_back("cd");
	x.push_back("ab");
	x.push_back("123");
	x.push_back("123");
	cout<< "Originally: "; vecPrint(x, "x");

	sort(x.begin(), x.end());
	cout << "After sort(): "; vecPrint(x, "x");
	cout << "x.size()=" << x.size() << endl;
	
	vector<string>::iterator endIndex=unique(x.begin(), x.end());
	cout << "After unique(): "; vecPrint(x, "x");	// Why the last element is missing?
	cout << "x.size()=" << x.size() << endl;
	
	x.erase(endIndex, x.end());		// Remove extra elements after unique()
//	x.resize(distance(x.begin(), endIndex));	// Another way to remove extra elements after unique()
	cout<< "After erase(): "; vecPrint(x, "x");
	cout << "x.size()=" << x.size() << endl;
		
	return 0;
}