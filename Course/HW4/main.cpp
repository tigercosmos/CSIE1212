/*
** Liu, An-Chi @ Copyright
*/
#include <algorithm>
#include <bitset>
#include <functional>
#include <iostream>
#include <map>
#include <new>
#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const unsigned PRIME_BASE = 29;
const unsigned PRIME_MOD = 1000000007;

long long make_hash(const string &s) {
  long long ret = 0;
  for (int i = 0; i < s.size(); i++) {
    ret = ret * PRIME_BASE + s[i];
    ret %= PRIME_MOD;
  }
  return ret;
}

long long get_power(const int len) {
  int exp = -1;
  int tmp = 1;
  while (tmp < len) {
    tmp *= 2;
    ++exp;
  }
  long long &&power = PRIME_BASE;
  for (int i = 0; i < exp; ++i) {
    power = (power * power) % PRIME_MOD;
  }
  for (int i = pow(2,exp); i < len; ++i) {
    power = (power * PRIME_BASE) % PRIME_MOD;
  }
  return move(power);
}

unsigned roll_hash(const string &sub_string, const string &main_string) {
  unsigned&& counter = 0;
  long long sub_hash = make_hash(sub_string);
  long long main_hash = 0;
  int sub_string_size = sub_string.size();

  long long power = get_power(sub_string_size);

  for (int i = 0; i < main_string.size(); i++) {
    // add the last letter
    main_hash = main_hash * PRIME_BASE + main_string[i];

    main_hash %= PRIME_MOD;

    // remove the first character, if needed
    if (i >= sub_string_size) {
      main_hash -= power * main_string[i - sub_string_size] % PRIME_MOD;
      if (main_hash < 0) // negative can be made positive with mod
        main_hash += PRIME_MOD;
    }

    // match?
    if (i >= sub_string_size - 1 && main_hash == sub_hash)
      ++counter;
  }

  return move(counter);
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string origin_string;
  int steps;
  char command;
  string prefix_string;
  string suffix_string;
  string target_string;
  cin >> origin_string >> steps;
  for (int i = 0; i < steps; ++i) {
    cin >> command >> target_string;
    if (command == '1') {
      prefix_string.insert(0, target_string);
    } else if (command == '2') {
      suffix_string += target_string;
    } else {
      origin_string.insert(0, prefix_string);
      origin_string += suffix_string;
      cout << origin_string <<endl;
      cout << roll_hash(target_string, origin_string) << "\n";
      prefix_string = "";
      suffix_string = "";
    }
  }
}