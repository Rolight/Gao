#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

class Solution {
   public:
    int smallestDistancePair(vector<int> &nums, int k) {
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.back() - nums[0];
        int ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int cur_val = 0;
            for (int i = 0; i < nums.size(); i++) {
                int cur_max_val = nums[i] + mid;
                int dis = upper_bound(nums.begin(), nums.end(), cur_max_val) -
                          nums.begin() - 1;
                dis -= i;
                cur_val += dis;
            }
            if (cur_val >= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        int final_ans = -1;
        for (int i = 0; i < nums.size(); i++) {
            int cur_max_val = nums[i] + ans;
            vector<int>::iterator iter =
                lower_bound(nums.begin(), nums.end(), cur_max_val);
            if (iter == nums.end()) {
                continue;
            }
            if (final_ans == -1 || *iter - nums[i] < final_ans) {
                final_ans = *iter - nums[i];
            }
        }
        return final_ans;
    }
};