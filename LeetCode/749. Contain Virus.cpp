#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

typedef pair<int, int> PII;
typedef pair<PII, PII> Wall;

bool vis[55][55];

class Solution {
    set<Wall> walls;
    int n, m;

    Wall make_wall(int x1, int y1, int x2, int y2) {
        PII p1 = make_pair(x1, y1), p2 = make_pair(x2, y2);
        if (p1 > p2) swap(p1, p2);
        return make_pair(p1, p2);
    }

    set<Wall> gao(vector<vector<int> > &grid, int x, int y) {
        set<Wall> walls;
        queue<PII> q;
        q.push(make_pair(x, y));
        vis[x][y] = true;
        while (!q.empty()) {
            PII cur_pos = q.front();
            q.pop();
            int cx = cur_pos.first, cy = cur_pos.second;
            printf("%d %d->", cx, cy);
            for (int i = 0; i < 4; i++) {
                int nx = dx[i] + cx, ny = dy[i] + cy;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (this->walls.count(make_wall(cx, cy, nx, ny)) > 0) continue;
                if (grid[nx][ny] == 1) {
                    if (vis[nx][ny]) continue;
                    q.push(make_pair(nx, ny));
                    vis[nx][ny] = true;
                } else {
                    walls.insert(make_wall(cx, cy, nx, ny));
                }
            }
        }
        printf("shoud %d\n", (int)walls.size());
        return walls;
    }

    int expand_value(set<Wall> &walls, vector<vector<int> > &grid) {
        set<PII> epos;
        for (set<Wall>::iterator iter = walls.begin(); iter != walls.end();
             ++iter) {
            if (grid[iter->first.first][iter->first.second] == 0) {
                epos.insert(iter->first);
            } else {
                epos.insert(iter->second);
            }
        }
        return epos.size();
    }

    int round(vector<vector<int> > &grid) {
        memset(vis, 0, sizeof(vis));
        vector<set<Wall> > statistics;
        int target = -1, target_val = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && grid[i][j] == 1) {
                    statistics.push_back(gao(grid, i, j));
                    int cur_value = expand_value(statistics.back(), grid);
                    if (cur_value > target_val) {
                        target_val = cur_value;
                        target = statistics.size() - 1;
                    }
                }
            }
        }
        printf("target_val = %d\n", target_val);
        if (target_val <= 0) return -1;
        // build wall
        for (set<Wall>::iterator iter = statistics[target].begin();
             iter != statistics[target].end(); ++iter) {
            this->walls.insert(*iter);
        }
        // expand virus
        for (int i = 0; i < statistics.size(); i++) {
            if (i == target) continue;
            for (set<Wall>::iterator iter = statistics[i].begin();
                 iter != statistics[i].end(); ++iter) {
                if (this->walls.count(*iter) == 0) {
                    grid[iter->first.first][iter->first.second] = 1;
                    grid[iter->second.first][iter->second.second] = 1;
                }
            }
        }
        return statistics[target].size();
    }

   public:
    int containVirus(vector<vector<int> > &grid) {
        n = grid.size();
        m = grid[0].size();
        int ans = 0;
        while (true) {
            int ret = round(grid);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    printf("%d", grid[i][j]);
                }
                puts("");
            }
            if (ret <= 0) break;
            ans += ret;
        }
        return ans;
    }
};