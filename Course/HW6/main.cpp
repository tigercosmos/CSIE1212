/*
** Copyright @ Liu, An-Chi
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <new>
#include <utility>
#include <vector>
using namespace std;

#define pos pair<int, int>
#define para pair<double, double>

#define debug

int T, n, x, y;

para make_parabola(pos p1, pos p2) {
  double b =
      -(p2.second - (p2.first * p2.first * p1.second / p1.first / p1.first)) /
      ((p1.first * p2.first * p2.first / p1.first / p1.first) - p2.first);
  double a = (p2.second - b * p2.first) / p2.first / p2.first;
  return make_pair(a, b);
}

int in_para(pos p, para f) {
  return (f.first * p.first * p.first + f.second * p.first - p.second == 0);
}

#ifdef debug
void test_make_parabola() {
  pos a(2, 6);
  pos b(4, 8);
  para p1 = make_parabola(a, b);
  cout << "parabola's a: " << p1.first << endl
       << "parabola's b: " << p1.second << endl;
  cout << "(2 ,6) in parabola: " << in_para(make_pair(2, 6), p1) << endl;
}
#endif

vector<int> find_all_points(vector<pos> &pv, vector<para> &para_vec) {
  vector<int> vec;
  for (int i = 0; i < para_vec.size(); i++) {
    int state = 0;
    for (int j = 0; j < pv.size(); j++) {
      if (in_para(pv[j], para_vec[i])) {
        state ^= (1 << i);
      }
    }
    vec.push_back(state);
  }
  return vec;
}

void solve(vector<pos> &pv) {
  vector<para> para_vec;
  vector<int> states;
  for (int i = 0; i < pv.size(); i++) {
    for (int j = i; j < pv.size(); j++) {
      if (i != j) {
        // find all parabola
        para_vec.push_back(make_parabola(pv[i], pv[j]));
      }
    }
  }
  states = find_all_points(pv, para_vec);
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> T;
  vector<pos> pos_vec;
  for (int i = 0; i < T; i++) {
    cin >> n;
    if (n == 2) {
      cout << "1\n";
      continue;
    }
    for (int j = 0; j < n; j++) {
      cin >> x >> y;
      pos_vec.push_back(make_pair(x, y));
    }
    solve(pos_vec);
  }
#ifdef debug
  test_make_parabola();
#endif
}