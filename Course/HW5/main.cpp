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

#define debug

struct Obj {
  int row;
  int val;
  int pos;
  int num;
  int trace;
  int last;
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
    cout << "pos: ";
    for (int j = 0; j < vv[i].size(); j++) {
      cout << vv[i][j].pos;
      if (j != vv[i].size() - 1) {
        cout << ' ';
      }
    }
    cout << '\n';
    cout << "num: ";
    for (int j = 0; j < vv[i].size(); j++) {
      cout << vv[i][j].num;
      if (j != vv[i].size() - 1) {
        cout << ' ';
      }
    }
    cout << '\n';
    cout << "trace: ";
    for (int j = 0; j < vv[i].size(); j++) {
      cout << vv[i][j].trace;
      if (j != vv[i].size() - 1) {
        cout << ' ';
      }
    }
    cout << '\n';
    cout << "last: ";
    for (int j = 0; j < vv[i].size(); j++) {
      cout << vv[i][j].last;
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

void print_rev(vector<int> &vec) {
  for (int i = vec.size() - 1; i >= 0; i--) {
    cout << vec[i];
    if (i != 0) {
      cout << ' ';
    }
  }
  cout << '\n';
}

void print(vector<Obj> &v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i].pos;
    if (i != v.size() - 1) {
      cout << ' ';
    }
  }
  cout << '\n';
}

int choose_min(vector<vector<int>> &answers) {
  for (int i = answers[0].size() - 1; i >= 0; i--) {
    vector<int> tmp;
    for (int j = 0; j < answers.size(); j++) {
      tmp.push_back(answers[j][i]);
    }
    sort(tmp.begin(), tmp.end());
    if (tmp[0] != tmp[1]) {
      for (int j = 0; j < answers.size(); j++) {
        if (tmp[0] == answers[j][i]) {
          return j;
        }
      }
    }
  }
  return 0;
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
  stack.push_back({0, s[0], 1, 1, 0, -1});
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
      int trace = 5001;
      int minPos = 5001;
      for (int col = 0; col < stacks[row].size(); col++) {
        if (stacks[row][col].val <= n) {
          num += stacks[row][col].num;
          num %= MOD;
          if (stacks[row][col].pos < minPos) {
            minPos = stacks[row][col].pos;
            trace = stacks[row][col].trace;
          }
        }
      }

      if (num > 0) {
        if (stacks.size() == stacks_size && row == stacks_size - 1) {
          stack.clear();
          stack.push_back({row + 1, n, i + 1, num, trace, minPos});
          stacks.push_back(stack);
        } else {
          stacks[row + 1].push_back({row + 1, n, i + 1, num, trace, minPos});
        }
        break;
      }
      if (row == 0) {
        stacks[row].push_back({row, n, i + 1, 1, i, -1});
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
  vector<vector<int>> answers;
  int tr = 5001;
  // from the last row to find which line can get the result
  for (int col = 0; col < stacks.back().size(); col++) {
    tr = min(stacks.back()[col].trace, tr);
  }

#ifdef debug
  cout << "All Possible line:\n";
#endif
  // from the last row to trace all possible lines
  for (int col = 0; col < stacks.back().size(); col++) {
    if (stacks.back()[col].trace == tr) {
      // trace the line
      vector<int> tmp;
      tmp.push_back(stacks.back()[col].pos);
      for (int row = stacks.size() - 1; row > 0; row--) {
        for (int col = 0; col < stacks[row].size(); col++) {
          if (stacks[row][col].trace == tr &&
              stacks[row][col].pos == tmp.back()) {
            tmp.push_back(stacks[row][col].last);
            break;
          }
        }
      }
      answers.push_back(tmp);
#ifdef debug
      print_rev(tmp);
#endif
    }
  }

  int c = choose_min(answers);

  cout << max << '\n';
  cout << total << '\n';
  print_rev(answers[c]);
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