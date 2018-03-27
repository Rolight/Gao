/*
 * [87] Scramble String
 *
 * https://leetcode.com/problems/scramble-string/description/
 *
 * algorithms
 * Hard (29.66%)
 * Total Accepted:    72.6K
 * Total Submissions: 244.7K
 * Testcase Example:  '"a"\n"a"'
 *
 *
 * Given a string s1, we may represent it as a binary tree by partitioning it
 * to two non-empty substrings recursively.
 *
 *
 * Below is one possible representation of s1 = "great":
 *
 *
 * ⁠   great
 * ⁠  /    \
 * ⁠ gr    eat
 * ⁠/ \    /  \
 * g   r  e   at
 * ⁠          / \
 * ⁠         a   t
 *
 *
 * To scramble the string, we may choose any non-leaf node and swap its two
 * children.
 *
 *
 * For example, if we choose the node "gr" and swap its two children, it
 * produces a scrambled string "rgeat".
 *
 *
 * ⁠   rgeat
 * ⁠  /    \
 * ⁠ rg    eat
 * ⁠/ \    /  \
 * r   g  e   at
 * ⁠          / \
 * ⁠         a   t
 *
 *
 * We say that "rgeat" is a scrambled string of "great".
 *
 *
 * Similarly, if we continue to swap the children of nodes "eat" and "at", it
 * produces a scrambled string "rgtae".
 *
 *
 * ⁠   rgtae
 * ⁠  /    \
 * ⁠ rg    tae
 * ⁠/ \    /  \
 * r   g  ta  e
 * ⁠      / \
 * ⁠     t   a
 *
 *
 * We say that "rgtae" is a scrambled string of "great".
 *
 *
 * Given two strings s1 and s2 of the same length, determine if s2 is a
 * scrambled string of s1.
 *
 */
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
   public:
    vector<vector<int> > acount, bcount;
    bool dfs(int al, int ar, int bl, int br) {
        // std::cout << al << " " << ar << " " << bl << " " << br << std::endl;
        if (al == ar && bl == br) {
            return true;
        }
        bool ret = false;
        for (int t = 0; al + t < ar; t++) {
            int amid = al + t, bmid1 = bl + t, bmid2 = br - t - 1;
            if (checkCount(al, amid, bl, bmid1)) {
                if (dfs(al, amid, bl, bmid1) &&
                    dfs(amid + 1, ar, bmid1 + 1, br)) {
                    ret = true;
                    break;
                }
            }

            if (checkCount(al, amid, bmid2 + 1, br)) {
                if (dfs(al, amid, bmid2 + 1, br) &&
                    dfs(amid + 1, ar, bl, bmid2)) {
                    ret = true;
                    break;
                }
            }
        }
        return ret;
    }

    bool checkCount(int al, int ar, int bl, int br) {
        for (int i = 0; i < 128; i++) {
            int ac = acount[ar][i];
            int bc = bcount[br][i];
            if (al > 0) ac -= acount[al - 1][i];
            if (bl > 0) bc -= bcount[bl - 1][i];
            if (ac != bc) return false;
        }
        return true;
    }

    bool isScramble(string s1, string s2) {
        int alen = s1.length(), blen = s2.length();
        if (alen != blen) return false;

        for (int i = 0; i < alen; i++) {
            vector<int> tmp(128);
            tmp[s1[i]] = 1;
            if (i > 0) {
                for (int j = 0; j < 128; j++) {
                    tmp[j] += acount[i - 1][j];
                }
            }
            acount.push_back(tmp);
        }

        for (int i = 0; i < alen; i++) {
            vector<int> tmp(128);
            tmp[s2[i]] = 1;
            if (i > 0) {
                for (int j = 0; j < 128; j++) {
                    tmp[j] += bcount[i - 1][j];
                }
            }
            bcount.push_back(tmp);
        }
        if (!checkCount(0, alen - 1, 0, alen - 1)) return false;
        return dfs(0, alen - 1, 0, blen - 1);
    }
};

int main() {
    string a, b;
    while (std::cin >> a >> b) {
        Solution s;
        std::cout << s.isScramble(a, b) << std::endl;
    }
    return 0;
}
