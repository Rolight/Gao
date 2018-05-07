/*
 * [363] Max Sum of Rectangle No Larger Than K
 *
 * https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/description/
 *
 * algorithms
 * Hard (33.79%)
 * Total Accepted:    19.4K
 * Total Submissions: 57.3K
 * Testcase Example:  '[[1,0,1],[0,-2,3]]\n2'
 *
 * Given a non-empty 2D matrix matrix and an integer k, find the max sum of a
 * rectangle in the matrix such that its sum is no larger than k.
 *
 * Example:
 * Given matrix = [
 * ⁠ [1,  0, 1],
 * ⁠ [0, -2, 3]
 * ]
 * k = 2
 *
 *
 *
 * The answer is 2. Because the sum of rectangle [[0, 1], [-2, 3]] is 2 and 2
 * is the max number no larger than k (k = 2).
 *
 * Note:
 *
 * The rectangle inside the matrix must have an area > 0.
 * What if the number of rows is much larger than the number of columns?
 *
 *
 *
 * Credits:Special thanks to @fujiaozhu for adding this problem and creating
 * all test cases.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int> > ssum;

    int check(int sx, int sy, int ex, int ey) {
        int ret = ssum[ex][ey];
        if (sx > 0) ret -= ssum[sx - 1][ey];
        if (sy > 0) ret -= ssum[ex][sy - 1];
        if (sx > 0 && sy > 0) ret += ssum[sx - 1][sy - 1];
        return ret;
    }

   public:
    int maxSumSubmatrix(vector<vector<int> > &matrix, int k) {
        int n = matrix.size();
        int m = matrix[0].size();
        int ans = -1e8;
        ssum = matrix;
        // init prefix summary
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < m; j++) {
                ssum[i][j] += ssum[i][j - 1];
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ssum[i][j] += ssum[i - 1][j];
            }
        }

        for (int sx = 0; sx < n; sx++) {
            for (int sy = 0; sy < m; sy++) {
                for (int ex = sx; ex < n; ex++) {
                    for (int ey = sy; ey < m; ey++) {
                        int ret = check(sx, sy, ex, ey);
                        if (ret <= k) {
                            ans = max(ans, ret);
                        }
                    }
                }
            }
        }
        return ans;
    }
};
