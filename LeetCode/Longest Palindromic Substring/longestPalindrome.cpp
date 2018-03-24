#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
  public:
    string longestPalindrome(string inputString)
    {
        string newString = preprocess(inputString);
        string ouputString = findLongestPalindrome(newString);
        return ouputString;
    }

  private:
    // i.e. input  "abcde"
    //      output "@*a*b*c*d*e*&"
    string preprocess(string originString)
    {
        string outputString = "@*";
        for (int i = 0; i < originString.size(); i++)
        {
            outputString += originString[i];
            outputString += "*";
        }
        outputString += "&";
        return outputString;
    }

    // Manacher’s Algorithm
    string findLongestPalindrome(string inputString)
    {
        // points of lastest max palindrome
        int center = 1;
        int right = 1;
        // symmetry point of i
        int sym = 1;
        // record the longest number of current point
        vector<int> record(inputString.size(), 0);
        // greatest point
        int gcenter = 0;
        int grecord = 0;

        // from index 1 begin to avoid boundary
        for (int i = 1; i < inputString.size() - 1; i++)
        {
            // lastest palindrome's radius v.s. i's symmetry's radius
            sym = 2 * center - i;
            if (right - center > record[sym])
            {
                // i must equal to sym if sym's redius is not out of left boundary
                // if sym is outside left boundary, at least get current radius
                record[i] = min(record[sym], right - center);
            }
            else
            {
                // outside the right boundary, we don't know now
                record[i] = 1;
            }

            // find the current point's longest palindrome if we don't know
            while (inputString[i - record[i]] == inputString[i + record[i]])
            {
                record[i] += 1;
            }

            // check this point's radius
            if (i + record[i] > right)
            {
                center = i;
                right = i + record[i];
            }

            // update greatest point
            if (record[i] > grecord)
            {
                grecord = record[i];
                gcenter = i;
            }
        }

        // from record to get substring
        string palindromeStr = inputString.substr(gcenter - (grecord - 1), 2 * grecord - 1);
        string outputStr = "";

        for (int i = 0; i < palindromeStr.size(); i++)
        {
            if (palindromeStr[i] != '*')
            {
                outputStr += palindromeStr[i];
            }
        }

        return outputStr;
    }

    // for debug
    void print(string s)
    {
        for (int i = 0; i < s.size(); i++)
        {
            cout << s[i] << " ";
        }
        cout << endl;
    }

    void print(vector<int> s)
    {
        for (int i = 0; i < s.size(); i++)
        {
            cout << s[i] << " ";
        }
        cout << endl;
    }
};