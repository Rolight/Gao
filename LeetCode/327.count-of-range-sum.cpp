/*
 * [327] Count of Range Sum
 *
 * https://leetcode.com/problems/count-of-range-sum/description/
 *
 * algorithms
 * Hard (30.65%)
 * Total Accepted:    23.9K
 * Total Submissions: 77.9K
 * Testcase Example:  '[-2,5,-1]\n-2\n2'
 *
 *
 * ⁠   Given an integer array nums, return the number of range sums that lie
 * in [lower, upper] inclusive.
 *
 * ⁠   Range sum S(i, j) is defined as the sum of the elements in nums between
 * indices i and
 * ⁠   j (i ≤ j), inclusive.
 *
 *
 *
 * ⁠   Note:
 * ⁠   A naive algorithm of O(n2) is trivial. You MUST do better than that.
 *
 *
 * ⁠   Example:
 * ⁠   Given nums = [-2, 5, -1], lower = -2, upper = 2,
 * ⁠   Return 3.
 * ⁠   The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums
 * are: -2, -1, 2.
 *
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating
 * all test cases.
 */
#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

class Solution {
    vector<LL> C, values;
    inline int lowbit(int x) { return x & -x; }
    inline void addv(int pos, LL v) {
        while (pos < C.size()) {
            C[pos] += v;
            pos += lowbit(pos);
        }
    }

    inline int query(int pos) {
        LL ret = 0;
        while (pos > 0) {
            ret += C[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }

    void discretization(vector<int>& nums, int lower) {
        values.clear();
        LL cur_level = 0;
        for (int i = 0; i < nums.size(); i++) {
            LL cur_real_num = nums[i];
            cur_level += cur_real_num;

            LL cur_num = cur_real_num - cur_level;
            values.push_back(cur_num);
            LL cur_lower = lower - cur_level;
            values.push_back(cur_lower);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
    }

    inline int getID(int x) {
        // find id lower than or equal with x
        vector<LL>::iterator iter =
            lower_bound(values.begin(), values.end(), x);
        return iter - values.begin() + 1;
    }

   public:
    LL countLowerRangeSum(vector<int>& nums, int lower) {
        // count how may range which sum is lower than or equal with arg.lower
        discretization(nums, lower);
        // init BIT
        C = vector<LL>(values.size() + 10);

        LL ans = 0;
        LL cur_level = 0;
        for (int i = 0; i < nums.size(); i++) {
            LL cur_real_num = nums[i];
            cur_level += cur_real_num;
            LL cur_num = nums[i] - cur_level;
            addv(getID(cur_num), 1);
            // cout << cur_num << " += 1" << endl;
            LL cur_lower = lower - cur_level;
            // cout << "add " << query(getID(cur_lower)) << " with query level "
            // << cur_lower << endl;
            ans += query(getID(cur_lower));
        }
        // cout << "lower: " << lower << ", ans: " << ans << endl;
        return ans;
    }
    LL countRangeSum(vector<int>& nums, int lower, int upper) {
        return countLowerRangeSum(nums, upper) -
               countLowerRangeSum(nums, lower - 1);
    }
};
