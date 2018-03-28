/*
 * [97] Interleaving String
 *
 * https://leetcode.com/problems/interleaving-string/description/
 *
 * algorithms
 * Hard (25.11%)
 * Total Accepted:    82K
 * Total Submissions: 326.2K
 * Testcase Example:  '""\n""\n""'
 *
 *
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and
 * s2.
 *
 *
 *
 * For example,
 * Given:
 * s1 = "aabcc",
 * s2 = "dbbca",
 *
 *
 * When s3 = "aadbbcbcac", return true.
 * When s3 = "aadbbbaccc", return false.
 *
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::max;
using std::string;
using std::vector;

class Solution {
   public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.length(), m = s2.length();
        int z = s3.length();
        if (n + m != z) return false;
        vector<vector<int> > f(n + 1, vector<int>(m + 1));
        f[0][0] = 1;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                char tar_ch = s3[i + j - 1];
                if (i != 0 && s1[i - 1] == tar_ch) {
                    f[i][j] |= f[i - 1][j];
                }
                if (j != 0 && s2[j - 1] == tar_ch) {
                    f[i][j] |= f[i][j - 1];
                }
            }
        }
        return f[n][m];
    }
};