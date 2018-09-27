#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 1e5 + 10;
const int maxm = 1e6 + 10;
const int INF = 2e9;

int head[maxn], nxt[maxm << 1], v[maxm << 1], w[maxm << 1], ecnt;
int N, M, S, T;
int d[maxn], vis[maxn];

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

struct Node {
    int node, dis;
    Node(int node, int dis): node(node), dis(dis) {}
    bool operator < (const Node &x) const {
        return dis > x.dis;
    }
};

void dijkstra() {
    for(int i = 1; i <= N; i++) d[i] = INF;
    d[S] = 0;
    priority_queue<Node> pq;
    pq.push(Node(S, d[S]));
    memset(vis, 0, sizeof(vis));
    while(!pq.empty()) {
        Node now = pq.top();
        pq.pop();
        if(vis[now.node]) continue;
        vis[now.node] = true;
        for(int i = head[now.node]; i != -1; i = nxt[i]) {
            if(d[v[i]] > d[now.node] + w[i]) {
                d[v[i]] = d[now.node] + w[i];
                pq.push(Node(v[i], d[v[i]]));
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &N, &M, &S, &T);
    init();
    for(int i = 0; i < M; i++) {
        int uu, vv, ww;
        scanf("%d%d%d", &uu, &vv, &ww);
        adde(uu, vv, ww);
        adde(vv, uu, ww);
    }
    dijkstra();
    printf("%d\n", d[T]);
    return 0;
}