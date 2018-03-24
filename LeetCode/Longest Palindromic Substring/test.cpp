#include <string>
#include <iostream>
#include "./longestPalindrome.cpp"
using namespace std;

void assert_equal(string s1, string s2)
{
    if (s1 != s2)
    {
        cout << s1 << endl;
        cout << s2 << endl;
        cout << "the two are not the same!\n";
        throw "Test failed!";
    }
}

int main(int argc, char *argv[])
{
    Solution sol;
    assert_equal(sol.longestPalindrome("abcba"), "abcba");
    assert_equal(sol.longestPalindrome("abcca"), "cc");
    assert_equal(sol.longestPalindrome("abccbra"), "bccb");
    assert_equal(sol.longestPalindrome("1233245423397"), "332454233");
    assert_equal(sol.longestPalindrome("abbcccf"), "ccc");
    assert_equal(sol.longestPalindrome("a"), "a");
    assert_equal(sol.longestPalindrome("aa"), "aa");
}