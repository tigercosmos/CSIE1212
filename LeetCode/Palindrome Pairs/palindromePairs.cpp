/************************************************************************
  Implement in trie

  1. reverse all strings get words'
  2. store words' in trie
  3. foreach words look up in trie
  4. if the remain string in trie is palindrome, this word is a pair
  5. if the word is longer than the word in trie, check if the remainig
     of this word is palindrome.

  Complexity O(N*k*k)
  N for strings, each k for create and search k length string
************************************************************************/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static bool isPalindrome(string &word) {
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

class Node {
public:
  Node() {
    content = ' ';
    ids.clear();
    end.clear();
  };
  ~Node(){};
  char getContent() { return content; }
  void setContent(char s) { content = s; }
  void addId(int i) { ids.push_back(i); }
  vector<int> getId() { return ids; }
  void appendChild(Node *node) { children.push_back(node); }
  Node *findChild(char s);
  void setEnd(int i) { end.push_back(i); }
  vector<int> getEnd() { return end; }

private:
  char content;
  // all possible ids in this node
  vector<int> ids;
  // mark all ends in this node
  vector<int> end;
  vector<Node *> children;
};

class Trie {
public:
  Trie() { root = new Node(); };
  ~Trie(){};
  void addWord(string word, int wordId);
  vector<int> searchWordId(string &word);
  Node *getRoot() { return root; };

private:
  Node *root;
};

class Solution {
public:
  vector<vector<int>> palindromePairs(vector<string> &words) {
    vector<vector<int>> sets;
    vector<int> pair;
    Trie *trie = new Trie();
    for (int i = 0; i < words.size(); i++) {
      trie->addWord(words[i], i);
    }
    for (int i = 0; i < words.size(); i++) {
      vector<int> ids = trie->searchWordId(words[i]);

      for (int id = 0; id < ids.size(); id++) {
        if (ids[id] != i) {
          // { this, find}
          pair = {i, ids[id]};
          sets.push_back(pair);
        }
      }
      // special case: emtpy string
      if (words[i] == "") {
        ids = trie->getRoot()->getId();
        for (int k = 0; k < ids.size(); k++) {
          if (i != ids[k]) {
            pair = {i, ids[k]};
            sets.push_back(pair);
            pair = {ids[k], i};
            sets.push_back(pair);
          }
        }
      }
    }
    return sets;
  }
};

Node *Node::findChild(char s) {
  for (int i = 0; i < children.size(); i++) {
    Node *tmp = children[i];
    if (tmp->getContent() == s) {
      return tmp;
    }
  }
  return NULL;
}

// add word in reversed
void Trie::addWord(string word, int wordId) {
  Node *current = root;
  // reverse the word
  reverse(word.begin(), word.end());
  // the whole word is a palindrome
  if (isPalindrome(word)) {
    current->addId(wordId);
  }
  // add word into trie
  for (int i = 0; i < word.size(); i++) {
    Node *child = current->findChild(word[i]);
    if (child != NULL) {
      current = child;
    } else {
      Node *tmp = new Node();
      tmp->setContent(word[i]);
      current->appendChild(tmp);
      current = tmp;
    }
    // the remain subtring is a palindrome
    string suffixString = word.substr(i + 1);
    if (isPalindrome(suffixString)) {
      current->addId(wordId);
    }
    if (i == word.size() - 1) {
      current->setEnd(wordId);
    }
  }
};

vector<int> Trie::searchWordId(string &word) {
  vector<int> ids;
  Node *current = root;

  for (int i = 0; i < word.size(); i++) {
    // search this char in the next node
    Node *tmp = current->findChild(word[i]);
    if (tmp != NULL) {
      current = tmp;
    } else {
      break;
    }

    // if end of this word, get all ids that are palindrome
    if (i == word.size() - 1) {
      vector<int> currentNodeIds = current->getId();
      ids.insert(ids.end(), currentNodeIds.begin(), currentNodeIds.end());
      break;
    }

    // if the word is longer than trie's word, check if this is a pair
    string suffix = word.substr(i + 1);
    if (!current->getEnd().empty()) {
      if (isPalindrome(suffix)) {
        vector<int> currentNodeEnds = current->getEnd();
        ids.insert(ids.end(), currentNodeEnds.begin(), currentNodeEnds.end());
      }
    }
  }

  return ids;
};

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