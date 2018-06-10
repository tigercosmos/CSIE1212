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
  int val;
  int pos;
};

#ifdef debug

void print(vector<vector<Obj>> &vv) {
  for (int i = 0; i < vv.size(); i++) {
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
  if (s.size() == 0)
    return;
  vector<Obj> v;
  v.push_back({s[0], 1});
  vector<vector<Obj>> vv;
  vv.push_back(v);
#ifdef debug
  cout << "==========\n";
  print(s);
  cout << "----------\n";
  cout << s[0] << '\n';
  cout << ">\n";
  print(vv);
  cout << "----------\n";
#endif
  Obj *tmp = new Obj();
  for (int i = 1; i < s.size(); ++i) {
#ifdef debug
    cout << "----------\n";
    cout << s[i] << '\n';
    cout << ">\n";
#endif
    int n = s[i];
    int len = vv.size();
    for (int vi = 0; vi < len; ++vi) {
      tmp->pos = i + 1;
      tmp->val = n;
      if (n >= vv[vi].back().val) {
        vv[vi].push_back(*tmp);
      } else {
        vector<Obj> nv;
        nv.assign(vv[vi].begin(), vv[vi].end());
        auto low = lower_bound(nv.begin(), nv.end(), *tmp, cmp);
        int dis = low - nv.begin();
        while (dis < len && nv[dis].val == n) {
          dis += 1;
        }
        nv[dis] = *tmp;
        vv.push_back(nv);
      }
    }
#ifdef debug
    print(vv);
#endif
  }
  int max = 0;
  vector<Obj> ans;
  map<string, int> ans_set;

  for (int i = 0; i < vv.size(); ++i) {
    int len = vv[i].size();
    int flag = 1;
    string s = "";
    for (int j = 0; j < len - 1; ++j) {
      s += to_string(vv[i][j].pos);
      if (vv[i][j].pos > vv[i][j + 1].pos) {
        flag = 0;
        break;
      }
    }
    s += to_string(vv[i][len - 1].pos);
    if (!flag || len < max) {
      continue;
    }
    if (len > max) {
      max = len;
      ans = vv[i];
      ans_set.clear();
      ans_set.insert({s, 0});
    } else if (len == max) {
      ans_set.insert({s, 0});
    }
  }
  cout << max << '\n' << ans_set.size() << '\n';
  print(ans);
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