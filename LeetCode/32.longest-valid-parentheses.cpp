/*
 * [32] Longest Valid Parentheses
 *
 * https://leetcode.com/problems/longest-valid-parentheses/description/
 *
 * algorithms
 * Hard (23.22%)
 * Total Accepted:    120K
 * Total Submissions: 516.8K
 * Testcase Example:  '""'
 *
 * Given a string containing just the characters '(' and ')', find the length
 * of the longest valid (well-formed) parentheses substring.
 *
 *
 * For "(()", the longest valid parentheses substring is "()", which has length
 * = 2.
 *
 *
 * Another example is ")()())", where the longest valid parentheses substring
 * is "()()", which has length = 4.
 *
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;

typedef pair<int, int> PII;

class Solution {
public:
  int longestValidParentheses(string s) {
    int ans = lvp(s);
    std::reverse(s.begin(), s.end());
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '(')
        s[i] = ')';
      else
        s[i] = '(';
    }
    ans = std::max(ans, lvp(s));
    return ans;
  }

  int lvp(string s) {
    vector<PII> res;
    int cur_dep = 0, cur_head = 0;
    for (int cur = 0; cur < s.length(); cur++) {
      if (s[cur] == '(')
        cur_dep++;
      else
        cur_dep--;
      if (cur_dep < 0) {
        cur_head = cur + 1;
        cur_dep = 0;
      } else if (cur_dep == 0) {
        res.push_back(make_pair(cur_head, cur));
        cur_dep = 0;
        cur_head = cur + 1;
      }
    }
    /*
    for (vector<PII>::iterator i = res.begin(); i != res.end(); ++i) {
      std::cout << i->first << ", " << i->second << std::endl;
    }
    */
    int answer = 0, cur_ans = 0;
    for (int i = 0; i < res.size(); i++) {
      if (i == 0 || res[i - 1].second + 1 != res[i].first) {
        answer = std::max(answer, cur_ans);
        cur_ans = res[i].second - res[i].first + 1;
      } else {
        cur_ans += res[i].second - res[i].first + 1;
      }
    }
    answer = std::max(answer, cur_ans);
    return answer;
  }
};
