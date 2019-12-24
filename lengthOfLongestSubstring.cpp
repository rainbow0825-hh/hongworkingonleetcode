// lengthOfLongestSubstring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

class Solution
{
public:
   int lengthOfLongestSubstring(string s)
   {
      vector<char> unrepeatedChars;
      int maxLength = 0;
      for (auto iter = s.begin(); iter != s.end(); ++iter)
      {
         auto unrepeatedIter = find(unrepeatedChars.begin(), unrepeatedChars.end(), *iter);
         if (unrepeatedIter != unrepeatedChars.end())
         {
            if (unrepeatedChars.size() > maxLength)
            {
               maxLength = unrepeatedChars.size();
            }
            unrepeatedChars.erase(unrepeatedChars.begin(), ++unrepeatedIter);
         }
         unrepeatedChars.emplace_back(*iter);
      }
      if (unrepeatedChars.size() > maxLength)
      {
         maxLength = unrepeatedChars.size();
      }
      return maxLength;
   }
};

int main()
{
   string s("dvdf");

   Solution solution;
   cout << s << '\n' << solution.lengthOfLongestSubstring(s) << endl;

   return 0;
}

