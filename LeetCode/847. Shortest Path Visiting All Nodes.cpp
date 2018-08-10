#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 15;

int dis[maxn][maxn];
int f[maxn][1 << maxn];

class Solution {
    int N;

    int dfs(int now, int state) {
        if (state == ((1 << N) - 1)) return 0;
        int ret = 1e9;
        if (f[now][state] != -1) return f[now][state];
        for (int i = 0; i < N; i++) {
            if ((state & (1 << i))) continue;
            if (dis[now][i] == -1) continue;
            ret = min(ret, dfs(i, state | (1 << i)) + dis[now][i]);
        }
        f[now][state] = ret;
        return ret;
    }

   public:
    int shortestPathLength(vector<vector<int> > &graph) {
        memset(dis, -1, sizeof(dis));
        memset(f, -1, sizeof(f));
        N = graph.size();
        for (int i = 0; i < N; i++) {
            int m = graph[i].size();
            for (int j = 0; j < m; j++) {
                dis[i][graph[i][j]] = 1;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    if (dis[i][k] == -1) continue;
                    if (dis[k][j] == -1) continue;
                    if (dis[i][j] == -1 || dis[i][j] > dis[i][k] + dis[k][j]) {
                        dis[i][j] = dis[i][k] + dis[k][j];
                    }
                }
            }
        }

        int ans = 1e9;
        for (int i = 0; i < N; i++) {
            ans = min(ans, dfs(i, 1 << i));
        }
        return ans;
    }
};