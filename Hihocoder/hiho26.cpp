#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;
const int maxn = 1e3 + 10;
const int inf = 4e8;
int dis[maxn][maxn];
int N;
int vis[maxn];

struct Node {
    int node, dis;
    Node(int node, int dis): node(node), dis(dis) {}
    bool operator < (const Node &x) const {
        return dis > x.dis;
    }
};

int main() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            scanf("%d", &dis[i][j]);
        }
    }
    priority_queue<Node> pq;
    vis[1] = 1;
    int ans = 0;
    for(int i = 2; i <= N; i++) {
        pq.push(Node(i, dis[1][i]));
    }
    while(!pq.empty()) {
        Node now = pq.top();
        pq.pop();
        if(vis[now.node]) continue;
        vis[now.node] = 1;
        ans += now.dis;
        for(int i = 1; i <= N; i++) {
            if(vis[i]) continue;
            pq.push(Node(i, dis[now.node][i]));
        }
    }
    printf("%d\n", ans);
    return 0;
}