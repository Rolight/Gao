#include <vector>

using namespace std;

class Solution {
    vector<int> head, nxt, v, id;
    vector<int> indeg, outdeg;
    vector<bool> incyc, vis;
    bool found_cyc;

    void addedge(int u, int v, int id) {
        int ecnt = this->v.size();
        this->v.push_back(v);
        this->nxt.push_back(head[u]);
        this->id.push_back(id);
        head[u] = ecnt;
    }

    int find_cyc(int now) {
        vis[now] = true;
        for (int i = head[now]; i != -1; i = nxt[i]) {
            int v = this->v[i];
            if (vis[v]) {
                incyc[id[i]] = true;
                found_cyc = true;
                return v;
            }
            int ret = find_cyc(v);
            if (ret == -1) continue;
            incyc[id[i]] = true;
            if (ret == now) {
                return -1;
            } else {
                return ret;
            }
        }
        vis[now] = false;
        return -1;
    }

   public:
    vector<int> findRedundantDirectedConnection(vector<vector<int> > &edges) {
        incyc = vector<bool>(edges.size() + 1, false);
        head = vector<int>(edges.size() + 1, -1);
        id.clear();
        nxt.clear();
        v.clear();
        found_cyc = false;
        indeg = vector<int>(edges.size() + 1, 0);
        outdeg = vector<int>(edges.size() + 1, 0);
        for (int i = 0; i < edges.size(); i++) {
            printf("add %d %d\n", edges[i][0], edges[i][1]);
            addedge(edges[i][0], edges[i][1], i);
            indeg[edges[i][1]]++;
            outdeg[edges[i][0]]++;
        }
        int root = -1;
        int bad = -1;
        for (int i = 1; i <= edges.size(); i++) {
            if (indeg[i] > 1) {
                bad = i;
            }
        }
        vis = vector<bool>(edges.size() + 1, false);
        for (int i = 1; i <= edges.size(); i++) {
            find_cyc(i);
            if (found_cyc) break;
        }
        printf("cyc: \n");
        for (int i = 0; i < edges.size(); i++) {
            if (!incyc[i]) continue;
            printf("%d %d\n", edges[i][0], edges[i][1]);
        }
        if (bad != -1) {
            vector<int> bad_edge_id;
            printf("bad = %d\n", bad);
            for (int i = 0; i < edges.size(); i++) {
                if (edges[i][1] == bad) {
                    if (incyc[i]) {
                        return edges[i];
                    }
                    bad_edge_id.push_back(i);
                }
            }
            return edges[bad_edge_id.back()];
        } else {
            int ans_id = -1;
            for (int i = 0; i < edges.size(); i++) {
                if (incyc[i]) {
                    ans_id = i;
                }
            }
            return edges[ans_id];
        }
    }
};