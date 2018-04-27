/*
 * [315] Count of Smaller Numbers After Self
 *
 * https://leetcode.com/problems/count-of-smaller-numbers-after-self/description/
 *
 * algorithms
 * Hard (35.00%)
 * Total Accepted:    47.3K
 * Total Submissions: 135K
 * Testcase Example:  '[5,2,6,1]'
 *
 *
 * You are given an integer array nums and you have to return a new counts
 * array.
 * The counts array has the property where counts[i] is
 * the number of smaller elements to the right of nums[i].
 *
 *
 * Example:
 *
 *
 * Given nums = [5, 2, 6, 1]
 *
 * To the right of 5 there are 2 smaller elements (2 and 1).
 * To the right of 2 there is only 1 smaller element (1).
 * To the right of 6 there is 1 smaller element (1).
 * To the right of 1 there is 0 smaller element.
 *
 *
 *
 * Return the array [2, 1, 1, 0].
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<int> values;
    vector<int> BIT;

    inline int lowbit(int x) { return x & (-x); }
    inline int getID(int x) {
        return lower_bound(values.begin(), values.end(), x) - values.begin() +
               1;
    }
    void discretization(vector<int>& nums) {
        values.clear();
        for (int i = 0; i < nums.size(); i++) {
            values.push_back(nums[i]);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
    }

    void addv(int pos, int x) {
        while (pos < BIT.size()) {
            BIT[pos] += x;
            pos += lowbit(pos);
        }
    }

    int getsum(int pos) {
        int ret = 0;
        while (pos > 0) {
            ret += BIT[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }

    int getsum(int l, int r) {
        if (l > r) return 0;
        return getsum(r) - getsum(l - 1);
    }

   public:
    vector<int> countSmaller(vector<int>& nums) {
        discretization(nums);
        cout << "discretization finished" << endl;
        vector<int> ans, BIT(values.size() + 1);
        this->BIT = BIT;
        for (int i = nums.size() - 1; i >= 0; i--) {
            int curv = getID(nums[i]);
            ans.push_back(getsum(0, curv - 1));
            addv(curv, 1);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
