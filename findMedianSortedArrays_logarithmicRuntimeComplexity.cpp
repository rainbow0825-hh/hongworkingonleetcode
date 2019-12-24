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
      size_t num1 = 0;
      size_t totalSize = nums1.size() + nums2.size();
      size_t leftTotal = (size_t)floor(totalSize / 2);
      if (nums2.empty())
      {
         num1 = leftTotal;
      }
      else if (!nums1.empty())
      {
         size_t upperBound_max = min(nums1.size(), leftTotal);
         size_t upperBound = upperBound_max;
         size_t lowerBound = (nums2.size() >= leftTotal) ? 0 : leftTotal - nums2.size();

         num1 = findBoundaries(nums1, nums2, lowerBound, upperBound, upperBound_max, leftTotal);
      }

      int leftMax = 0;
      if (leftTotal)
      {
         if (num1 == 0)
         {
            leftMax = nums2[leftTotal - num1 - 1];
         }
         else if (num1 == leftTotal)
         {
            leftMax = nums1[num1 - 1];
         }
         else
         {
            leftMax = max(nums1[num1 - 1], nums2[leftTotal - num1 - 1]);
         }
      }

      int rightMin = 0;
      if (num1 == nums1.size())
      {
         rightMin = nums2[leftTotal - num1];
      }
      else if (leftTotal - num1 == nums2.size())
      {
         rightMin = nums1[num1];
      }
      else
      {
         rightMin = min(nums1[num1], nums2[leftTotal - num1]);
      }

      if (totalSize % 2)
      {
         return rightMin;
      }
      else
      {
         return ((double)(leftMax + rightMin)) / 2;
      }
   }

private:
   size_t findBoundaries(vector<int>& nums1, vector<int>& nums2, size_t& lowerBound, size_t& upperBound, const size_t upperBound_max, const size_t leftTotal)
   {
      if (lowerBound == upperBound)
      {
         return upperBound;
      }

      size_t num1 = (lowerBound + upperBound)/2 + 1;
      size_t num2 = leftTotal - num1;

      if (num1 > 0 && num2 < nums2.size() && nums1[num1 - 1] > nums2[num2])
      {
         upperBound = num1 - 1;
      }
      else if (num1 < upperBound_max && num2 > 0 && nums1[num1] < nums2[num2 - 1])
      {
         lowerBound = num1 + 1;
      }
      else
      {
         return num1;
      }

      return findBoundaries(nums1, nums2, lowerBound, upperBound, upperBound_max, leftTotal);
   }
};

struct TestData
{
   TestData(vector<int>&& nums1, vector<int>&& nums2, const double median):
      nums1(nums1), nums2(nums2), median(median)
   {}

   vector<int> nums1;
   vector<int> nums2;
   const double median;
};

//int main()
//{
//   Solution solution;
//
//   vector<TestData> testData;
//   testData.push_back(TestData({ 3, 4 }, {}, 3.5));
//   testData.push_back(TestData({ 2, 3, 5, 6 }, { 1, 4 }, 3.5));
//   testData.push_back(TestData({ 3 }, { -2, -1 }, -1));
//   testData.push_back(TestData({ 2, 3 }, { 1, 4 }, 2.5));
//   testData.push_back(TestData({ 2, 3, 4, 5, 7, 8, 10 }, { 1, 6 }, 5));
//   testData.push_back(TestData({ 1, 3 }, { 2 }, 2));
//   testData.push_back(TestData({ 1, 2 }, { 3, 4 }, 2.5));
//   testData.push_back(TestData({ }, { 3, 4 }, 3.5));
//   testData.push_back(TestData({ 3, 4 }, { }, 3.5));
//   testData.push_back(TestData({ }, { 1 }, 1));
//   testData.push_back(TestData({ 2, 3, 4, 5, 6, 7, 8, 9, 10 }, { 1 }, 5.5));
//
//
//   for (auto iter = testData.begin(); iter != testData.end(); ++iter)
//   {
//      double ans = solution.findMedianSortedArrays(iter->nums1, iter->nums2);
//      if (ans != iter->median)
//      {
//         cout << "nums1: ";
//         for (int i = 0; i < iter->nums1.size(); ++i)
//         {
//            cout << iter->nums1[i] << " ";
//         }
//         cout << endl;
//
//         cout << "nums2: ";
//         for (int i = 0; i < iter->nums2.size(); ++i)
//         {
//            cout << iter->nums2[i] << " ";
//         }
//         cout << endl;
//
//         cout << "expected median: " << to_string(iter->median) << endl;
//         cout << "ans: " << to_string(ans) << endl;
//      }
//   }
//
//   return 0;
//}