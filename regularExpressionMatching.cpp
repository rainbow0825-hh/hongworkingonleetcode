#include "stdio.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

class Solution
{
public:
   bool isMatch(string s, string p) {
      return isSubStringMatch(s, p);
   }

private:
   bool isSubStringMatch(const string& s, const string& p)
   {
      size_t nextIndexInS = 0;
      size_t nextIndexInP = 0;
      for (size_t i = 0; i < p.length() && nextIndexInP < p.length(); ++i)
      {
         if (p[i] != '.' && p[i] != '*')
         {
            continue;
         }

         if (p[i] == '.')
         {
            if (i == (p.length() - 1) || p[i + 1] != '*')
            {
               if (!compareSubStrings(s, p, nextIndexInS, nextIndexInP, i - nextIndexInP))
               {
                  return false;
               }
               if (nextIndexInS == s.length())
               {
                  return false;
               }
               ++nextIndexInS;
               ++nextIndexInP;
            }
            continue;
         }

         // p[i] == '*'
         assert(i > 0);
         if (!compareSubStrings(s, p, nextIndexInS, nextIndexInP, i - nextIndexInP - 1))
         {
            return false;
         }

         char previousChar = p[i - 1];
         if (previousChar == '.')
         {
            if (i == p.length() - 1)
            {
               return true;
            }
            char nextChar = p[i + 1];
            for (size_t j = nextIndexInS; j < s.length(); ++j)
            {
               if (nextChar != '.' && s[j] != nextChar)
               {
                  continue;
               }
               if (isSubStringMatch(&s[j], &p[i + 1]))
               {
                  return true;
               }
            }
            return false;
         }

         if (nextIndexInS == s.length())
         {
            nextIndexInP += 2;
            continue;
         }

         if (s[nextIndexInS] != previousChar)
         {
            size_t next_p = i + 1;
            for (; next_p < p.length(); ++next_p)
            {
               if (p[next_p] != previousChar && p[next_p] != '*')
               {
                  break;
               }
            }

            if (next_p != p.length())
            {
               return isSubStringMatch(&s[nextIndexInS], &p[next_p]);
            }
         }
         else
         {
            size_t next_s = nextIndexInS;
            for (; next_s != s.length(); ++next_s)
            {
               if (isSubStringMatch(&s[next_s], &p[i + 1]))
               {
                  return true;
               }
               if (s[next_s] != previousChar)
               {
                  break;
               }
            }
            if (next_s == s.length() && i + 1 == p.length())
            {
               return true;
            }
         }
         return false;
      }

      if (!compareSubStrings(s, p, nextIndexInS, nextIndexInP, min(p.length() - nextIndexInP, s.length() - nextIndexInS)))
      {
         return false;
      }
      return (nextIndexInS == s.length() && nextIndexInP == p.length());
   }

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

struct Test
{
   Test(string&& s, string&& p, bool match)
      : s(s), p(p), match(match) {}
   string s;
   string p;
   bool match;
};

int main()
{
   vector<Test> tests;
   // tests.push_back(Test("aa", "a", false));
   // tests.push_back(Test("aa", "a*", true));
   // tests.push_back(Test("ab", ".*", true));
   // tests.push_back(Test("aab", "c*a*b", true));
   // tests.push_back(Test("mississippi", "mis*is*p*.", false));
   // tests.push_back(Test("mississippi", "mis*is*ip*.", true));
   // tests.push_back(Test("bcaba", ".*a*.", true));
   // tests.push_back(Test("aaa", "ab*a*c*a", true));
   // tests.push_back(Test("a", "ab*", true));
   // tests.push_back(Test("ab", ".*..", true));
   // tests.push_back(Test("ab", ".*...", false));
   // tests.push_back(Test("abc", ".*..", true));
   // tests.push_back(Test("ab", ".*..c*", true));
   // tests.push_back(Test("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c", false));
   // tests.push_back(Test("b", "a*a*c", false));
   // tests.push_back(Test("", "c*c*", true));
   // tests.push_back(Test("", "..*", false));
   tests.push_back(Test("aabcbcbcaccbcaabc", ".*a*aa*.*b*.c*.*a*", true));

   Solution solution;
   for (auto iter = tests.begin(); iter != tests.end(); ++iter)
   {
      bool ans = solution.isMatch(iter->s, iter->p);
      if ( ans != iter->match)
      {
         cout << "wrong answer!\n";
         cout << "s: " << iter->s.c_str() << "\n" << "p: " << iter->p.c_str() << "\n" << endl;
         cout << "expected: " << iter->match << endl;
         cout << "ans: " << ans << endl;
      }
   }

   return 0;
}