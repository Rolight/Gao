/*
 * [44] Wildcard Matching
 *
 * https://leetcode.com/problems/wildcard-matching/description/
 *
 * algorithms
 * Hard (20.91%)
 * Total Accepted:    119.1K
 * Total Submissions: 569K
 * Testcase Example:  '"aa"\n"a"'
 *
 * Implement wildcard pattern matching with support for '?' and '*'.
 *
 *
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 *
 * The matching should cover the entire input string (not partial).
 *
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 *
 * Some examples:
 * isMatch("aa","a") → false
 * isMatch("aa","aa") → true
 * isMatch("aaa","aa") → false
 * isMatch("aa", "*") → true
 * isMatch("aa", "a*") → true
 * isMatch("ab", "?*") → true
 * isMatch("aab", "c*a*b") → false
 *
 */
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

typedef vector<bool> VB;

class Solution {
public:
  bool isMatch(string s, string p) {
    int lens = s.length(), lenp = p.length();
    if (lens == 0 && lenp == 0)
      return true;
    vector<VB> f;
    for (int i = 0; i <= lens; i++) {
      f.push_back(vector<bool>());
      for (int j = 0; j <= lenp; j++) {
        f[i].push_back(false);
      }
    }
    f[0][0] = true;
    for (int pos_p = 1; pos_p <= lenp; pos_p++) {
      char cur_p = p[pos_p - 1];
      if (cur_p == '*' && f[0][pos_p - 1]) {
        f[0][pos_p] = true;
      }
      for (int pos_s = 1; pos_s <= lens; pos_s++) {
        if (cur_p != '*' && f[pos_s - 1][pos_p - 1]) {
          if (s[pos_s - 1] == cur_p || cur_p == '?') {
            f[pos_s][pos_p] = true;
          }
        } else if (cur_p == '*') {
          f[pos_s][pos_p] = (f[pos_s][pos_p - 1] || f[pos_s - 1][pos_p - 1] ||
                             f[pos_s - 1][pos_p]);
        }
      }
    }
    return f[lens][lenp];
  }
};

int main() {
  while (true) {
    string a, b;
    std::cin >> a >> b;
    Solution s;
    std::cout << s.isMatch(a, b) << std::endl;
  }
  return 0;
}