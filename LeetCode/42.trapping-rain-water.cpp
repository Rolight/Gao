/*
 * [42] Trapping Rain Water
 *
 * https://leetcode.com/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (37.49%)
 * Total Accepted:    156.8K
 * Total Submissions: 418.4K
 * Testcase Example:  '[]'
 *
 *
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it is able to trap after
 * raining.
 *
 *
 *
 * For example,
 * Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
 *
 *
 *
 *
 * The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
 * In this case, 6 units of rain water (blue section) are being trapped. Thanks
 * Marcos for contributing this image!
 */
#include <cstdio>
#include <stack>
#include <vector>

using std::stack;
using std::vector;

class State {
public:
  int pos, height;
  State(int pos, int height) : pos(pos), height(height) {}
};

class Solution {
public:
  int trap(vector<int> &height) {
    stack<State> s;
    int answer = 0;
    for (vector<int>::iterator iter = height.begin(); iter != height.end();
         ++iter) {
      int cur_pos = std::distance(height.begin(), iter);
      State cur_state = State(cur_pos, *iter);
      int prev_height = 0;
      while (!s.empty() && s.top().height <= cur_state.height) {
        State cur_top = s.top();
        answer +=
            (cur_state.pos - cur_top.pos - 1) * (cur_top.height - prev_height);
        prev_height = cur_top.height;
        s.pop();
        // printf("pop pos=%d, h=%d\n", cur_top.pos, cur_top.height);
      }
      if (!s.empty()) {
        State cur_top = s.top();
        answer += (cur_state.pos - cur_top.pos - 1) *
                  (cur_state.height - prev_height);
      }
      s.push(cur_state);
      // printf("push pos=%d, h=%d\n", cur_state.pos, cur_state.height);
    }
    return answer;
  }
};
