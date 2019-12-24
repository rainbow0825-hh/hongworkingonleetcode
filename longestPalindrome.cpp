#include "stdafx.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Solution
{
public:
   string longestPalindrome(string s) {
      size_t startPos = 0;
      size_t longestLen = 1;
      vector<size_t> i_offsets{ 0,1 };
      for (size_t i = 0; i < s.length(); ++i)
      {
         for (auto i_offset : i_offsets)
         {
            size_t currentLongestLen = 1;
            size_t j = 0;
            for (; j <= i; ++j)
            {
               if (j == 0)
               {
                  if (i_offset)
                  {
                     if (s[i] != s[i + 1])
                     {
                        break;
                     }
                     ++currentLongestLen;
                  }
                  continue;
               }

               if (i + i_offset + j < s.length() && s[i - j] == s[i + i_offset + j])
               {
                  currentLongestLen = currentLongestLen + 2;
                  continue;
               }
               break;
            }
            if (currentLongestLen > longestLen)
            {
               startPos = i - j + 1;
               longestLen = currentLongestLen;
            }
         }
      }

      string ans(&s[startPos], longestLen);
      return ans;
   }
};

int main()
{
   //vector<string> s = { "bb", "babad", "cbbd", "abcbabcb", "baab", "bananas", "ccc", "aaaabaaa" };

   vector<string> s = { "cbbd" };

   Solution solution;
   for (auto iter = s.begin(); iter != s.end(); ++iter)
   {
      cout << "s: " << iter->c_str() << endl;
      cout << "ans: " << solution.longestPalindrome(*iter).c_str() << endl;
   }
   return 0;
}