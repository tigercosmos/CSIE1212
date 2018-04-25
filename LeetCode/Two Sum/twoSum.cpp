#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    vector<int> tmp;
    unordered_map<int, int> hash_table;
    for (int i = 0; i < nums.size(); i++) {
      hash_table.insert({target - nums[i], i});
    }
    for (int i = 0; i < nums.size(); i++) {
      if (hash_table.count(nums[i])) {
        if (hash_table[nums[i]] != i) {
          tmp = {i, hash_table[nums[i]]};
          break;
        }
      }
    }
    return tmp;
  }
};