#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;
class Solution
{
public:
    int maxArea(vector<int>& height){
        if (height.empty())
        {
            return 0;
        }

        if (height[0] <= height[height.size() - 1])
        {
            return calculateMaxArea(height, 0, height.size() - 1);
        }
        else
        {
            return calculateMaxArea(height, height.size() - 1, 0);
        }
    }

private:
    int calculateMaxArea(vector<int>& height, size_t first, size_t second)
    {
        int minHeight = height[first];
        int step = first < second ? 1 : -1;
        int maxArea = minHeight * (second - first) * step;

        for (; first != second; first += step)
        {
            if (height[first] <= minHeight)
            {
                continue;
            }

            if (height[first] <= height[second])
            {
                int currentArea = height[first] * (second - first) * step;
                if (currentArea > maxArea)
                {
                    maxArea = currentArea;
                    minHeight = height[first];
                }
            }
            else // height[first] > height[second]
            {
                return max(maxArea, calculateMaxArea(height, second, first));
            }
        }
        return maxArea;
    }
};

int main()
{
    Solution solution;

    // vector<int> height{1,8,6,2,5,4,8,3,7};
    vector<int> height{1, 2, 3, 1000, 1000, 3, 7, 1};
    // vector<int> height{3, 2, 1, 3};
    // vector<int> height{1, 1};
    // vector<int> height{2, 1};
    // vector<int> height{2,3,10,5,7,8,9};
    cout << solution.maxArea(height) << endl;
}