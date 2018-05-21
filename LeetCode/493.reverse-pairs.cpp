/*
 * [493] Reverse Pairs
 *
 * https://leetcode.com/problems/reverse-pairs/description/
 *
 * algorithms
 * Hard (20.63%)
 * Total Accepted:    11.9K
 * Total Submissions: 57.7K
 * Testcase Example:  '[1,3,2,3,1]'
 *
 * Given an array nums, we call (i, j) an important reverse pair if i < j and
 * nums[i] > 2*nums[j].
 *
 * You need to return the number of important reverse pairs in the given
 * array.
 *
 * Example1:
 *
 * Input: [1,3,2,3,1]
 * Output: 2
 *
 *
 * Example2:
 *
 * Input: [2,4,3,5,1]
 * Output: 3
 *
 *
 * Note:
 *
 * The length of the given array will not exceed 50,000.
 * All the numbers in the input array are in the range of 32-bit integer.
 *
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

class Solution {
    vector<LL> values;
    int N;
    vector<int> sum;

    inline int lowbit(int x) { return x & -x; }

    void discretization(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++) {
            values.push_back(nums[i]);
            values.push_back((LL)nums[i] * 2);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        N = values.size() + 1;
    }

    inline void initBIT() { sum = vector<int>(N + 1, 0); }

    inline int getID(LL x) {
        return lower_bound(values.begin(), values.end(), x) - values.begin() +
               1;
    }

    inline void addv(int pos, int val) {
        while (pos <= N) {
            sum[pos] += val;
            pos += lowbit(pos);
        }
    }

    inline int _ask(int pos) {
        int ret = 0;
        while (pos > 0) {
            ret += sum[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }

    inline int ask(int l, int r) {
        if (l > r) return 0;
        if (l == 0) return _ask(r);
        return _ask(r) - _ask(l - 1);
    }

   public:
    int reversePairs(vector<int> &nums) {
        int ans = 0;
        discretization(nums);
        initBIT();
        for (int i = 0; i < nums.size(); i++) {
            int cur_id = getID((LL)nums[i] * 2);
            ans += ask(cur_id + 1, N);
            addv(getID(nums[i]), 1);
        }
        return ans;
    }
};
