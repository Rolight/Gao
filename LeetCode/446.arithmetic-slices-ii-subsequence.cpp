/*
 * [446] Arithmetic Slices II - Subsequence
 *
 * https://leetcode.com/problems/arithmetic-slices-ii-subsequence/description/
 *
 * algorithms
 * Hard (28.01%)
 * Total Accepted:    9.2K
 * Total Submissions: 32.7K
 * Testcase Example:  '[2,4,6,8,10]'
 *
 * A sequence of numbers is called arithmetic if it consists of at least three
 * elements and if the difference between any two consecutive elements is the
 * same.
 *
 * For example, these are arithmetic sequences:
 * 1, 3, 5, 7, 9
 * 7, 7, 7, 7
 * 3, -1, -5, -9
 *
 * The following sequence is not arithmetic. 1, 1, 2, 5, 7
 *
 *
 * A zero-indexed array A consisting of N numbers is given. A subsequence slice
 * of that array is any sequence of LLegers (P0, P1, ..., Pk) such that 0 ≤ P0
 * < P1 < ... < Pk < N.
 *
 * A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the
 * sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic. In particular,
 * this means that k ≥ 2.
 *
 * The function should return the number of arithmetic subsequence slices in
 * the array A.
 *
 * The input contains N LLegers. Every LLeger is in the range of -231 and
 * 231-1 and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 231-1.
 *
 *
 * Example:
 *
 * Input: [2, 4, 6, 8, 10]
 *
 * Output: 7
 *
 * Explanation:
 * All arithmetic subsequence slices are:
 * [2,4,6]
 * [4,6,8]
 * [6,8,10]
 * [2,4,6,8]
 * [4,6,8,10]
 * [2,4,6,8,10]
 * [2,6,10]
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long LL;

class Solution {
   public:
    int numberOfArithmeticSlices(vector<int> &A) {
        unordered_map<LL, vector<LL> > pos;
        for (LL i = 0; i < A.size(); i++) {
            pos[A[i]].push_back(i);
        }
        LL ans = 0;
        vector<unordered_map<LL, LL> > f(A.size());
        for (LL i = 0; i < A.size(); i++) {
            // prLLf("cur i is %d\n", i);
            for (LL j = i + 1; j < A.size(); j++) {
                LL cur_gap = (LL)A[j] - A[i];
                LL next_val = A[j] + cur_gap;
                if (pos.count(next_val) == 0) continue;
                vector<LL> &next_val_pos = pos[next_val];
                vector<LL>::iterator iter =
                    upper_bound(next_val_pos.begin(), next_val_pos.end(), j);
                f[j][cur_gap] += f[i][cur_gap] + 1;
                ans += (LL)(next_val_pos.end() - iter) * (f[i][cur_gap] + 1);
            }
        }
        return ans;
    }
};