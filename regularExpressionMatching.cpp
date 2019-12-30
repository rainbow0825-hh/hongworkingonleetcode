#include "stdio.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <map>

using namespace std;

class Solution
{
public:
   bool isMatch(string s, string p) {
      memo.clear();
      return isSubStringMatch(s, p);
   }

private:
   map<pair<string, string>, bool> memo;

   bool isSubStringMatch(const string& s, const string& p, const size_t s_index, const size_t p_index)
   {
      string s_sub(&s[s_index]);
      string p_sub(&p[p_index]); 
      auto key = make_pair(s_sub, p_sub);
      auto iter = memo.find(key);
      if (iter != memo.end())
      {
         return iter->second;
      }
      bool isMatch = isSubStringMatch(s_sub, p_sub);
      memo[key] = isMatch;
      return isMatch;

      // return isSubStringMatch(&s[s_index], &p[p_index]);
   }

   bool isSubStringMatch(const string& s, const string& p)
   {
      if (p.empty() && !s.empty())
      {
         return false;
      }

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

         if (nextIndexInS == s.length())
         {
            nextIndexInP += 2;
            continue;
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
               if (isSubStringMatch(s, p, j, i + 1))
               {
                  return true;
               }
            }
            return false;
         }

         if (isSubStringMatch(s, p, nextIndexInS, i + 1))
         {
            return true;
         }

         size_t next_s = nextIndexInS;
         if (s[next_s] != previousChar)
         {
            return false;
         }

         for (; next_s != s.length(); ++next_s)
         {
            if (s[next_s] != previousChar)
            {
               break;
            }
            if (isSubStringMatch(s, p, next_s + 1, i - 1))
            {
               return true;
            }
         }
         if (next_s == s.length() && i + 1 == p.length())
         {
            return true;
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
   tests.push_back(Test("aa", "a", false));
   tests.push_back(Test("aa", "a*", true));
   tests.push_back(Test("ab", ".*", true));
   tests.push_back(Test("aab", "c*a*b", true));
   tests.push_back(Test("mississippi", "mis*is*p*.", false));
   tests.push_back(Test("sipp", "s*p*", false));
   tests.push_back(Test("mississippi", "mis*is*ip*.", true));
   tests.push_back(Test("bcaba", ".*a*.", true));
   tests.push_back(Test("aaa", "ab*a*c*a", true));
   tests.push_back(Test("a", "ab*", true));
   tests.push_back(Test("ab", ".*..", true));
   tests.push_back(Test("ab", ".*...", false));
   tests.push_back(Test("abc", ".*..", true));
   tests.push_back(Test("ab", ".*..c*", true));
   tests.push_back(Test("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c", false));
   tests.push_back(Test("b", "a*a*c", false));
   tests.push_back(Test("", "c*c*", true));
   tests.push_back(Test("", "..*", false));
   tests.push_back(Test("aabcbcbcaccbcaabc", ".*a*aa*.*b*.c*.*a*", true));
   tests.push_back(Test("abcaaaaaaabaabcabac", ".*ab.a.*a*a*.*b*b*", true));
   tests.push_back(Test("aaaaaabaabcabac", ".*b*", true));

   Solution solution;
   for (auto iter = tests.begin(); iter != tests.end(); ++iter)
   {
      cout << "s: " << iter->s.c_str() << "\n" << "p: " << iter->p.c_str() << endl;
      cout << endl;

      bool ans = solution.isMatch(iter->s, iter->p);
      if ( ans != iter->match)
      {
         cout << "wrong answer!\n";
         cout << "expected: " << iter->match << endl;
         cout << "ans: " << ans << endl;
         cout << endl;
      }
   }

   return 0;
}