/*
 * [10] Regular Expression Matching
 *
 * https://leetcode.com/problems/regular-expression-matching/description/
 *
 * algorithms
 * Hard (24.34%)
 * Total Accepted:    186.7K
 * Total Submissions: 767.3K
 * Testcase Example:  '"aa"\n"a"'
 *
 * Implement regular expression matching with support for '.' and '*'.
 *
 *
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
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
 * isMatch("aa", "a*") → true
 * isMatch("aa", ".*") → true
 * isMatch("ab", ".*") → true
 * isMatch("aab", "c*a*b") → true
 *
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::string;

class State {
public:
  std::map<char, State *> transfers;
  bool isEnd;

  State() { isEnd = false; }

  string toString() {
    string ret = "can transfer to: ";
    for (std::map<char, State *>::iterator iter = transfers.begin();
         iter != transfers.end(); ++iter) {
      char cur_ch = iter->first;
      if (cur_ch == 0) {
        cur_ch = '$';
      }
      ret += cur_ch;
      ret += " ";
    }
    return ret;
  }
};

class Solution {
public:
  State *compile(string p) {
    State *start_state = new State();
    State *cur_state = start_state;
    for (string::iterator iter = p.begin(); iter != p.end(); ++iter) {
      if ((iter + 1) != p.end() && *(iter + 1) == '*') {
        State *ns1 = new State(), *ns2 = new State();
        cur_state->transfers[*iter] = ns1;
        ns1->transfers[*iter] = ns1;
        cur_state->transfers[0] = ns2;
        ns1->transfers[0] = ns2;
        cur_state = ns2;
        iter++;
      } else {
        State *next_state = new State();
        cur_state->transfers[*iter] = next_state;
        cur_state = next_state;
      }
    }
    cur_state->isEnd = true;
    return start_state;
  }

  bool isEndState(State *s) {
    if (s->transfers.count(0) != 0) {
      return isEndState(s->transfers[0]);
    }
    return s->isEnd;
  }

  bool isMatch(string &s, int pos, State *state) {
    if (pos == s.size()) {
      return isEndState(state);
    }
    bool result = false;
    std::vector<char> v;
    v.push_back('.');
    v.push_back(s[pos]);
    v.push_back(0);
    for (std::vector<char>::iterator iter = v.begin(); iter != v.end();
         ++iter) {
      if (state->transfers.count(*iter) != 0) {
        int next_pos = pos + 1;
        if (*iter == 0) {
          next_pos = pos;
        }
        result |= isMatch(s, next_pos, state->transfers[*iter]);
      }
      if (result) {
        break;
      }
    }
    return result;
  }

  bool isMatch(string s, string p) {
    State *start_state = compile(p);
    return isMatch(s, 0, start_state);
  }
};