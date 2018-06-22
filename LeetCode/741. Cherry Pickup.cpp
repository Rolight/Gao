#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int maxn = 51;
const int dx[] = {0, 1};
const int dy[] = {1, 0};
int f[maxn][maxn][maxn][maxn];

class Solution {
    vector<vector<int> > g;
    int n;
    int dfs(int x1, int y1, int x2, int y2) {
        if (x1 == n - 1 && y1 == n - 1 && x2 == n - 1 && y2 == n - 1) {
            return 0;
        }
        int ret = -1e9;
        if (f[x1][y1][x2][y2] != -1) return f[x1][y1][x2][y2];
        for (int d1 = 0; d1 < 2; d1++) {
            int nx1 = x1 + dx[d1], ny1 = y1 + dy[d1];
            if (nx1 >= n || ny1 >= n) continue;
            if (g[nx1][ny1] == -1) continue;
            for (int d2 = 0; d2 < 2; d2++) {
                int nx2 = x2 + dx[d2], ny2 = y2 + dy[d2];
                if (nx2 >= n || ny2 >= n) continue;
                if (nx2 > nx1 || ny1 > ny1) continue;
                if (g[nx2][ny2] == -1) continue;
                int gain = 0;
                if (g[nx1][ny1] == 1) gain += 1;
                if ((ny2 != ny1 || nx1 != nx2) && g[nx2][ny2]) {
                    gain += 1;
                }
                ret = max(ret, dfs(nx1, ny1, nx2, ny2) + gain);
            }
        }
        f[x1][y1][x2][y2] = ret;
        return ret;
    }

   public:
    int cherryPickup(vector<vector<int> > &grid) {
        memset(f, -1, sizeof(f));
        this->g = grid;
        n = grid.size();
        if (n == 1) {
            return max(grid[0][0], 0);
        }
        int ans = dfs(0, 0, 0, 0) + max(grid[0][0], 0);
        ans = max(ans, 0);
        return ans;
    }
};