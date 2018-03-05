// http://www.geeksforgeeks.org/unordered_map-in-stl-and-its-applications/

// C++ program to find freq of every word using unordered_map

//#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;
 
// Prints frequencies of individual words in str
void printFrequencies(const string &str){
	// declaring map of <string, int> type, each word
	// is mapped to its frequency
	unordered_map<string, int> wordFreq;
 
	// breaking input into word using string stream
	stringstream ss(str);  // Used for breaking words
	string word; // To store individual words
	while (ss >> word)
		wordFreq[word]++;
 
	// now iterating over word, freq pair and printing them in <, > format
	unordered_map<string, int>:: iterator p;
	for (p = wordFreq.begin(); p != wordFreq.end(); p++)
		cout << "(" << p->first << ", " << p->second << ")\n";
}
 
// Driver code
int main(){
	string str = "geeks for geeks geeks quiz practice qa for";
	printFrequencies(str);
	return 0;
}