#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int maxn = 1e5 + 10;
const int maxm = 1e6 + 10;
const int inf = 4e8;
int N, M;
int vis[maxn];
int head[maxn], nxt[maxm << 1], v[maxm << 1], w[maxm << 1], ecnt;

struct Node {
    int node, dis;
    Node(int node, int dis): node(node), dis(dis) {}
    bool operator < (const Node &x) const {
        return dis > x.dis;
    }
};

void init() {
    ecnt = 0;
    memset(head, -1, sizeof(head));
}

void adde(int _u, int _v, int _w) {
    w[ecnt] = _w;
    v[ecnt] = _v;
    nxt[ecnt] = head[_u];
    head[_u] = ecnt++;
}

int main() {
    scanf("%d%d", &N, &M);
    init();
    for(int i = 0; i < M; i++) {
        int uu, vv, ww;
        scanf("%d%d%d", &uu, &vv, &ww);
        adde(uu, vv, ww);
        adde(vv, uu, ww);
    }
    priority_queue<Node> pq;
    vis[1] = 1;
    int ans = 0;
    for(int i = head[1]; ~i; i = nxt[i]) {
        pq.push(Node(v[i], w[i]));
    }
    while(!pq.empty()) {
        Node now = pq.top();
        pq.pop();
        if(vis[now.node]) continue;
        vis[now.node] = 1;
        ans += now.dis;
        for(int i = head[now.node]; ~i; i = nxt[i]) {
            if(vis[v[i]]) continue;
            pq.push(Node(v[i], w[i]));
        }
    }
    printf("%d\n", ans);
    return 0;
}