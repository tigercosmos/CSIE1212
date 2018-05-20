/*
** Liu, An-Chi @ Copyright
*/
#include <cmath>
#include <iostream>
#include <map>
#include <string>
using namespace std;

// #define debug

const unsigned PRIME_BASE = 29;
const unsigned PRIME_MOD = 1000000007;

map<long long, int> hash_map;

char origin_string[200000];
int front = 100000, back = 100000 - 1;
string target_string;

#ifdef debug
void print() {
  for (int i = front; i <= back; i++) {
    cout << origin_string[i];
  }
  cout << '\n';
}
#endif

inline long long make_hash(const string &s) {
  long long ret = 0;
  for (int i = 0; i < s.length(); i++) {
    ret = ret * PRIME_BASE + s[i];
    ret %= PRIME_MOD;
  }
  return ret;
}

inline long long get_power(const int len) {
  int exp = -1;
  int tmp = 1;
  while (tmp < len) {
    tmp *= 2;
    ++exp;
  }
  long long &&power = PRIME_BASE;
  if (len > 1) {
    for (int i = 0; i < exp; ++i) {
      power = (power * power) % PRIME_MOD;
    }
    for (int i = pow(2, exp); i < len; ++i) {
      power = (power * PRIME_BASE) % PRIME_MOD;
    }
  }
  return move(power);
}

// 暴力比對：製造正確答案
int compare() {
  int count = 0;
#ifdef debug
  cout << front << " " << back << endl;
#endif
  for (int i = front; i <= back - target_string.length() + 1; ++i) {
    int flag = 1;
#ifdef debug
    print();
    for (int j = front; j < i; ++j) {
      cout << " ";
    }
    for (int j = 0; j < target_string.length(); ++j) {
      cout << origin_string[i + j];
    }
    cout << endl;
    for (int j = front; j < i; ++j) {
      cout << " ";
    }
    for (int j = 0; j < target_string.length(); ++j) {
      cout << target_string[j];
    }
    cout << endl;
#endif
    for (int j = 0; j < target_string.length(); ++j) {
      if (origin_string[i + j] != target_string[j]) {
        flag = 0;
        break;
      }
    }
    if (flag) {
#ifdef debug
      for (int j = front; j < i; ++j) {
        cout << " ";
      }
      cout << "^" << endl;
#endif
      ++count;
    }
  }
  return count;
}

inline unsigned roll_hash() {
  unsigned &&counter = 0;
  long long sub_hash = make_hash(target_string);
  long long main_hash = 0;
  int sub_string_size = target_string.length();

  long long power = get_power(sub_string_size);

  for (int i = front; i <= back; ++i) {

    // add the last letter
    main_hash = main_hash * PRIME_BASE + origin_string[i];

    main_hash %= PRIME_MOD;

    // remove the first character, if needed
    if ((i - front) >= sub_string_size) {
      main_hash -= (power * origin_string[i - sub_string_size] % PRIME_MOD);

      if (main_hash < 0) // negative can be made positive with mod
        main_hash += PRIME_MOD;
    }
#ifdef debug
    print();
    for (int j = front; j < i; ++j) {
      cout << " ";
    }
    cout << "^\n";
    cout << main_hash << endl;
    cout << sub_hash << endl;
#endif
    // match?
    if ((i - front) >= sub_string_size - 1 && main_hash == sub_hash) {
#ifdef debug
      cout << "\033[1;36m====MATCH====\033[0m" << endl;
#endif
      ++counter;
    }
#ifdef debug
    cout << "-----\n";
#endif
  }

  return move(counter);
}

inline void roll_hash_map() {
  for (int len = 1; len <= 10 && len <= (back - front + 1); ++len) {
    long long main_hash = 0;

    long long power = get_power(len);

    for (int i = front; i <= back; ++i) {

      // add the last letter
      main_hash = main_hash * PRIME_BASE + origin_string[i];

      main_hash %= PRIME_MOD;

      // remove the first character, if needed
      if ((i - front) >= len) {
        main_hash -= (power * origin_string[i - len] % PRIME_MOD);

        if (main_hash < 0) // negative can be made positive with mod
          main_hash += PRIME_MOD;
      }

      if ((i - front) >= len - 1) {
        auto search = hash_map.find(main_hash);
        if (search != hash_map.end()) {
          hash_map[main_hash] += 1;
        } else {
          hash_map.insert({main_hash, 1});
        }
      }
    }
  }
}

inline void roll_hash_map_front() {
  for (int len = 1; len <= 10 && len <= (back - front + 1); ++len) {
    long long main_hash = 0;

    for (int i = front; i <= front + len - 1; ++i) {
      // add the last letter
      main_hash = main_hash * PRIME_BASE + origin_string[i];

      main_hash %= PRIME_MOD;
    }
    auto search = hash_map.find(main_hash);
    if (search != hash_map.end()) {
      hash_map[main_hash] += 1;
    } else {
      hash_map.insert({main_hash, 1});
    }
  }
}

inline void roll_hash_map_back() {
  for (int len = 1; len <= 10 && len <= (back - front + 1); ++len) {
    long long main_hash = 0;

    for (int i = back - len + 1; i <= back; ++i) {
      // add the last letter
      main_hash = main_hash * PRIME_BASE + origin_string[i];

      main_hash %= PRIME_MOD;
    }
    auto search = hash_map.find(main_hash);
    if (search != hash_map.end()) {
      hash_map[main_hash] += 1;
    } else {
      hash_map.insert({main_hash, 1});
    }
  }
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int steps;
  char command;
  char tmp_char;
  char suffix_char;
  target_string.reserve(100000);

  cin >> target_string >> steps;

  for (int i = 0; i < target_string.length(); ++i) {
    origin_string[++back] = target_string[i];
  }
  roll_hash_map();
  for (int i = 0; i < steps; ++i) {
    cin >> command;
    if (command == '1') {
      cin >> tmp_char;
      origin_string[--front] = tmp_char;
      roll_hash_map_front();
    } else if (command == '2') {
      cin >> tmp_char;
      origin_string[++back] = tmp_char;
      roll_hash_map_back();
    } else {
      cin >> target_string;
      // cout << compare() << '\n';
      if (target_string.length() > 10) {
        cout << roll_hash() << '\n';
      } else {
        auto search = hash_map.find(make_hash(target_string));
        if (search != hash_map.end()) {
          cout << search->second << '\n';
        } else {
          cout << "0\n";
        }
      }
    }
  }
}