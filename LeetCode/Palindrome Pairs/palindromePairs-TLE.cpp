// First try with failure.
// 101 / 134 test cases passed with TLE
// N strings with k length
// Complexity in O(k^2*N^2)

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> palindromePairs(vector<string> &words) {
    return getCombinations(words);
  }

private:
  vector<vector<int>> getCombinations(vector<string> &words) {
    string newWord = "";
    vector<vector<int>> sets;
    vector<int> tmp;
    for (int i = 0; i < words.size(); i++) {
      for (int j = 0; j < words.size(); j++) {
        if (i == j) {
          continue;
        }
        // avoid duplication
        bool isPair = false;
        if (words[i].length() >= words[i].length()) {
          newWord = words[i] + words[j];
          if (isPalindrome(newWord)) {
            tmp = {i, j};
            sets.push_back(tmp);
          }
          if (!isPair && words[i].length() != words[i].length()) {
            newWord = words[j] + words[i];
            if (isPalindrome(newWord)) {
              tmp = {i, j};
              sets.push_back(tmp);
            }
          }
        }
      }
    }
    return sets;
  }

  bool isPalindrome(string &word) {
    int front = 0;
    int rear = word.size() - 1;
    int counter = word.size() / 2;
    while (front < rear) {
      if (word[front] == word[rear]) {
        counter -= 1;
      } else {
        break;
      }
      front += 1;
      rear -= 1;
    }
    return counter == 0;
  }
};