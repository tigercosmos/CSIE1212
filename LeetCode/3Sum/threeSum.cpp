#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    int size = nums.size();
    if (size < 3) {
      return {};
    }
    vector<vector<int>> answer;
    vector<int> ans;
    sort(nums.begin(), nums.end());
    int target_start, target_end;
    if (nums[size / 2] < 0) {
      target_end = size;
      for (int i = size / 2; i < size; i++) {
        target_start = i;
        if (nums[i] >= 0) {
          break;
        }
      }
    } else {
      target_start = 0;
      for (int i = size / 2; i >= 0; i--) {
        target_end = i + 2;
        if (nums[i] < 0) {
          break;
        }
      }
    }
    unordered_map<string, vector<int>> answer_map;
    for (int k = target_start; k < target_end; k++) {
      int target = -nums[k];
      unordered_multimap<int, int> hash_table;
      for (int i = 0; i < size; i++) {
        hash_table.insert({target - nums[i], i});
      }
      for (int i = 0; i < size; i++) {
        if ((target > 0 && nums[i] < 0) || (target < 0 && nums[i] > 0)) {
          continue;
        }
        if (k != i) {
          auto range = hash_table.equal_range(nums[i]);
          for (auto it = range.first; it != range.second; ++it) {
            // the three are not the same
            if (it->second != i && it->second != k) {
              int tmp[3] = {nums[k], nums[i], nums[it->second]};
              sort(tmp, tmp + 3);
              ans.assign(tmp, tmp + 3);
              string&& key = to_string(tmp[0]) + to_string(tmp[1]);
              answer_map.emplace(key, move(ans));
            }
          }
        }
      }
    }
    for (auto it = answer_map.begin(); it != answer_map.end(); it++) {
      answer.push_back(it->second);
    }
    return answer;
  }
};