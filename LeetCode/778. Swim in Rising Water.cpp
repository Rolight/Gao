#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int cx[] = {1, -1, 0, 0};
const int cy[] = {0, 0, 1, -1};

class Solution {
    int n, m;

    bool check(vector<vector<int> > &grid, int time) {
        queue<int> qx, qy;
        qx.push(0);
        qy.push(0);
        vector<int> tmp_row(m, -1);
        vector<vector<int> > vis(n, tmp_row);
        while (!qx.empty()) {
            int x = qx.front(), y = qy.front();
            qx.pop();
            qy.pop();

            for (int i = 0; i < 4; i++) {
                int nx = x + cx[i], ny = y + cy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (vis[nx][ny] != -1) continue;
                if (grid[nx][ny] > time) continue;
                vis[nx][ny] = 1;
                qx.push(nx);
                qy.push(ny);
            }
        }
        return vis[n - 1][m - 1] == 1;
    }

   public:
    int swimInWater(vector<vector<int> > &grid) {
        n = grid.size();
        m = grid[0].size();
        int l = grid[0][0], r = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                r = max(grid[i][j], r);
            }
        }
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(grid, mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};