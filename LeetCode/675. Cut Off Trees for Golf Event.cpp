#include <cstdlib>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int vis[50][50];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

class Solution {
    struct PNode {
        int x, y, val;
        bool operator<(const PNode &p) const {
            if (val == p.val) {
                return make_pair(x, y) < make_pair(p.x, p.y);
            } else {
                return val < p.val;
            }
        }
    };
    int n, m;
    int findNext(vector<vector<int> > &forest, int &cur_x, int &cur_y,
                 int tar_height) {
        memset(vis, -1, sizeof(vis));
        queue<pair<int, int> > q;
        if (forest[cur_x][cur_y] == tar_height) {
            return 0;
        }
        q.push(make_pair(cur_x, cur_y));
        vis[cur_x][cur_y] = 0;
        while (!q.empty()) {
            pair<int, int> cur = q.front();

            q.pop();
            int x = cur.first, y = cur.second;
            // printf("%d %d\n", x, y);
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                // printf("bfs: %d %d %d %d\n", nx, ny, forest[nx][ny],
                // vis[nx][ny]);
                if (forest[nx][ny] == tar_height) {
                    cur_x = nx;
                    cur_y = ny;
                    return vis[x][y] + 1;
                }
                if (forest[nx][ny] > 0 && vis[nx][ny] == -1) {
                    vis[nx][ny] = vis[x][y] + 1;
                    q.push(make_pair(nx, ny));
                }
            }
        }
        return -1;
    }

   public:
    int cutOffTree(vector<vector<int> > &forest) {
        n = forest.size();
        m = forest[0].size();
        set<PNode> pos;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (forest[i][j] > 1) {
                    pos.insert(PNode{i, j, forest[i][j]});
                }
            }
        }
        int cur_x = 0, cur_y = 0;
        int mm = pos.size();
        int ans = 0;
        for (int i = 0; i < mm; i++) {
            int ret = findNext(forest, cur_x, cur_y, pos.begin()->val);
            // printf("%d %d %d %d\n", cur_x, cur_y, pos.begin()->val, ret);
            if (ret == -1) return -1;
            pos.erase(PNode{cur_x, cur_y, forest[cur_x][cur_y]});
            forest[cur_x][cur_y] = 1;
            ans += ret;
        }
        return ans;
    }
};