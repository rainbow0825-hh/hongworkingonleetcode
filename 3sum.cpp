#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
    public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        if (nums.size() < 3)
        {
            return ans;
        }
        sort(nums.begin(), nums.end());   
        for (size_t i = 0; i < nums.size() - 2; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            size_t j = i + 1;
            size_t k = nums.size() - 1;
            while (j < k)
            {
                if (nums[i] + nums[j] + nums[k] > 0)
                {
                    --k;
                }
                else if (nums[i] + nums[j] + nums[k] < 0)
                {
                    ++j;
                }
                else
                {
                    ans.emplace_back(vector<int>({nums[i], nums[j], nums[k]}));
                    while (j < k)
                    {
                        ++j;
                        if (nums[j] != nums[j - 1])
                        {
                            break;
                        }
                    }
                }
            }
        }
        return ans;
    }
};

int main()
{
    // vector<int> nums{-1, 0, 1, 2, -1, -4};
    // vector<int> nums{-1, -1, -1, 2};
    // vector<int> nums{-5, 1, 2, 3, 4};
    vector<int> nums{-2, 0, 0, 2, 2};

    // vector<int> nums;
    Solution solution;
    auto ans = solution.threeSum(nums);

    for (size_t i = 0; i < ans.size(); ++i)
    {
        for (size_t j = 0; j < ans[i].size(); ++j)
        {
            cout << ans[i][j] << " ";    
        }
        cout << endl;
    }
}