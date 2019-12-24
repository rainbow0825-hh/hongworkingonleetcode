// twoSum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct LessThanBySecond
{
   bool operator()(const std::pair<int, int>& pair1, const std::pair<int, int>& pair2)
   {
      return pair1.second < pair2.second;
   }
};

class Solution {
public:
   vector<int> twoSum(vector<int>& nums, int target)
   {
      vector<pair<int, int>> pairs;
      for (int i = 0; i < nums.size(); ++i)
      {
         pairs.push_back(make_pair(i, nums[i]));
      }
      LessThanBySecond cmp;
      sort(pairs.begin(), pairs.end(), cmp);

      auto iter1 = pairs.begin(), iter2 = pairs.end();
      --iter2;

      while (iter1->second + iter2->second != target)
      {
         if (iter1->second + iter2->second < target)
         {
            ++iter1;
         }
         else
         {
            --iter2;
         }
      }

      int index1 = iter1->first;
      int index2 = iter2->first;

      if (index1 < index2)
      {
         return{ index1, index2 };
      }
      else
      {
         return{ index2, index1 };
      }
   }
};

int main()
{
   vector<int> nums = { 3, 1, 3, 2 };
   int target = 6;
   Solution solution;
   auto ans = solution.twoSum(nums, target);
   return 0;
}

