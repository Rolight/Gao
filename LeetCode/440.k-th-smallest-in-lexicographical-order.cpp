/*
 * [440] K-th Smallest in Lexicographical Order
 *
 * https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/description/
 *
 * algorithms
 * Hard (25.70%)
 * Total Accepted:    6.1K
 * Total Submissions: 23.7K
 * Testcase Example:  '13\n2'
 *
 * Given integers n and k, find the lexicographically k-th smallest integer in
 * the range from 1 to n.
 *
 * Note: 1 ≤ k ≤ n ≤ 109.
 *
 * Example:
 *
 * Input:
 * n: 13   k: 2
 *
 * Output:
 * 10
 *
 * Explanation:
 * The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so
 * the second smallest number is 10.
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

class Solution {
    vector<int> limits;
    vector<LL> values;
    int N;

    void get_limits(int n) {
        N = n;
        limits.clear();
        while (n) {
            limits.push_back(n % 10);
            n /= 10;
        }
    }

    LL count(int n, int left_pos) { return n % values[left_pos]; }

    LL gao(int left_len, int k, LL cur_num, bool bound) {
        /*
        printf("left_len: %d, k: %d, cur_num: %lld, bound: %d\n", left_len, k,
               cur_num, bound);
        getchar();
        */
        if (k == 0) return cur_num;
        int min_fill_val = left_len == limits.size() ? 1 : 0;
        LL left_count = 0;
        for (int fill_num = min_fill_val; fill_num <= 9; ++fill_num) {
            LL cur_left_count = 0;
            int cur_limits = limits[left_len - 1];
            bool hold_bound;
            if (!bound || fill_num < cur_limits) {
                for (int i = 0; i <= left_len - 1; i++) {
                    cur_left_count += values[i];
                }
                hold_bound = false;
            } else if (fill_num == cur_limits) {
                for (int i = 0; i < left_len - 1; i++) {
                    cur_left_count += values[i];
                }
                cur_left_count += count(N, left_len - 1) + 1;
                hold_bound = true;
            } else {
                for (int i = 0; i < left_len - 1; i++) {
                    cur_left_count += values[i];
                }
                hold_bound = false;
            }
            /*
            printf("fill num %d, cur left count = %lld, left_count=%lld\n",
                   fill_num, cur_left_count, left_count);
            */
            if (left_count + 1 == k) {
                return cur_num * 10 + fill_num;
            } else if (left_count + cur_left_count >= k) {
                if (!bound || fill_num <= cur_limits) {
                    return gao(left_len - 1, k - left_count - 1,
                               cur_num * 10 + fill_num, hold_bound);
                } else {
                    return gao(left_len - 2, k - left_count - 1,
                               cur_num * 10 + fill_num, hold_bound);
                }
            } else
                left_count += cur_left_count;
        }
        return -1;
    }

   public:
    Solution() {
        values.push_back(1);
        for (int i = 1; i <= 16; i++) {
            values.push_back(values[i - 1] * 10);
        }
    }
    int findKthNumber(int n, int k) {
        get_limits(n);
        return gao(limits.size(), k, 0, true);
    }
};

int main() {
    Solution s;
    int n, k;
    while (cin >> n >> k) {
        cout << s.findKthNumber(n, k) << endl;
    }
    return 0;
}
