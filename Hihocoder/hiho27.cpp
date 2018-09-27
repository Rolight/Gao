#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int maxn = 1e5 + 10;
const int maxm = 1e6 + 10;
const int INF = 2e9;

int head[maxn], nxt[maxm << 1], v[maxm << 1], w[maxm << 1], ecnt;
int N, M, S, T;
int d[maxn], vis[maxn];

int fa[maxn];

int getfa(int x) {
    return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}

bool uni(int x, int y) {
    int fax = getfa(x), fay = getfa(y);
    if(fax == fay) {
        return false;
    }
    fa[fax] = fay;
    return true;
}

struct Node {
    int u, v, dis;
    Node(int u, int v, int dis): u(u), v(v), dis(dis) {}
    bool operator < (const Node &x) const {
        return dis < x.dis;
    }
};

int main() {
    scanf("%d%d", &N, &M);
    int ans = 0;
    vector<Node> nodes;
    for(int i = 1; i <= N; i++) fa[i] = i;
    for(int i = 0; i < M; i++) {
        int uu, vv, ww;
        scanf("%d%d%d", &uu, &vv, &ww);
        nodes.push_back(Node(uu, vv, ww));
    }
    sort(nodes.begin(), nodes.end());
    for(int i = 0; i < M; i++) {
        if(uni(nodes[i].u, nodes[i].v)) {
            ans += nodes[i].dis;
        }
    }
    printf("%d\n", ans);
    return 0;
}