/*
 * [552] Student Attendance Record II
 *
 * https://leetcode.com/problems/student-attendance-record-ii/description/
 *
 * algorithms
 * Hard (31.65%)
 * Total Accepted:    7.8K
 * Total Submissions: 24.7K
 * Testcase Example:  '1'
 *
 * Given a positive integer n, return the number of all possible attendance
 * records with length n, which will be regarded as rewardable. The answer may
 * be very large, return it after mod 109 + 7.
 *
 * A student attendance record is a string that only contains the following
 * three characters:
 *
 *
 *
 * 'A' : Absent.
 * 'L' : Late.
 * ⁠'P' : Present.
 *
 *
 *
 *
 * A record is regarded as rewardable if it doesn't contain more than one 'A'
 * (absent) or more than two continuous 'L' (late).
 *
 * Example 1:
 *
 * Input: n = 2
 * Output: 8
 * Explanation:
 * There are 8 records with length 2 will be regarded as rewardable:
 * "PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
 * Only "AA" won't be regarded as rewardable owing to more than one absent
 * times.
 *
 *
 *
 * Note:
 * The value of n won't exceed 100,000.
 *
 *
 *
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
const LL mod = 1e9 + 7;

class Solution {
   public:
    int checkRecord(int n) {
        LL f[n][3][2];
        /*
            'A' = 0
            'L' = 1
            'P' = 2
        */
        f[0][0][0] = 0;
        f[0][0][1] = 1;

        f[0][1][0] = 1;
        f[0][1][1] = 0;

        f[0][2][0] = 1;
        f[0][2][1] = 0;

        for (int i = 1; i < n; i++) {
            f[i][0][1] = f[i - 1][1][0] + f[i - 1][2][0];
            f[i][0][0] = 0;

            if (i == 1) {
                f[i][1][0] = f[i - 1][1][0] + f[i - 1][2][0];
                f[i][1][1] = f[i - 1][1][1] + f[i - 1][2][1] + f[i - 1][0][1];
            } else {
                f[i][1][0] = f[i - 2][2][0] * 2 + f[i - 2][1][0];
                f[i][1][1] = f[i - 2][2][0] + f[i - 2][2][1] * 2 +
                             f[i - 2][0][1] * 2 + f[i - 2][1][0] +
                             f[i - 2][1][1];
            }

            f[i][2][0] = f[i - 1][1][0] + f[i - 1][2][0];
            f[i][2][1] = f[i - 1][2][1] + f[i - 1][1][1] + f[i - 1][0][1];

            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 2; k++) {
                    f[i][j][k] %= mod;
                }
            }
        }

        LL ans = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++) ans = (ans + f[n - 1][i][j]) % mod;
        return ans;
    }
};
