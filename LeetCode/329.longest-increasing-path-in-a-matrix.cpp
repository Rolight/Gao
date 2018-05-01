/*
 * [329] Longest Increasing Path in a Matrix
 *
 * https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/
 *
 * algorithms
 * Hard (37.46%)
 * Total Accepted:    52.6K
 * Total Submissions: 140.5K
 * Testcase Example:  '[[9,9,4],[6,6,8],[2,1,1]]'
 *
 * Given an integer matrix, find the length of the longest increasing path.
 *
 *
 * From each cell, you can either move to four directions: left, right, up or
 * down. You may NOT move diagonally or move outside of the boundary (i.e.
 * wrap-around is not allowed).
 *
 *
 * Example 1:
 *
 * nums = [
 * ⁠ [9,9,4],
 * ⁠ [6,6,8],
 * ⁠ [2,1,1]
 * ]
 *
 *
 *
 *
 * Return 4
 *
 * The longest increasing path is [1, 2, 6, 9].
 *
 *
 * Example 2:
 *
 * nums = [
 * ⁠ [3,4,5],
 * ⁠ [3,2,6],
 * ⁠ [2,2,1]
 * ]
 *
 *
 *
 *
 * Return 4
 *
 * The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not
 * allowed.
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating
 * all test cases.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

class Solution {
    int ans = 0;
    int n, m;
    vector<vector<int> > matrix;
    void dfs(int x, int y, vector<vector<int> >& vis) {
        ans = max(ans, vis[x][y]);
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (vis[nx][ny] >= vis[x][y] + 1) continue;
            if (matrix[nx][ny] <= matrix[x][y]) continue;
            vis[nx][ny] = vis[x][y] + 1;
            dfs(nx, ny, vis);
        }
    }

   public:
    int longestIncreasingPath(vector<vector<int> >& matrix) {
        n = matrix.size();
        if (n == 0) return 0;
        m = matrix[0].size();
        this->matrix = matrix;
        vector<int> tmp(m);
        vector<vector<int> > vis(n, tmp);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                vis[i][j] = max(vis[i][j], 1);
                dfs(i, j, vis);
            }
        }
        return ans;
    }
};
