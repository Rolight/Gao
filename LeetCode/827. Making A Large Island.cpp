#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

class Solution {
    int n, m, total;
    vector<int> fa, size, vis;

    inline int id(int x, int y) { return x * m + y; }

    int getfa(int x) {
        if (fa[x] == x) return x;
        int cur_fa = fa[x];
        int root_fa = getfa(fa[x]);
        if (cur_fa != root_fa) size[cur_fa] -= size[x];
        fa[x] = root_fa;
        return fa[x];
    }

    void megre(int x, int y) {
        int fx = getfa(x), fy = getfa(y);
        if (fx == fy) return;
        if (fx > fy) swap(fx, fy);
        fa[fy] = fx;
        size[fx] += size[fy];
    }

    inline bool invalid(int x, int y) {
        return x < 0 || x >= n || y < 0 || y >= m;
    }

    void bfs(int x, int y, vector<vector<int> > &grid) {
        int root = id(x, y);
        queue<int> q;
        q.push(root);
        vis[root] = 1;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            int cx = now / m, cy = now % m;
            for (int i = 0; i < 4; i++) {
                int nx = cx + dx[i], ny = cy + dy[i];
                if (invalid(nx, ny)) continue;
                if (vis[id(nx, ny)] == 1) continue;
                if (grid[nx][ny] == 0) continue;
                vis[id(nx, ny)] = 1;
                megre(root, id(nx, ny));
                q.push(id(nx, ny));
            }
        }
    }

   public:
    int largestIsland(vector<vector<int> > &grid) {
        n = grid.size();
        if (n == 0) return 0;
        m = grid[0].size();
        total = n * m;
        fa = vector<int>(total);
        size = vector<int>(total);
        vis = vector<int>(total);

        for (int i = 0; i < total; i++) {
            size[i] = 1;
            fa[i] = i;
            vis[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[id(i, j)] && grid[i][j] == 1) {
                    bfs(i, j, grid);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < total; i++) ans = max(ans, size[i]);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) continue;
                set<int> cur;
                for (int d = 0; d < 4; d++) {
                    int nx = i + dx[d], ny = j + dy[d];
                    if (invalid(nx, ny)) continue;
                    if (grid[nx][ny] == 0) continue;
                    cur.insert(getfa(id(nx, ny)));
                }
                int cur_ans = 1;
                for (int root : cur) {
                    // printf("%d %d with root %d\n", i, j, root);
                    cur_ans += size[root];
                }
                ans = max(ans, cur_ans);
            }
        }
        return ans;
    }
};