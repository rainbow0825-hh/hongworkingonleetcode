#include "stdafx.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Solution
{
public:
   string convert(string s, int numRows) {
      auto len = s.length();
      if ((len == 0) || (numRows == 1))
      {
         return s;
      }

      auto distanceInTopRow = 2 * numRows - 2;

      string convertedString;
      for (int row = 0; row < numRows; ++row)
      {
         for (size_t rootIndex = 0; rootIndex < len; rootIndex += distanceInTopRow)
         {
            appendChar(convertedString, s, len, rootIndex + row);
            if ((row != 0) && (row != (numRows - 1)))
            {
               appendChar(convertedString, s, len, rootIndex + distanceInTopRow - row);
            }
         }
      }
      return convertedString;
   }

private:
   void appendChar(string& convertedString, string& s, size_t len, size_t index)
   {
      if (index < len)
      {
         convertedString.append(&s[index], &s[index + 1]);
      }
   }
};

int main()
{
   string s = "ABCDE";
   int numRows = 4;

   Solution solution;
   cout << solution.convert(s, numRows).c_str() << endl;

   return 0;
}