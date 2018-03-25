/*
 * [84] Largest Rectangle in Histogram
 *
 * https://leetcode.com/problems/largest-rectangle-in-histogram/description/
 *
 * algorithms
 * Hard (27.49%)
 * Total Accepted:    114.3K
 * Total Submissions: 415K
 * Testcase Example:  '[2,1,5,6,2,3]'
 *
 *
 * Given n non-negative integers representing the histogram's bar height where
 * the width of each bar is 1, find the area of largest rectangle in the
 * histogram.
 *
 *
 *
 *
 * Above is a histogram where width of each bar is 1, given height =
 * [2,1,5,6,2,3].
 *
 *
 *
 *
 * The largest rectangle is shown in the shaded area, which has area = 10
 * unit.
 *
 *
 *
 * For example,
 * Given heights = [2,1,5,6,2,3],
 * return 10.
 *
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using std::max;
using std::reverse;
using std::stack;
using std::vector;

class Node {
   public:
    int pos, height;
    Node(int pos, int height) : pos(pos), height(height) {}
};

class Solution {
   public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        int ans = 0, m = heights.size();
        vector<Node> stk;
        for (int i = 0; i < m; i++) {
            int last_pos = i, count_pos = 0;
            while (!stk.empty() && stk.back().height >= heights[i]) {
                Node top_node = stk.back();
                stk.pop_back();
                ans = max(ans, (i + 1 - top_node.pos) * heights[i]);
                ans = max(ans, (i - top_node.pos) * top_node.height);
                last_pos = top_node.pos;
            }
            stk.push_back(Node(last_pos, heights[i]));
            ans = max(ans, heights[i]);
        }
        return ans;
    }
};

int main() {
    int n;
    vector<int> input;
    while (std::cin >> n) {
        input.clear();
        for (int i = 0; i < n; i++) {
            int tmp;
            std::cin >> tmp;
            input.push_back(tmp);
        }
        Solution s;
        std::cout << "answer: " << s.largestRectangleArea(input) << std::endl;
    }
    return 0;
}
