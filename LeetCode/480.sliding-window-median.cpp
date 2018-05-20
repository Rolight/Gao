/*
 * [480] Sliding Window Median
 *
 * https://leetcode.com/problems/sliding-window-median/description/
 *
 * algorithms
 * Hard (30.83%)
 * Total Accepted:    14.1K
 * Total Submissions: 45.7K
 * Testcase Example:  '[1,3,-1,-3,5,3,6,7]\n3'
 *
 * Median is the middle value in an ordered integer list. If the size of the
 * list is even, there is no middle value. So the median is the mean of the two
 * middle value.
 * Examples:
 * [2,3,4] , the median is 3
 * [2,3], the median is (2 + 3) / 2 = 2.5
 *
 * Given an array nums, there is a sliding window of size k which is moving
 * from the very left of the array to the very right. You can only see the k
 * numbers in the window. Each time the sliding window moves right by one
 * position. Your job is to output the median array for each window in the
 * original array.
 *
 * For example,
 * Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
 *
 *
 * Window position                Median
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       1
 * ⁠1 [3  -1  -3] 5  3  6  7       -1
 * ⁠1  3 [-1  -3  5] 3  6  7       -1
 * ⁠1  3  -1 [-3  5  3] 6  7       3
 * ⁠1  3  -1  -3 [5  3  6] 7       5
 * ⁠1  3  -1  -3  5 [3  6  7]      6
 *
 *
 * Therefore, return the median sliding window as [1,-1,-1,3,5,6].
 *
 * Note:
 * You may assume k is always valid, ie: k is always smaller than input array's
 * size for non-empty array.
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

class Solution {
    vector<int> values;
    vector<int> sum;
    int N;

    void discretization(vector<int> &nums) {
        values.clear();
        for (int i = 0; i < nums.size(); i++) {
            values.push_back(nums[i]);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        N = values.size();
    }

    inline int getID(int x) {
        return lower_bound(values.begin(), values.end(), x) - values.begin() +
               1;
    }

    void build() { sum = vector<int>(N * 4 + 10, 0); }

    inline void pushup(int rt) { sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }

    void update(int rt, int l, int r, int pos, int val) {
        if (l == r)
            sum[rt] += val;
        else {
            int mid = (l + r) / 2;
            if (pos <= mid)
                update(lson, pos, val);
            else
                update(rson, pos, val);
            pushup(rt);
        }
    }

    double findkth(int k) {
        int rt = 1, l = 1, r = N;
        while (l < r) {
            int mid = (l + r) / 2;
            int lc = rt << 1, rc = rt << 1 | 1;
            // printf("cur in %d->%d, sum[lc] = %d, sum[rc] = %d\n", l, r,
            // sum[lc],
            //        sum[rc]);
            if (sum[lc] >= k) {
                rt = lc;
                r = mid;
            } else {
                k -= sum[lc];
                rt = rc;
                l = mid + 1;
            }
        }
        // printf("get %d\n", l);
        return (double)values[l - 1];
    }

   public:
    vector<double> medianSlidingWindow(vector<int> &nums, int k) {
        discretization(nums);
        build();
        vector<double> ans;
        for (int i = 0; i < nums.size(); i++) {
            int cur_id = getID(nums[i]);
            update(1, 1, N, cur_id, 1);
            if (i >= k) {
                int remove_id = getID(nums[i - k]);
                update(1, 1, N, remove_id, -1);
            }
            if (sum[1] == k) {
                if (k % 2 == 0) {
                    double n1 = findkth(k / 2), n2 = findkth(k / 2 + 1);

                    ans.push_back((n1 + n2) / 2.0);
                } else {
                    double n1 = findkth(k / 2 + 1);
                    ans.push_back(n1);
                }
            }
        }
        return ans;
    }
};