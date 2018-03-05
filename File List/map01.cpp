// Basic use of STL vector

#include <iostream>
#include <string>
#include <map>
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
	map<string, char> gradeList;
	map<string, char>::iterator i;
	
	gradeList["John"] = 'B';
	gradeList["Mary"] = 'A';
	gradeList["Jacobi"] = 'C';
	gradeList["Helen"] = 'D';

	cout << "gradeList[\"Mary\"] = " << gradeList["Mary"] << endl;
	cout << "Map size = " << gradeList.size() << endl;
	
	gradeList.erase("Mary");
	cout << "gradeList.size() = " << gradeList.size() << endl;
//	cout << "gradeList[\"Mary\"] = " << gradeList["Mary"] << endl;	// Why?
//	cout << "gradeList.size() = " << gradeList.size() << endl;		// Why?
	
	i=gradeList.find("Jacobi");
	if(i==gradeList.end())
		cout << "Jacobi is not in the map!" << endl;
	else
		cout << i->first << " ==> " << i->second << endl;

	mapPrint(gradeList, "gradeList");

	return 0;
}
