/*
 * [45] Jump Game II
 *
 * https://leetcode.com/problems/jump-game-ii/description/
 *
 * algorithms
 * Hard (26.14%)
 * Total Accepted:    111.9K
 * Total Submissions: 428.4K
 * Testcase Example:  '[0]'
 *
 *
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array.
 *
 *
 * Each element in the array represents your maximum jump length at that
 * position.
 *
 *
 * Your goal is to reach the last index in the minimum number of jumps.
 *
 *
 *
 * For example:
 * Given array A = [2,3,1,1,4]
 *
 *
 * The minimum number of jumps to reach the last index is 2. (Jump 1 step from
 * index 0 to 1, then 3 steps to the last index.)
 *
 *
 *
 * Note:
 * You can assume that you can always reach the last index.
 */
#include <deque>
#include <map>
#include <vector>

using std::deque;
using std::make_pair;
using std::pair;
using std::vector;

typedef pair<int, int> PII;

class Solution {
public:
  int jump(vector<int> &nums) {
    deque<PII> s;
    // first: val, second: pos
    s.push_back(make_pair(0, 0));
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      PII cur_state = s.front();
      if (i == n - 1) {
        return cur_state.first;
      }
      while (!s.empty() && s.front().second <= i) {
        s.pop_front();
      }
      int next_val = cur_state.first + 1, next_pos = i + nums[i];
      if (next_pos >= s.back().second) {
        s.push_back(make_pair(next_val, next_pos));
      }
    }
    return 0;
  }
};
