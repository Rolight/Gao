#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int maxn = 1024;

vector<pair<int, int> > edges;
int head[maxn], v[maxn << 1], nxt[maxn << 1], ecnt;
int n;
int fa[maxn];
int dis[maxn];
bool incyc[maxn];

void addedge(int a, int b) {
    v[ecnt] = b;
    nxt[ecnt] = head[a];
    head[a] = ecnt++;
}

int findfa(int x) { return x == fa[x] ? x : fa[x] = findfa(fa[x]); }

pair<int, int> find_cyc() {
    // init union set
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 0; i < edges.size(); i++) {
        int y1 = findfa(edges[i].first), y2 = findfa(edges[i].second);
        if (y1 == y2) return edges[i];
        fa[y1] = y2;
    }
}

bool vis[maxn];
bool dfs(int cur, int str, int end) {
    incyc[cur] = true;
    if (cur == end) return true;
    for (int i = head[cur]; i != -1; i = nxt[i]) {
        if (cur == str && v[i] == end) continue;
        if (vis[v[i]]) continue;
        vis[v[i]] = true;
        if (dfs(v[i], str, end)) {
            return true;
        }
    }
    incyc[cur] = false;
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d", &n);
        memset(head, -1, sizeof(head));
        ecnt = 0;
        edges.clear();
        // read edges
        for (int i = 1; i <= n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            edges.push_back(make_pair(a, b));
            addedge(a, b);
            addedge(b, a);
        }
        // find cycle
        pair<int, int> cyc_e = find_cyc();
        memset(incyc, 0, sizeof(incyc));
        memset(vis, 0, sizeof(vis));
        int str = cyc_e.first;
        vis[str] = true;
        dfs(str, str, cyc_e.second);
        queue<pair<int, int> > q;
        memset(dis, -1, sizeof(dis));
        for (int i = 1; i <= n; i++) {
            if (incyc[i]) {
                q.push(make_pair(i, 0));
                dis[i] = 0;
            }
        }
        while (!q.empty()) {
            pair<int, int> now = q.front();
            q.pop();
            int cur = now.first, curd = now.second;
            for (int i = head[cur]; i != -1; i = nxt[i]) {
                if (incyc[v[i]]) continue;
                if (dis[v[i]] != -1 && dis[v[i]] <= curd + 1) continue;
                dis[v[i]] = curd + 1;
                q.push(make_pair(v[i], dis[v[i]]));
            }
        }
        printf("Case #%d:", kase);
        for (int i = 1; i <= n; i++) {
            printf(" %d", dis[i]);
        }
        puts("");
    }
    return 0;
}