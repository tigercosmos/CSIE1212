// Sparse array example: (why hold space for thousands of elements when all we have is five)
// http://www.yolinux.com/TUTORIALS/CppStlMultiMap.html

#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(){
	map<int, string> employeeList;
	employeeList[5234] = "Mike C.";
	employeeList[3374] = "Charlie M.";
	employeeList[1923] = "David D.";
	employeeList[7582] = "John A.";
	employeeList[5328] = "Peter Q.";

	cout << "employeeList[3374]=" << employeeList[3374] << endl;
	cout << "Map size: " << employeeList.size() << endl;
	for(map<int,string>::iterator i=employeeList.begin(); i!=employeeList.end(); ++i)
		cout << (*i).first << ": " << (*i).second << endl;
}