/*
 * [316] Remove Duplicate Letters
 *
 * https://leetcode.com/problems/remove-duplicate-letters/description/
 *
 * algorithms
 * Hard (30.42%)
 * Total Accepted:    40.1K
 * Total Submissions: 131.7K
 * Testcase Example:  '"bcabc"'
 *
 *
 * Given a string which contains only lowercase letters, remove duplicate
 * letters so that every letter appear once and only once. You must make sure
 * your result is the smallest in lexicographical order among all possible
 * results.
 *
 *
 *
 * Example:
 *
 *
 * Given "bcabc"
 * Return "abc"
 *
 *
 * Given "cbacdcbc"
 * Return "acdb"
 *
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating
 * all test cases.
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
    int bit(char c) { return 1 << (c - 'a'); }

   public:
    string removeDuplicateLetters(string s) {
        vector<int> mask;
        for (int i = s.length() - 1; i >= 0; i--) {
            int cur = bit(s[i]);
            if (mask.size() > 0) {
                cur |= mask[mask.size() - 1];
            }
            mask.push_back(cur);
        }
        reverse(mask.begin(), mask.end());
        string ans;
        vector<int> ans_mask(26);
        for (int i = 0; i < s.length(); i++) {
            while (ans.size() > 0 && ans.back() > s[i] &&
                   ans_mask[s[i] - 'a'] == 0 && (bit(ans.back()) & mask[i])) {
                ans_mask[ans.back() - 'a']--;
                ans.pop_back();
            }
            if (ans_mask[s[i] - 'a'] == 0) {
                ans.push_back(s[i]);
                ans_mask[s[i] - 'a']++;
            }
        }
        return ans;
    }
};

int main() {
    string buf;
    while (cin >> buf) {
        Solution s;
        cout << s.removeDuplicateLetters(buf) << endl;
    }
    return 0;
}