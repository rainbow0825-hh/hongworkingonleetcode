// addTwoNumbers.cpp : Defines the entry point for the console application.
//

// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output : 7 -> 0 -> 8
// Explanation : 342 + 465 = 807.

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
   ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
      ListNode* sum = NULL;
      ListNode* current = NULL;
      int carry = 0;
      while (l1 != NULL || l2 != NULL)
      {
         int sumOfValues = ((l1 != NULL) ? l1->val : 0) + ((l2 != NULL) ? l2->val : 0) + carry;

         ListNode *node = new ListNode(sumOfValues % 10);

         carry = (sumOfValues - node->val) / 10;

         if (sum == NULL)
         {
            sum = node;
            current = sum;
         }
         else
         {
            current = current->next = node;
         }

         if (l1 != NULL)
         {
            l1 = l1->next;
         }
         if (l2 != NULL)
         {
            l2 = l2->next;
         }
      }
      if (carry)
      {
         current->next = new ListNode(1);
      }
      return sum;
   }
};

ListNode* convertToNode(vector<int>& input)
{
   ListNode* inputPtr = NULL;
   ListNode* currentPtr = NULL;
   for (auto iter = input.begin(); iter < input.end(); ++iter)
   {
      ListNode* node = new ListNode(*iter);
      if (inputPtr == NULL)
      {
         inputPtr = node;
         currentPtr = node;
      }
      else
      {
         currentPtr = currentPtr->next = node;
      }
   }
   return inputPtr;
}

void output(ListNode* sum)
{
   if (sum->next)
   {
      output(sum->next);
   }
   cout << sum->val;
   return;
}

void cleanup(ListNode* sum)
{
   if (sum->next)
   {
      cleanup(sum->next);
   }
   delete sum;
   return;
}

int main()
{
   vector<int> input0 = { 9 };
   vector<int> input1 = { 1, 9, 9, 9, 9, 9, 9, 9, 9, 9 };

   ListNode* inputPtr0 = convertToNode(input0);
   ListNode* inputPtr1 = convertToNode(input1);

   Solution solution;
   ListNode* sum = solution.addTwoNumbers(inputPtr0, inputPtr1);

   output(inputPtr0);
   cout << endl;

   output(inputPtr1);
   cout << endl;

   output(sum);
   cout << endl;

   cleanup(inputPtr0);
   cleanup(inputPtr1);
   cleanup(sum);

   return 0;
}

