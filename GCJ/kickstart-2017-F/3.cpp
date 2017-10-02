#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100;
const int maxp = 300;
const int INF = 1e8;

long double f[maxn][maxp], g[maxn][maxp];

int dis[maxn][maxn];
int n, m, p;

int main() {
    int T; scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d%d%d", &n, &m, &p);
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if (i == j) dis[i][j] = 0;
                else dis[i][j] = INF;
            }
        }
        for(int i = 1; i <= m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            dis[u][v] = dis[v][u] = std::min(dis[u][v], w);
        }
        // floyd
        for(int k = 1; k <= n; k++) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    dis[i][j] = std::min(
                            dis[i][j],
                            dis[i][k] + dis[k][j]);
                }
            }
        }
        // dp
        g[1][0] = 1;
        for(int pp = 1; pp <= p; pp++) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) if (j != i) {
                    g[i][pp] += g[j][pp - 1];
                    f[i][pp] += f[j][pp - 1] + g[j][pp - 1] * dis[j][i];
                }
            }
        }
        double ans = 0;
        for(int i = 1; i <= n; i++) {
            for(int pp = 1; pp <= p; pp++) {
                f[i][p] /= (n - 1);
            }
            ans += f[i][p];
        }
        printf("Case #%d: %.8f\n", kase, ans);
    }
    return 0;
}
