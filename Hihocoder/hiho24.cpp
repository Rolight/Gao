#include <cstdio>
#include <algorithm>

using namespace std;
const int maxn = 128;
const int inf = 4e8;
int dis[maxn][maxn];
int N, M;

int main() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            dis[i][j] = inf;
        }
        dis[i][i] = 0;
    }
    for(int i = 1; i <= M; i++) {
        int u, v, w; 
        scanf("%d%d%d", &u, &v, &w);
        dis[u][v] = dis[v][u] = min(dis[u][v], w);
    }
    for(int k = 1; k <= N; k++) {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            printf("%d ", dis[i][j]);
        }
        puts("");
    }
    return 0;
}