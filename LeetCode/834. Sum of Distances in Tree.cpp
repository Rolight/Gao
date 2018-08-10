#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    vector<int> ch_dis, fa, sz, dis;
    unordered_map<int, vector<int> > e;
    int N;

    int dfs(int now, int now_fa) {
        // printf("%d\n", now);
        fa[now] = now_fa;
        sz[now] = 1;
        vector<int> &edges = e[now];
        for (int ch : edges) {
            if (ch == now_fa) continue;
            sz[now] += dfs(ch, now);
            ch_dis[now] += ch_dis[ch] + sz[ch];
        }
        return sz[now];
    }

    void dfs1(int now) {
        vector<int> &edges = e[now];
        if (fa[now] == -1)
            dis[now] = ch_dis[now];
        else {
            int fa_dis_ex = dis[fa[now]] - sz[now] - ch_dis[now];
            int fa_sz_ex = N - sz[now];
            dis[now] = ch_dis[now] + fa_dis_ex + fa_sz_ex;
        }
        for (int ch : edges) {
            if (ch == fa[now]) continue;
            dfs1(ch);
        }
    }

   public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int> > &edges) {
        sz = fa = dis = ch_dis = vector<int>(N, 0);
        this->N = N;
        for (int i = 0; i < edges.size(); i++) {
            e[edges[i][0]].push_back(edges[i][1]);
            e[edges[i][1]].push_back(edges[i][0]);
        }
        dfs(0, -1);
        // printf("sz: ");
        // for(int i = 0; i < N; i++) printf("%d ", sz[i]); puts("");
        // printf("ch_dis: ");
        // for(int i = 0; i < N; i++) printf("%d ", ch_dis[i]); puts("");
        dfs1(0);
        return dis;
    }
};