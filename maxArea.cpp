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
        int maxArea = min(height[left], height[right]) * (right - left);

        while(1)
        {
            if (left >= right)
            {
                break;
            }
            if (height[left] < height[right])
            {
                int minHeight = height[left];
                for (++left; left < right; ++left)
                {
                    if (height[left] > minHeight)
                    {
                        int currentArea = min(height[left], height[right]) * (right - left);
                        if (currentArea > maxArea)
                        {
                            maxArea = currentArea;
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
                int minHeight = height[right];
                for (--right; right > left; --right)
                {
                    if (height[right] > minHeight)
                    {
                        int currentArea = min(height[left], height[right]) * (right - left);
                        if (currentArea > maxArea)
                        {
                            maxArea = currentArea;
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
                int currentArea = min(height[left], height[right]) * (right - left);
                if (currentArea > maxArea)
                {
                    maxArea = currentArea;
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