#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 128;
int head[maxn], v[maxn << 1], nxt[maxn << 1], ecnt;
int w[maxn];
int n, m;
int f[maxn][maxn];

void adde(int _u, int _v) {
    v[ecnt] = _v;
    nxt[ecnt] = head[_u];
    head[_u] = ecnt++;
}


void dfs(int now, int now_fa) {
    for(int i = 1; i <= m; i++) f[now][i] = w[now];
    for(int i = head[now]; i != -1; i = nxt[i]) {
        if(v[i] == now_fa) continue;
        dfs(v[i], now);
        for(int j = m; j >= 2; j--) {
            for(int k = 1; k < j; k++) {
                f[now][j] = max(f[now][j], f[now][j - k] + f[v[i]][k]);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
    memset(head, -1, sizeof(head));
    ecnt = 0;
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        adde(a, b);
        adde(b, a);
    }
    dfs(1, -1);
    printf("%d\n", f[1][m]);
    return 0;
}