/*
 * [233] Number of Digit One
 *
 * https://leetcode.com/problems/number-of-digit-one/description/
 *
 * algorithms
 * Hard (29.02%)
 * Total Accepted:    34.1K
 * Total Submissions: 117.6K
 * Testcase Example:  '-1'
 *
 * Given an integer n, count the total number of digit 1 appearing in all
 * non-negative integers less than or equal to n.
 *
 *
 * For example:
 * Given n = 13,
 * Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12,
 * 13.
 *
 */
#include <iostream>
#include <vector>

typedef long long LL;

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Solution {
   public:
    vector<int> decode(LL n) {
        vector<int> limits;
        while (n > 0) {
            limits.push_back(n % 10);
            n /= 10;
        }
        return limits;
    }

    LL f[30][20];
    LL cur_num = 0;

    LL dfs(int pos, int r, bool bound, vector<int> &limits) {
        if (pos == 0) {
            if (r != 0)
                return 1;
            else
                return 0;
        }
        if (f[pos][r] != -1 && !bound) return f[pos][r];
        int cur_lim = bound ? limits[pos - 1] : 9;
        LL ret = 0;
        for (int i = 0; i <= cur_lim; i++) {
            if (i == 9) continue;
            ret += dfs(pos - 1, (r + i) % 9, bound && i == cur_lim, limits);
        }
        if (!bound) f[pos][r] = ret;
        return ret;
    }

    LL gao(LL n) {
        if (n <= 0) return 0;
        vector<int> limits = decode(n);
        memset(f, -1, sizeof(f));
        LL ans = dfs(limits.size(), 0, true, limits);
        return ans;
    }
};

int main() {
    LL T, A, B;
    cin >> T;
    Solution s;
    for (int kase = 1; kase <= T; ++kase) {
        cin >> A >> B;
        LL ans = s.gao(B) - s.gao(A - 1);
        cout << "Case #" << kase << ": " << ans << endl;
    }
    return 0;
}
