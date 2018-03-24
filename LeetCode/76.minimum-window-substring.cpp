/*
 * [76] Minimum Window Substring
 *
 * https://leetcode.com/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (26.64%)
 * Total Accepted:    141.6K
 * Total Submissions: 530.5K
 * Testcase Example:  '"a"\n"a"'
 *
 *
 * Given a string S and a string T, find the minimum window in S which will
 * contain all the characters in T in complexity O(n).
 *
 *
 *
 * For example,
 * S = "ADOBECODEBANC"
 * T = "ABC"
 *
 *
 * Minimum window is "BANC".
 *
 *
 *
 * Note:
 * If there is no such window in S that covers all characters in T, return the
 * empty string "".
 *
 *
 * If there are multiple such windows, you are guaranteed that there will
 * always be only one unique minimum window in S.
 *
 */
#include <cstdlib>
#include <iostream>
#include <string>

using std::string;

class Solution {
    void add_ch(int hash[], int target[], int &tar_count, int &count, char ch) {
        int idx = ch;
        if (hash[idx] + 1 == target[idx]) {
            count++;
        }
        hash[idx]++;
    }

    void remove_ch(int hash[], int target[], int &tar_count, int &count,
                   char ch) {
        int idx = ch;
        if (hash[idx] && hash[idx] == target[idx]) {
            count--;
        }
        if (hash[idx] > 0) hash[idx]--;
    }

   public:
    string minWindow(string s, string t) {
        int hash[128], target[128], tar_count = 0, count = 0;
        memset(hash, 0, sizeof(hash));
        memset(target, 0, sizeof(target));
        int ansl = 0, ansr = s.size(), l = 0;
        bool found = false;
        // init target
        for (string::iterator iter = t.begin(); iter != t.end(); ++iter) {
            if (target[*iter] == 0) {
                tar_count++;
            }
            target[*iter]++;
        }
        // gao
        int len = s.length();
        for (int r = 0; r < len; ++r) {
            add_ch(hash, target, tar_count, count, s[r]);
            while (count == tar_count && l <= r) {
                if (r - l < ansr - ansl) {
                    ansr = r;
                    ansl = l;
                    found = true;
                }
                remove_ch(hash, target, tar_count, count, s[l]);
                l++;
            }
        }
        if (!found) {
            return "";
        } else {
            return s.substr(ansl, ansr - ansl + 1);
        }
    }
};

int main() {
    string ss, tt;
    while (std::cin >> ss >> tt) {
        Solution s;
        std::cout << s.minWindow(ss, tt) << std::endl;
    }
    return 0;
}