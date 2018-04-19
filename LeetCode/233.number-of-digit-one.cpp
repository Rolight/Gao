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

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
    int total_count, one_count;
    Node(int total_count = 0, int one_count = 0)
        : total_count(total_count), one_count(one_count) {}
};

class Solution {
   public:
    vector<int> decode(int n) {
        vector<int> limits;
        while (n > 0) {
            limits.push_back(n % 10);
            n /= 10;
        }
        return limits;
    }

    Node f[20];

    Node dfs(int pos, bool bound, vector<int> &limits) {
        if (pos == 0) {
            return Node(1, 0);
        }
        if (f[pos].one_count != -1 && !bound) return f[pos];
        int cur_lim = bound ? limits[pos - 1] : 9;
        // cout << "cur_lim " << cur_lim << endl;
        Node ret;
        for (int i = 0; i <= cur_lim; i++) {
            Node cret = dfs(pos - 1, bound && i == cur_lim, limits);
            ret.total_count += cret.total_count;
            ret.one_count += cret.one_count;
            if (i == 1) {
                ret.one_count += cret.total_count;
            }
        }
        if (!bound) f[pos] = ret;
        return ret;
    }

    int countDigitOne(int n) {
        if (n <= 0) return 0;
        vector<int> limits = decode(n);
        for (int i = 0; i < 20; i++) {
            f[i] = Node(-1, -1);
        }
        Node ans = dfs(limits.size(), true, limits);
        return ans.one_count;
    }
};

int main() {
    int n;
    while (cin >> n) {
        Solution s;
        cout << s.countDigitOne(n) << endl;
    }
    return 0;
}
