#include "./twoSum.cpp"

static void print(vector<int> v) {
  string s = "[";
  for (int i = 0; i < v.size(); i++) {
    s += to_string(v[i]);
    s += " ";
  }
  s += "]\n";
  cout << s;
}

static void assert_equal(vector<int> v1, vector<int> v2) {
  bool isEqual = false;
  if (v1 == v2) {
    isEqual = true;
  }
  if (!isEqual) {
    cout << "   get: ";
    print(v1);
    cout << "expect: ";
    print(v2);
    cout << "the two are not the same!\n";
    throw "Test failed!";
  }
}

int main(int argc, char *argv[]) {
  Solution sol;
  vector<int> v = {2, 7, 11, 15};
  vector<int> ans = {0, 1};
  assert_equal(sol.twoSum(v, 9), ans);
}