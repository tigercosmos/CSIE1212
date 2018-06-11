/*
** Copyright @ Liu, An-Chi
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <new>
#include <vector>
using namespace std;
#define MOD 1000000007

// #define debug

struct Obj {
  int row;
  int val;
  int pos;
  int num;
};

#ifdef debug

void print(vector<vector<Obj>> &vv) {
  for (int i = 0; i < vv.size(); i++) {
    cout << "row: ";
    for (int j = 0; j < vv[i].size(); j++) {
      cout << vv[i][j].row;
      if (j != vv[i].size() - 1) {
        cout << ' ';
      }
    }
    cout << '\n';
    cout << "val: ";
    for (int j = 0; j < vv[i].size(); j++) {
      cout << vv[i][j].val;
      if (j != vv[i].size() - 1) {
        cout << ' ';
      }
    }
    cout << '\n';
    // cout << "pos: ";
    // for (int j = 0; j < vv[i].size(); j++) {
    //   cout << vv[i][j].pos;
    //   if (j != vv[i].size() - 1) {
    //     cout << ' ';
    //   }
    // }
    // cout << '\n';
    cout << "num: ";
    for (int j = 0; j < vv[i].size(); j++) {
      cout << vv[i][j].num;
      if (j != vv[i].size() - 1) {
        cout << ' ';
      }
    }
    cout << "\n-\n";
  }
}

void print(vector<int> &v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i];
    if (i != v.size() - 1) {
      cout << ' ';
    }
  }
  cout << '\n';
}
#endif

void print(vector<Obj> &v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i].pos;
    if (i != v.size() - 1) {
      cout << ' ';
    }
  }
  cout << '\n';
}

bool cmp(Obj const &a, Obj const &b) { return a.val < b.val; }

void LIS(vector<int> &s) {
#ifdef debug
  cout << "==========\n";
  print(s);
  cout << "----------\n";
#endif
  int total = 0;
  vector<vector<Obj>> stacks;
  vector<Obj> stack;
  if (s.size() == 0)
    return;
  stack.push_back({0, s[0], 0, 1});
  stacks.push_back(stack);

#ifdef debug
  cout << "> " << s[0] << endl;
  print(stacks);
#endif
  for (int i = 1; i < s.size(); i++) {
    int n = s[i];
#ifdef debug
    cout << "> " << n << endl;
#endif
    int stacks_size = stacks.size();
    for (int row = stacks_size - 1; row >= 0; row--) {
      int num = 0;
      for (int col = 0; col < stacks[row].size(); col++) {
        if (stacks[row][col].val <= n) {
          num += stacks[row][col].num;
        }
      }

      if (num > 0) {
        if (stacks.size() == stacks_size && row == stacks_size - 1) {
          stack.clear();
          stack.push_back({row + 1, n, i, num});
          stacks.push_back(stack);
        } else {
          stacks[row + 1].push_back({row + 1, n, i, num});
        }
        break;
      }
      if (row == 0) {
        stacks[row].push_back({row, n, i, 1});
      }
    }
#ifdef debug
    print(stacks);
#endif
  }
  int max = stacks.size();
  for (int i = 0; i < stacks.back().size(); i++) {
    total += stacks.back()[i].num;
  }
  cout << max << '\n';
  cout << total << '\n';
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N = 0;
  cin >> N;
  vector<int> data;
  data.reserve(N + 1);
  int tmp;
  for (int i = 0; i < N; ++i) {
    cin >> tmp;
    data.push_back(tmp);
  }
  LIS(data);
}