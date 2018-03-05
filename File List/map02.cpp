// Different ways of assigning Map container contents
// http://www.yolinux.com/TUTORIALS/CppStlMultiMap.html

#include <string>
#include <iostream>
#include <map>
#include <utility>
using namespace std;

// Print a map
template <class T, class T2>
void mapPrint(map<T, T2> myMap, char *mapName){
	typename map<T, T2>::iterator i;
	cout << "Entries of " << mapName << ":" << endl;
	for (i=myMap.begin(); i!=myMap.end(); i++)
		cout << "\t" << i->first << "==>" << i->second << endl;
}
 
int main(){
	map<string, int> employeeList;
	// 1) Assignment using array index notation
	employeeList["Mike C."] = 5234;
	employeeList["Charlie M."] = 3374;
	// 2) Assignment using member function insert() and STL pair
	employeeList.insert(pair<string,int>("David D.", 1923));
	// 3) Assignment using member function insert() and "value_type()"
	employeeList.insert(map<string,int>::value_type("John A.", 7582));
	// 4) Assignment using member function insert() and "make_pair()"
	employeeList.insert(make_pair("Peter Q.", 5328));
	cout << "employeeList.size() = " << employeeList.size() << endl;
	mapPrint(employeeList, "employeeList");
}
