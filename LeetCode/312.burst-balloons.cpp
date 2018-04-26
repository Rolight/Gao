/*
 * [312] Burst Balloons
 *
 * https://leetcode.com/problems/burst-balloons/description/
 *
 * algorithms
 * Hard (43.70%)
 * Total Accepted:    38.4K
 * Total Submissions: 87.9K
 * Testcase Example:  '[3,1,5,8]'
 *
 *
 * ⁠   Given n balloons, indexed from 0 to n-1. Each balloon is painted with a
 * ⁠   number on it represented by array nums.
 *
 * ⁠   You are asked to burst all the balloons. If the you burst
 * ⁠   balloon i you will get nums[left] * nums[i] * nums[right] coins. Here
 * left
 * ⁠   and right are adjacent indices of i. After the burst, the left and
 * right ⁠   then becomes adjacent.
 *
 *
 * ⁠   Find the maximum coins you can collect by bursting the balloons
 * wisely.
 *
 *
 * ⁠   Note:
 * ⁠   (1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore
 * you can not burst them.
 * ⁠   (2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
 *
 *
 *
 *
 * ⁠   Example:
 *
 *
 * ⁠   Given [3, 1, 5, 8]
 *
 *
 * ⁠   Return 167
 *
 *
 * ⁠   nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
 * ⁠  coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
 *
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating
 * all test cases.
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 512;
int f[maxn][maxn];

class Solution {
   public:
    int maxCoins(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        memset(f, 0, sizeof(f));
        for (int cur_len = 1; cur_len < nums.size() - 1; cur_len++) {
            for (int l = 1; l + cur_len - 1 < nums.size() - 1; l++) {
                int r = l + cur_len - 1;
                for (int k = l; k <= r; k++) {
                    f[l][r] =
                        max(f[l][r], f[l][k - 1] + f[k + 1][r] +
                                         nums[l - 1] * nums[k] * nums[r + 1]);
                }
            }
        }
        return f[1][nums.size() - 2];
    }
};

int main() {
    vector<int> nums;
    int n;
    while (cin >> n) {
        nums.clear();
        for (int i = 1; i <= n; i++) {
            int tmp;
            cin >> tmp;
            nums.push_back(tmp);
        }
        Solution s;
        cout << s.maxCoins(nums) << endl;
    }
}