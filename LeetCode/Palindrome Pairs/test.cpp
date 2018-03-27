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
  cout << s;
}

static void print(vector<string> v) {
  string s = "Testing: [";
  for (int i = 0; i < v.size(); i++) {
    s += " '";
    s += v[i];
    s += "'";
  }
  s += "]\n";
  cout << s;
}

static void assert_equal(vector<vector<int>> v1, vector<vector<int>> v2) {
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

  vector<string> words = {"a", "aa", "aaa"};
  vector<vector<int>> anwser = {{0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1}};
  print(words);
  assert_equal(sol.palindromePairs(words), anwser);

  words = {"a", ""};
  anwser = {{1, 0}, {0, 1}};
  print(words);
  assert_equal(sol.palindromePairs(words), anwser);

  words = {"bat", "tab", "vvvcat"};
  anwser = {{0, 1}, {1, 0}};
  print(words);
  assert_equal(sol.palindromePairs(words), anwser);

  words = {"abcd", "dcba", "lls", "s", "sssll"};
  anwser = {{0, 1}, {1, 0}, {2, 4}, {3, 2}};
  print(words);
  assert_equal(sol.palindromePairs(words), anwser);

  words = {"a", "abc", "aba", ""};
  anwser = {{3, 0}, {0, 3}, {3, 2}, {2, 3}};
  print(words);
  assert_equal(sol.palindromePairs(words), anwser);

  words = {"a", "b", "c", "ab", "ac", "aa"};
  anwser = {{0, 5}, {1, 3}, {2, 4}, {3, 0}, {4, 0}, {5, 0}};
  print(words);
  assert_equal(sol.palindromePairs(words), anwser);
}