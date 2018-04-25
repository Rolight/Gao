/*
 * [301] Remove Invalid Parentheses
 *
 * https://leetcode.com/problems/remove-invalid-parentheses/description/
 *
 * algorithms
 * Hard (35.85%)
 * Total Accepted:    67.8K
 * Total Submissions: 189.1K
 * Testcase Example:  '"()())()"'
 *
 *
 * Remove the minimum number of invalid parentheses in order to make the input
 * string valid. Return all possible results.
 *
 * Note: The input string may contain letters other than the parentheses ( and
 * ).
 *
 *
 *
 * Examples:
 *
 * "()())()" -> ["()()()", "(())()"]
 * "(a)())()" -> ["(a)()()", "(a())()"]
 * ")(" -> [""]
 *
 *
 *
 * Credits:Special thanks to @hpplayer for adding this problem and creating all
 * test cases.
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    vector<string> ans;
    unordered_map<int, unordered_map<int, bool> > hashp;
    int min_rmv;
    bool dfs(string &cur_string, int pos, int dep, int cur_rmv, string &s) {
        int pcount = 0;
        while (pos < s.length() && s[pos] != '(' && s[pos] != ')') {
            cur_string.push_back(s[pos++]);
            pcount++;
        }
        bool ret = false;
        if (pos == s.length()) {
            if (dep == 0) {
                if (cur_rmv < min_rmv) {
                    min_rmv = cur_rmv;
                    ans.clear();
                }
                ans.push_back(cur_string);
                ret = true;
            }
        } else {
            cur_string.push_back(s[pos]);
            if (s[pos] == '(') {
                ret |= dfs(cur_string, pos + 1, dep + 1, cur_rmv, s);
            } else if (dep > 0) {
                ret |= dfs(cur_string, pos + 1, dep - 1, cur_rmv, s);
            }
            cur_string.pop_back();
            // pass
            if (cur_rmv < min_rmv)
                ret |= dfs(cur_string, pos + 1, dep, cur_rmv + 1, s);
        }
        while (pcount--) cur_string.pop_back();
        return ret;
    }

   public:
    vector<string> removeInvalidParentheses(string s) {
        ans.clear();
        hashp.clear();
        string tmp;
        min_rmv = s.length();
        dfs(tmp, 0, 0, 0, s);
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    }
};

int main() {
    string buf;
    Solution s;
    while (cin >> buf) {
        vector<string> ret = s.removeInvalidParentheses(buf);
        for (int i = 0; i < ret.size(); i++) {
            cout << ret[i] << endl;
        }
    }
}
