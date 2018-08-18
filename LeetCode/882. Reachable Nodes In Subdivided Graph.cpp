#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int maxn = 3005 + 100;
const int maxe = 1e4 + 100;

int head[maxn], nxt[maxe << 1], v[maxe << 1], w[maxe << 1], ecnt;

class Solution {
    void init() {
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    void add_edge(int _u, int _v, int _w) {
        v[ecnt] = _v;
        w[ecnt] = _w;
        nxt[ecnt] = head[_u];
        head[_u] = ecnt++;
    }

    void convert_edges(vector<vector<int> > &edges) {
        for (int i = 0; i < edges.size(); i++) {
            add_edge(edges[i][0], edges[i][1], edges[i][2]);
            add_edge(edges[i][1], edges[i][0], edges[i][2]);
        }
    }

   public:
    int reachableNodes(vector<vector<int> > &edges, int M, int N) {
        init();
        convert_edges(edges);

        // build single source shortest path and DP
        queue<int> q;
        int inf = 1e9;
        vector<int> remain_power(N, -inf), edge_cover(edges.size() * 2, 0);
        vector<bool> inq(N, false);

        q.push(0);
        inq[0] = true;
        remain_power[0] = M;

        while (!q.empty()) {
            int now = q.front();
            q.pop();
            inq[now] = false;
            // printf("cur is %d, remain power is %d\n", now,
            // remain_power[now]);

            for (int i = head[now]; ~i; i = nxt[i]) {
                edge_cover[i] =
                    min(w[i], max(edge_cover[i], remain_power[now]));
                if (remain_power[now] - w[i] - 1 > remain_power[v[i]]) {
                    remain_power[v[i]] = remain_power[now] - w[i] - 1;
                    if (remain_power[v[i]] > 0 && !inq[v[i]]) {
                        q.push(v[i]);
                        inq[v[i]] = true;
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < N; i++) {
            // printf("%d remain power: %d\n", i, remain_power[i]);
            if (remain_power[i] >= 0) {
                ans++;
            }
        }

        for (int i = 0; i < edges.size(); i += 2) {
            // printf("%d cover %d\n", i, edge_cover[i]);
            ans += min(w[i], edge_cover[i] + edge_cover[i ^ 1]);
        }

        return ans;
    }
};