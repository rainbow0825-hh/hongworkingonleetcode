#include <stdio.h>
#include <algorithm>
#include <vector>
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

        size_t left = 0;
        size_t right = height.size() - 1;
        int minHeight = min(height[left], height[right]);
        int maxArea = minHeight * (right - left);

        while(1)
        {
            if (left >= right)
            {
                break;
            }
            if (height[left] < height[right])
            {
                for (++left; left < right; ++left)
                {
                    if (height[left] > minHeight)
                    {
                        int currentMinHeight = min(height[left], height[right]);
                        int currentArea = currentMinHeight * (right - left);
                        if (currentArea > maxArea)
                        {
                            maxArea = currentArea;
                            minHeight = currentMinHeight;
                        }
                    }
                    if (height[left] >= height[right])
                    {
                        break;
                    }
                }
                if (height[left] < height[right])
                {
                    break;
                }
            }
            else if (height[right] < height[left])
            {
                for (--right; right > left; --right)
                {
                    if (height[right] > minHeight)
                    {
                        int currentMinHeight = min(height[left], height[right]);
                        int currentArea = min(height[left], height[right]) * (right - left);
                        if (currentArea > maxArea)
                        {
                            maxArea = currentArea;
                            minHeight = currentMinHeight;
                        }
                    }
                    if (height[right] >= height[left])
                    {
                        break;
                    }
                }
                if (height[right] < height[left])
                {
                    break;
                }
            }
            else
            {
                if (++left >= --right)
                {
                    break;
                }
                int currentMinHeight = min(height[left], height[right]);
                int currentArea = currentMinHeight * (right - left);
                if (currentArea > maxArea)
                {
                    maxArea = currentArea;
                    minHeight = currentMinHeight;
                }
            }
        }
        return maxArea;
    }
};

int main()
{
    Solution solution;

    // vector<int> height{1,8,6,2,5,4,8,3,7};
    // vector<int> height{1, 2, 3, 1000, 1000, 3, 7, 1};
    // vector<int> height{3, 2, 1, 3};
    // vector<int> height{1, 1};
    // vector<int> height{2, 1};
    vector<int> height{2,3,10,5,7,8,9};
    cout << solution.maxArea(height) << endl;
}