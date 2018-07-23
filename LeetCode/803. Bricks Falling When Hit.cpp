#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

class Solution {
    int n, m;
    inline int id(int i, int j) { return i * m + j; }
    vector<int> fa;
    vector<int> fc;

    int getfa(int x) {
        if (x == fa[x]) return x;

        int cur_fa = getfa(fa[x]);
        if (cur_fa != fa[x]) fc[fa[x]] -= fc[x];
        fa[x] = cur_fa;

        return cur_fa;
    }

    void megre(int x, int y) {
        // printf("megre %d, %d and %d, %d\n", x / m, x % m, y / m, y % m);
        int fax = getfa(x), fay = getfa(y);
        if (fax < fay) {
            fa[fay] = fax;
            fc[fax] += fc[fay];
        } else if (fay < fax) {
            fa[fax] = fay;
            fc[fay] += fc[fax];
        }
        // printf("after megre\n");
        // outputfa();
    }

    void bfs(int sx, int sy, vector<bool> &vis, vector<vector<int> > &grid) {
        queue<int> q;
        vis[id(sx, sy)] = true;
        q.push(id(sx, sy));
        while (!q.empty()) {
            int pos = q.front();
            q.pop();
            int x = pos / m, y = pos % m;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (vis[id(nx, ny)]) continue;
                if (grid[nx][ny] == 0) continue;
                vis[id(nx, ny)] = true;
                megre(pos, id(nx, ny));
                q.push(id(nx, ny));
            }
        }
    }

   public:
    vector<int> hitBricks(vector<vector<int> > &grid,
                          vector<vector<int> > &hits) {
        n = grid.size();
        m = grid[0].size();
        vector<bool> badflag(hits.size(), false);
        for (int i = 0; i < hits.size(); i++) {
            if (grid[hits[i][0]][hits[i][1]] != 0) {
                grid[hits[i][0]][hits[i][1]] = 0;
            } else {
                badflag[i] = true;
            }
        }
        fa = vector<int>(n * m);
        fc = vector<int>(n * m, 1);
        for (int i = 0; i < n * m; i++) {
            fa[i] = i;
        }
        vector<bool> vis(n * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[id(i, j)] && grid[i][j] == 1) bfs(i, j, vis, grid);
            }
        }

        // add hits
        vector<int> ans;
        for (int i = hits.size() - 1; i >= 0; i--) {
            int x = hits[i][0], y = hits[i][1];
            if (badflag[i]) {
                ans.push_back(0);
                continue;
            }
            bool can_up = false, all_up = true;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (grid[nx][ny] == 0) continue;
                int cur_fa = getfa(id(nx, ny));
                if (cur_fa / m != 0) {
                    all_up = false;
                } else {
                    can_up = true;
                }
            }
            if (x == 0) can_up = true;
            if (can_up == true && all_up == false) {
                int count = 0;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (grid[nx][ny] == 0) continue;
                    int cur_fa = getfa(id(nx, ny));
                    if (cur_fa / m != 0 && cur_fa != getfa(id(x, y))) {
                        count += fc[cur_fa];
                    }
                    megre(id(nx, ny), id(x, y));
                }
                ans.push_back(count);
            } else {
                ans.push_back(0);
            }
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (grid[nx][ny] == 0) continue;
                megre(id(x, y), id(nx, ny));
            }

            grid[x][y] = 1;
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};