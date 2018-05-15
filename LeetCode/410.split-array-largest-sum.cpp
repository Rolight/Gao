/*
 * [410] Split Array Largest Sum
 *
 * https://leetcode.com/problems/split-array-largest-sum/description/
 *
 * algorithms
 * Hard (39.35%)
 * Total Accepted:    23.2K
 * Total Submissions: 58.9K
 * Testcase Example:  '[7,2,5,10,8]\n2'
 *
 * Given an array which consists of non-negative integers and an integer m, you
 * can split the array into m non-empty continuous subarrays. Write an
 * algorithm to minimize the largest sum among these m subarrays.
 *
 *
 * Note:
 * If n is the length of array, assume the following constraints are
 * satisfied:
 *
 * 1 ≤ n ≤ 1000
 * 1 ≤ m ≤ min(50, n)
 *
 *
 *
 * Examples:
 *
 * Input:
 * nums = [7,2,5,10,8]
 * m = 2
 *
 * Output:
 * 18
 *
 * Explanation:
 * There are four ways to split nums into two subarrays.
 * The best way is to split it into [7,2,5] and [10,8],
 * where the largest sum among the two subarrays is only 18.
 *
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    bool check(long long largest_sum, vector<int> &num, int m) {
        long long cur_sum = 0, subarray_count = 1;
        for (int i = 0; i < num.size(); i++) {
            if (cur_sum + num[i] > largest_sum) {
                ++subarray_count;
                cur_sum = 0;
            }
            if (subarray_count > m) return false;
            cur_sum += num[i];
        }
        return true;
    }

   public:
    int splitArray(vector<int> &nums, int m) {
        long long min_val = 0, total_sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            min_val = max(min_val, (long long)nums[i]);
            total_sum += nums[i];
        }
        long long ans = -1, l = min_val, r = total_sum;
        while (l <= r) {
            long long mid = (l + r) / 2;
            if (check(mid, nums, m)) {
                r = mid - 1;
                ans = mid;
            } else {
                l = mid + 1;
            }
        }
        return (int)ans;
    }
};
