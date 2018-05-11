/*
 * [407] Trapping Rain Water II
 *
 * https://leetcode.com/problems/trapping-rain-water-ii/description/
 *
 * algorithms
 * Hard (37.86%)
 * Total Accepted:    17.2K
 * Total Submissions: 45.5K
 * Testcase Example:  '[[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]'
 *
 * Given an m x n matrix of positive integers representing the height of each
 * unit cell in a 2D elevation map, compute the volume of water it is able to
 * trap after raining.
 *
 *
 * Note:
 * Both m and n are less than 110. The height of each unit cell is greater than
 * 0 and is less than 20,000.
 *
 *
 * Example:
 *
 * Given the following 3x6 height map:
 * [
 * ⁠ [1,4,3,1,3,2],
 * ⁠ [3,2,1,3,2,4],
 * ⁠ [2,3,3,2,3,1]
 * ]
 *
 * Return 4.
 *
 *
 *
 *
 *
 * The above image represents the elevation map
 * [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] before the rain.
 *
 *
 *
 *
 * After the rain, water is trapped between the blocks. The total volume of
 * water trapped is 4.
 *
 */

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

struct HeapNode {
    int height, x, y;
    HeapNode(int height, int x, int y) : height(height), x(x), y(y) {}
    bool operator<(const HeapNode &node) { return height > node.height; }
};

class Solution {
   public:
    int trapRainWater(vector<vector<int> > &heightMap) {
        int n = heightMap.size();
        if (n == 0) return 0;
        int m = heightMap[0].size();

        priority_queue<HeapNode> q;
        vector<bool> vis_row(m, false);
        vector<vector<bool> > vis(n, vis_row);

        for (int i = 0; i < n; i++) {
            q.push(HeapNode(heightMap[i][0], i, 0));
            q.push(HeapNode(heightMap[i][m - 1], i, m - 1));
            vis[i][0] = vis[i][m - 1] = true;
        }
        for (int i = 0; i < m; i++) {
            q.push(HeapNode(heightMap[0][i], 0, i));
            q.push(HeapNode(heightMap[n - 1][i], n - 1, i));
            vis[0][i] = vis[n - 1][i] = true;
        }

        int ans = 0;
        while (!q.empty()) {
            HeapNode cur = q.top();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = cur.x + dx[i], ny = cur.y + dy[i];
                if (nx < 0 || nx == n || ny < 0 || ny == m) continue;
                if (vis[nx][ny]) continue;
                if (heightMap[nx][ny] < cur.height) {
                    ans += heightMap[nx][ny] - cur.height;
                    heightMap[nx][ny] = cur.height;
                }
                vis[nx][ny] = true;
                q.push(HeapNode(heightMap[nx][ny], nx, ny));
            }
        }
        return ans;
    }
};
