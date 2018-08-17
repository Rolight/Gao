#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int maxn = 30;
const int maxS = 1 << 6;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

bool vis[maxn][maxn][maxS][maxS];

class Node {
   public:
    int x, y, s1, s2, step;
    Node(int x, int y, int s1, int s2, int step)
        : x(x), y(y), s1(s1), s2(s2), step(step) {}
};

class Solution {
    int n, m;

    bool isLock(char c) { return c >= 'A' && c <= 'Z'; }

    bool isKey(char c) { return c >= 'a' && c <= 'z'; }

    bool check_bit(int s, int pos) { return s & (1 << pos); }

    int bfs(int sx, int sy, int lock_size, vector<string> &grid) {
        queue<Node> q;
        q.push(Node(sx, sy, 0, 0, 0));
        vis[sx][sy][0][0] = true;
        int target_mask = (1 << lock_size) - 1;
        while (!q.empty()) {
            Node now = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = now.x + dx[i], ny = now.y + dy[i];
                int ns1 = now.s1, ns2 = now.s2;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (grid[nx][ny] == '#') continue;
                if (isLock(grid[nx][ny])) {
                    int lock_bit = grid[nx][ny] - 'A';
                    if (!check_bit(now.s2, lock_bit)) {
                        if (!check_bit(now.s1, lock_bit)) {
                            continue;
                        } else {
                            ns2 ^= (1 << lock_bit);
                        }
                    }
                } else if (isKey(grid[nx][ny])) {
                    int lock_bit = grid[nx][ny] - 'a';
                    if (!check_bit(now.s1, lock_bit)) {
                        ns1 ^= (1 << lock_bit);
                    }
                }
                if (vis[nx][ny][ns1][ns2]) {
                    continue;
                }
                vis[nx][ny][ns1][ns2] = true;
                if (ns1 == target_mask) return now.step + 1;
                q.push(Node(nx, ny, ns1, ns2, now.step + 1));
            }
        }
        return -1;
    }

   public:
    int shortestPathAllKeys(vector<string> &grid) {
        n = grid.size();
        m = grid[0].length();
        memset(vis, 0, sizeof(vis));
        int sx, sy;
        vector<int> locks;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '@') {
                    sx = i;
                    sy = j;
                } else if (grid[i][j] >= 'A' && grid[i][j] <= 'Z') {
                    locks.push_back(grid[i][j]);
                }
            }
        }
        int ans = bfs(sx, sy, locks.size(), grid);
        return ans;
    }
};