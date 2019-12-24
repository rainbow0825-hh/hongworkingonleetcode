#include "stdafx.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <vector>
#include <assert.h>

using namespace std;

class Solution
{
public:
   bool isMatch(string s, string p) {
      size_t nextIndexInS = 0;
      size_t nextIndexInP = 0;
      for (size_t i = 0; i < p.length() && nextIndexInS < s.length() && nextIndexInP < p.length(); ++i)
      {
         if (p[i] == '.' && i < (p.length() - 1) && p[i + 1] != '*')
         {
            if (!compareSubStrings(s, p, nextIndexInS, nextIndexInP, i - nextIndexInP))
            {
               return false;
            }
            ++nextIndexInS;
            ++nextIndexInP;
            continue;
         }

         if (p[i] == '*')
         {
            if (!compareSubStrings(s, p, nextIndexInS, nextIndexInP, i - nextIndexInP - 1))
            {
               return false;
            }

            assert(i > 0);
            char previousChar = p[i - 1];
            if (previousChar == '.')
            {
               previousChar = s[nextIndexInS];
            }
            while (nextIndexInS < s.length() && s[nextIndexInS] == previousChar)
            {
               ++nextIndexInS;
            }
            ++i;
            while (i< p.length() && p[i] == previousChar)
            {
               ++i;
            }
            nextIndexInP = i;
            --i;
         }
      }
      if (!compareSubStrings(s, p, nextIndexInS, nextIndexInP, p.length() - nextIndexInP))
      {
         return false;
      }
      if (nextIndexInS != s.length())
      {
         return false;
      }
      return true;
   }

private:
   bool compareSubStrings(const string& s, const string& p, size_t& nextIndexInS, size_t& nextIndexInP, const size_t len)
   {
      if (len > 0)
      {
         string subS(&s[nextIndexInS], len);
         string subP(&p[nextIndexInP], len);
         if (subS != subP)
         {
            return false;
         }
         nextIndexInS += len;
         nextIndexInP += len;
      }
      return true;
   }
};

int main()
{
   //string s = "mississippi";
   //string p = "mis*i.*sippi";
   
   //string s = "aa";
   //string p = "a";
   //string p = "a*";

   string s = "ab";
   string p = ".*";

   Solution solution;
   cout << "ans: " << solution.isMatch(s, p) << endl;
   return 0;
}