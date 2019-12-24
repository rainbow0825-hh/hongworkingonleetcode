#include "stdafx.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <exception>

using namespace std;

class Solution
{
public:
   double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      size_t num1 = 0;
      size_t totalSize = nums1.size() + nums2.size();
      size_t leftTotal = totalSize / 2;

      if (nums2.empty())
      {
         num1 = leftTotal;
      }
      else if (!nums1.empty()) // nums1.empty() => num1 = 0 is already covered
      {
         size_t lowerBound = (nums2.size() >= leftTotal) ? 0 : leftTotal - nums2.size();
         size_t upperBound = min(nums1.size(), leftTotal);

         num1 = findBoundaries(nums1, nums2, lowerBound, upperBound, leftTotal);
      }

      double rightMin = getRightMin(nums1, nums2, leftTotal, num1);

      if (totalSize % 2)
      {
         return rightMin;
      }
      else
      {
         double leftMax = getLeftMax(nums1, nums2, leftTotal, num1);
         return (leftMax + rightMin) / 2;
      }
   }

private:
   double getRightMin(vector<int>& nums1, vector<int>&nums2, const size_t leftTotal, const size_t num1)
   {
      if (num1 == nums1.size())
      {
         return nums2[leftTotal - num1];
      }
      if (leftTotal - num1 == nums2.size())
      {
         return nums1[num1];
      }
      return min(nums1[num1], nums2[leftTotal - num1]);
   }

   double getLeftMax(vector<int>& nums1, vector<int>&nums2, const size_t leftTotal, const size_t num1)
   {
      if (num1 == 0)
      {
         return nums2[leftTotal - num1 - 1];
      }
      if (num1 == leftTotal)
      {
         return nums1[num1 - 1];
      }
      return max(nums1[num1 - 1], nums2[leftTotal - num1 - 1]);
   }

   size_t findBoundaries(vector<int>& nums1, vector<int>& nums2, size_t& lowerBound, size_t& upperBound, const size_t leftTotal)
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
      else if (num1 < nums1.size() && num2 > 0 && nums1[num1] < nums2[num2 - 1])
      {
         lowerBound = num1 + 1;
      }
      else
      {
         return num1;
      }

      return findBoundaries(nums1, nums2, lowerBound, upperBound, leftTotal);
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

int main()
{
   Solution solution;

   vector<TestData> testData;
   //testData.push_back(TestData({ 2, 3, 5, 6 }, { 1, 4 }, 3.5));
   //testData.push_back(TestData({ 2, 3, 4, 5, 7, 8, 10 }, { 1, 6 }, 5));
   //testData.push_back(TestData({ 3 }, { -2, -1 }, -1));
   //testData.push_back(TestData({ 2, 3 }, { 1, 4 }, 2.5));
   //testData.push_back(TestData({ 1, 3 }, { 2 }, 2));
   //testData.push_back(TestData({ 1, 2 }, { 3, 4 }, 2.5));
   //testData.push_back(TestData({ }, { 3, 4 }, 3.5));
   //testData.push_back(TestData({ 3, 4 }, { }, 3.5));
   //testData.push_back(TestData({ }, { 1 }, 1));
   testData.push_back(TestData({ 2, 3, 4, 5, 6, 7, 8, 9, 10 }, { 1 }, 5.5));
   //testData.push_back(TestData({ 1 }, { 2, 3, 4 }, 2.5));

   for (auto iter = testData.begin(); iter != testData.end(); ++iter)
   {
      double ans = solution.findMedianSortedArrays(iter->nums1, iter->nums2);
      if (ans != iter->median)
      {
         cout << "nums1: ";
         for (size_t i = 0; i < iter->nums1.size(); ++i)
         {
            cout << iter->nums1[i] << " ";
         }
         cout << endl;

         cout << "nums2: ";
         for (size_t i = 0; i < iter->nums2.size(); ++i)
         {
            cout << iter->nums2[i] << " ";
         }
         cout << endl;

         cout << "expected median: " << to_string(iter->median) << endl;
         cout << "ans: " << to_string(ans) << endl;
         throw("wrong ans");
      }
   }

   return 0;
}