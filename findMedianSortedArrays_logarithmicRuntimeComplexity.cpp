#include "stdafx.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

class Solution
{
public:
   double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      if (nums1.empty())
      {
         return findMedianSortedArray(nums2);
      }

      if (nums2.empty())
      {
         return findMedianSortedArray(nums1);
      }

      size_t totalSize = nums1.size() + nums2.size();
      size_t leftTotal = (size_t)floor(totalSize / 2);
      size_t min1 = 0, max1 = min(nums1.size(), leftTotal);

      findBoundaries(nums1, nums2, min1, max1, leftTotal);

      int leftMax = 0;
      if (max1 == 0)
      {
         leftMax = nums2[leftTotal - max1 - 1];
      }
      else if (max1 == leftTotal)
      {
         leftMax = nums1[max1 - 1];
      }
      else
      {
         leftMax = max(nums1[max1 - 1], nums2[leftTotal - max1 - 1]);
      }

      int rightMin = 0;
      if (max1 == nums1.size())
      {
         rightMin = nums2[leftTotal - max1];
      }
      else if (leftTotal - max1 == nums2.size())
      {
         rightMin = nums1[max1];
      }
      else
      {
         rightMin = min(nums1[max1], nums2[leftTotal - max1]);
      }

      if (totalSize % 2)
      {
         return rightMin;
      }
      else
      {
         return ((double)(leftMax + rightMin)) / 2;
      }
      
      return 0;
   }

private:
   void findBoundaries(vector<int>& nums1, vector<int>& nums2, size_t& min1, size_t& max1, int leftTotal)
   {
      size_t num1 = max1;
      size_t num2 = leftTotal - num1;

      if (num1 == 0)
      {
         return;
      }

      if (num1 == nums1.size() && nums1[num1 - 1] <= nums2[num2])
      {
         return;
      }

      if (num2 != nums2.size() && nums1[num1 - 1] > nums2[num2])
      {
         if (leftTotal > nums2.size())
         {
            max1 = max((min(max1 - 1, (size_t)floor(max1 / 2) + 1)), leftTotal - nums2.size());
         }
         else
         {
            max1 = (min(max1 - 1, (size_t)floor(max1 / 2) + 1));
         }
      }
      else if ((num2 > 0) && nums1[num1] < nums2[num2 - 1])
      {
         min1 = (size_t)floor(max1 / 2);
      }
      else
      {
         return;
      }

      findBoundaries(nums1, nums2, min1, max1, leftTotal);
   }

   double findMedianSortedArray(vector<int>& nums)
   {
      if (nums.size() % 2) {
         return nums[(size_t)floor(nums.size() / 2)];
      }
      else
      {
         return ((double)nums[nums.size() / 2 - 1] + (double)nums[nums.size() / 2]) / 2;
      }
   }
};