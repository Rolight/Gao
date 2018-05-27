#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

const int maxn = 16;
int L[maxn][maxn], eid[maxn][maxn];
int n;
vector<pair<int, int> > edges;
unordered_map<int, unordered_map<int, int> > f;

vector<int> elen;
bool check(int choose_mask) {
    elen.clear();
    for (int i = 0; i < edges.size(); i++) {
        if (choose_mask & (1 << i)) {
            elen.push_back(L[edges[i].first][edges[i].second]);
        }
    }
    if (elen.size() < 3) return false;
    sort(elen.begin(), elen.end());
    int lsum = 0;
    for (int i = 0; i < elen.size() - 1; i++) {
        lsum += elen[i];
    }
    return lsum > elen.back();
}

int dfs(int choose_mask, int remain_mask) {
    int ret = 0;
    // printf("%d %d\n", choose_mask, remain_mask);
    if (f.count(choose_mask) && f[choose_mask].count(remain_mask)) {
        return f[choose_mask][remain_mask];
    }
    if (check(choose_mask)) ++ret;
    if (remain_mask == 0) return f[choose_mask][remain_mask] = ret;
    int last = -1;
    for (int i = 0; i < edges.size(); i++) {
        if ((1 << i) & choose_mask) last = i;
    }
    for (int i = last + 1; i < edges.size(); i++) {
        if (remain_mask & (1 << i)) {
            int n_choose_mask = choose_mask | (1 << i);
            int u = edges[i].first, v = edges[i].second;
            int n_remain_mask = remain_mask ^ (1 << i);
            for (int j = 1; j <= n; j++) {
                if (L[u][j] != 0 && (n_remain_mask & (1 << eid[u][j]))) {
                    n_remain_mask ^= (1 << eid[u][j]);
                }
                if (L[v][j] != 0 && (n_remain_mask & (1 << eid[v][j]))) {
                    n_remain_mask ^= (1 << eid[v][j]);
                }
            }
            ret += dfs(n_choose_mask, n_remain_mask);
        }
    }
    return f[choose_mask][remain_mask] = ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        scanf("%d", &n);
        edges.clear();
        memset(eid, 0, sizeof(eid));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &L[i][j]);
                if (i < j && L[i][j] != 0) {
                    eid[i][j] = eid[j][i] = edges.size();
                    edges.push_back(make_pair(i, j));
                }
            }
        }
        f.clear();
        // printf("edge size = %d\n", (int)edges.size());
        int ans = dfs(0, (1 << edges.size()) - 1);
        printf("Case #%d: %d\n", kase, ans);
    }
    return 0;
}