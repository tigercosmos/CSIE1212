// On the use of a comparison function for map
// http://www.yolinux.com/TUTORIALS/CppStlMultiMap.html

#include <string>
#include <iostream>
#include <map>
#include <utility>
using namespace std;

// Print a map (Note this is different from the one used without a comparison function)
template <class T, class T2, class T3>
void mapPrint(map<T, T2, T3> myMap, char *mapName){
	typename map<T, T2>::iterator i;
	cout << "Entries of " << mapName << ":" << endl;
	for (i=myMap.begin(); i!=myMap.end(); i++)
		cout << "\t" << i->first << "==>" << i->second << endl;
}

struct strCompare{
	bool operator()(string const &a, string const &b){
		return(a>b);	// The default behavior is a<b
	}
};
 
int main(){
	map<string, int, strCompare> employeeList;
	// 1) Assignment using array index notation
	employeeList["Ron C."] = 5234;
	employeeList["Charlie M."] = 3374;
	employeeList["Johnson J."] = 3234;
	// 2) Assignment using member function insert() and STL pair
	employeeList.insert(pair<string,int>("David D.", 1923));
	// 3) Assignment using member function insert() and "value_type()"
	employeeList.insert(map<string,int>::value_type("John A.", 7582));
	// 4) Assignment using member function insert() and "make_pair()"
	employeeList.insert(make_pair("Peterson Q.", 5328));
	cout << "Map size: " << employeeList.size() << endl;
	mapPrint(employeeList, "employeeList");
}
