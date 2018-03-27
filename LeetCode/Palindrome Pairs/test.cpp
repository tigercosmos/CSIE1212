#include "./palindromePairs.cpp"

static void print(vector<vector<int>> v) {
  string s = "[";
  for (int i = 0; i < v.size(); i++) {
    s += "[";
    for (int j = 0; j < v[i].size(); j++) {
      s += to_string(v[i][j]);
      if (j != v[i].size() - 1)
        s += " ";
    }
    s += "]";
  }
  s += "]\n";
  cout << s << endl;
}

static void assert_equal(vector<vector<int>> v1, vector<vector<int>> v2) {
  bool isEqual = false;
  if (v1 == v2) {
    isEqual = true;
  }
  if (!isEqual) {
    print(v1);
    print(v2);
    cout << "the two are not the same!\n";
    throw "Test failed!";
  }
}

int main(int argc, char *argv[]) {
  Solution sol;

  vector<string> words = {"bat", "tab", "cat"};
  vector<vector<int>> anwser = {{0, 1}, {1, 0}};
  assert_equal(sol.palindromePairs(words), anwser);

  words = {"abcd", "dcba", "lls", "s", "sssll"};
  anwser = {{0, 1}, {1, 0}, {2, 4}, {3, 2}};
  assert_equal(sol.palindromePairs(words), anwser);
}