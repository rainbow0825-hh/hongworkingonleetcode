#include "stdafx.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Solution
{
public:
   double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      auto begin1 = nums1.begin(), begin2 = nums2.begin();
      auto end1 = nums1.end(), end2 = nums2.end();
      
      while (1)
      {
         if (begin1 == end1)
         {
            return findMedianSortedArray(begin2, end2);
         }

         if (begin2 == end2)
         {
            return findMedianSortedArray(begin1, end1);
         }

         if ((end1 - begin1 == 1) && (end2 - begin2 == 1))
         {
            return (double)(*begin1 + *begin2) / 2;
         }

         if (*begin1 < *begin2)
         {
            ++begin1;
         }
         else
         {
            ++begin2;
         }

         if ((begin2 == end2) || *(end1 - 1) > *(end2 - 1))
         {
            --end1;
         }
         else
         {
            --end2;
         }
      }

      return 0;
   }

private:
   double findMedianSortedArray(const vector<int>::iterator begin, const vector<int>::iterator end)
   {
      int distance = end - begin;
      int mod = distance % 2;
      if (mod) {
         return *(begin + floor(distance / 2));
      }
      else
      {
         return (double)(*(begin + distance / 2 - 1) + *(begin + distance / 2)) / 2;
      }
   }
};

//int main()
//{
//   vector<int> nums1{ 1 };
//   vector<int> nums2{ 1, 5, 6, 7, 10 };
//
//   Solution solution;
//   cout << solution.findMedianSortedArrays(nums1, nums2) << endl;
//
//   return 0;
//}