/*
 * [85] Maximal Rectangle
 *
 * https://leetcode.com/problems/maximal-rectangle/description/
 *
 * algorithms
 * Hard (29.42%)
 * Total Accepted:    83.9K
 * Total Submissions: 284.2K
 * Testcase Example:
 * '[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]'
 *
 *
 * Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
 * containing only 1's and return its area.
 *
 *
 * For example, given the following matrix:
 *
 * 1 0 1 0 0
 * 1 0 1 1 1
 * 1 1 1 1 1
 * 1 0 0 1 0
 *
 * Return 6.
 *
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using std::make_pair;
using std::max;
using std::pair;
using std::vector;

typedef pair<int, int> PII;

class Solution {
    vector<vector<int> > getHeightMatrix(vector<vector<char> >& matrix) {
        vector<vector<int> > height;
        int n = matrix.size(), m = matrix[0].size();
        for (int i = 0; i < n; i++) {
            vector<int> tmpv;
            for (int j = 0; j < m; j++) {
                int tmp = 0;
                if (i == 0) {
                    tmp = matrix[i][j] - '0';
                } else {
                    if (matrix[i][j] == '0') {
                        tmp = 0;
                    } else {
                        tmp = height[i - 1][j] + 1;
                    }
                }
                tmpv.push_back(tmp);
            }
            height.push_back(tmpv);
        }
        return height;
    }

    inline int pos(PII& p) { return p.first; }

    inline int h(PII& p) { return p.second; }

    int getMaxArea(vector<int>& height) {
        // pair<int, int>: pos, height
        vector<PII> stk;
        height.push_back(0);
        int ans = 0;
        int n = height.size();
        for (int i = 0; i < n; i++) {
            int cur_pos = i;
            while (!stk.empty() && h(stk.back()) >= height[i]) {
                PII cur_top = stk.back();
                ans = max(ans, (i - pos(cur_top)) * h(cur_top));
                cur_pos = pos(cur_top);
                stk.pop_back();
            }
            stk.push_back(make_pair(cur_pos, height[i]));
        }
        return ans;
    }

   public:
    int maximalRectangle(vector<vector<char> >& matrix) {
        if (matrix.size() == 0) return 0;
        vector<vector<int> > height = getHeightMatrix(matrix);
        int ans = 0;
        for (vector<vector<int> >::iterator iter = height.begin();
             iter != height.end(); ++iter) {
            ans = max(ans, getMaxArea(*iter));
        }
        return ans;
    }
};

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        vector<vector<char> > vec(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int tmp;
                std::cin >> tmp;
                vec[i].push_back('0' + tmp);
            }
        }
        Solution s;
        std::cout << s.maximalRectangle(vec) << std::endl;
    }
    return 0;
}
