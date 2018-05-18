/*
 * [466] Count The Repetitions
 *
 * https://leetcode.com/problems/count-the-repetitions/description/
 *
 * algorithms
 * Hard (27.23%)
 * Total Accepted:    5.8K
 * Total Submissions: 21.4K
 * Testcase Example:  '"acb"\n4\n"ab"\n2'
 *
 * Define S = [s,n] as the string S which consists of n connected strings s.
 * For example, ["abc", 3] ="abcabcabc".
 * On the other hand, we define that string s1 can be obtained from string s2
 * if we can remove some characters from s2 such that it becomes s1. For
 * example, “abc”  can be obtained from “abdbec” based on our definition, but
 * it can not be obtained from “acbbe”.
 * You are given two non-empty strings s1 and s2 (each at most 100 characters
 * long) and two integers 0 ≤ n1 ≤ 106 and 1 ≤ n2 ≤ 106. Now consider the
 * strings S1 and S2, where S1=[s1,n1] and S2=[s2,n2]. Find the maximum integer
 * M such that [S2,M] can be obtained from S1.
 *
 * Example:
 *
 * Input:
 * s1="acb", n1=4
 * s2="ab", n2=2
 *
 * Return:
 * 2
 *
 *
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int len1 = s1.length(), len2 = s2.length();
        vector<int> last_pos(len1, -1), last_pos_1(len1, -1);
        long long step1, step2, base;
        for (int i = 0, j = 0;; i++) {
            for (int j_step = 0; s1[j % len1] != s2[i % len2] && j_step < len1;
                 j_step++, j++)
                ;
            if (s1[j % len1] != s2[i % len2]) return 0;

            if (i % len2 == len2 - 1) {
                if (last_pos[j % len1] == -1) {
                    last_pos[j % len1] = i;
                    last_pos_1[j % len1] = j;
                } else {
                    step2 = i - last_pos[j % len1];
                    step1 = j - last_pos_1[j % len1];
                    base = (j + 1) % step1;
                    break;
                }
            }
            j++;
        }
        long long full_steps = ((long long)len1 * n1 - base) / step1 * step1;
        int ans = full_steps / step1 * step2 / len2;
        for (int i = full_steps, j = 0; i < len1 * n1; i++) {
            while (i < len1 * n1 && s1[i % len1] != s2[j % len2]) i++;
            if (i == len1 * n1 || s1[i % len1] != s2[j % len2]) break;
            if (j % len2 == len2 - 1) ans++;
            j++;
        }
        ans /= n2;
        return ans;
    }
};

int main() {
    string s1, s2;
    Solution s;
    int n1, n2;
    while (cin >> s1 >> n1 >> s2 >> n2) {
        cout << s.getMaxRepetitions(s1, n1, s2, n2) << endl;
    }
    return 0;
}
