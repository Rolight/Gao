#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;
int head[maxn], nxt[maxn << 1], v[maxn << 1], ecnt;
int f[maxn], g[maxn], h[maxn];

void adde(int _u, int _v) {
    v[ecnt] = _v;
    nxt[ecnt] = head[_u];
    head[_u] = ecnt++;
}

void maintain(int &m, int &mm, int cur) {
    if(cur >= m) {
        mm = m;
        m = cur;
    } else {
        mm = max(mm, cur);
    }
}

void dfs(int now, int nowfa) {
    int max_val = 0, second_max_val = 0;
    f[now] = 1;
    g[now] = 1;
    h[now] = 1;
    for(int i = head[now]; i != -1; i = nxt[i]) {
        if(v[i] == nowfa) continue;
        dfs(v[i], now);
        maintain(max_val, second_max_val, h[v[i]]);
        f[now] = max(f[now], f[v[i]]);
        h[now] = max(h[now], h[v[i]] + 1);
    }
    g[now] = 1 + max_val + second_max_val;
    f[now] = max(f[now], g[now]);
    // printf("%d: %d ,%d\n", now, f[now], g[now]);
    // printf("%d, %d\n", max_val, second_max_val);
}

int main() {
    int n;
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    ecnt = 0;
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        adde(a, b);
        adde(b, a);
    }
    dfs(1, -1);
    printf("%d\n", f[1] - 1);
    return 0;
}