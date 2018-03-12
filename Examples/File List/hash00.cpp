// How to compile: g++ hash00.cpp -std=c++11 -O2 -o hash00

// http://en.cppreference.com/w/cpp/container/unordered_map
// https://zh.wikipedia.org/wiki/%E6%97%A0%E5%BA%8F%E5%85%B3%E8%81%94%E5%AE%B9%E5%99%A8_(STL)

#include <iostream>
#include <string>
#include <unordered_map>
 
int main(){
	// Create an unordered_map of three strings (that map to strings)
	std::unordered_map<std::string, std::string> u={{"RED","#FF0000"}, {"GREEN","#00FF00"}, {"BLUE","#0000FF"}};
 
	// Iterate and print keys and values of unordered_map
	for(const auto& n:u)
		std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
 
	// Add two new entries to the unordered_map
	u["BLACK"]="#000000";
	u["WHITE"]="#FFFFFF";
 
	// Output values by key
	std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
	std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n";

	// Iterate and print keys and values of unordered_map
	for(const auto& n:u)
		std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";

	//判断map中是否包含一个键值，没有直接做此事的成员函数。类似其他的STL容器，解决办法是：
	if( u.find("SALMON")==u.end() )
		printf("No such key \"SALMON\" in the map.\n");
	
	return 0;
}