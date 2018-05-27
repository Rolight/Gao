#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

const int maxn = 16;
const int N = maxn * maxn;
int L[maxn][maxn], eid[maxn][maxn];
int n;
vector<pair<int, int> > edges;

vector<int> elen;
bool check(bitset<N> choose_mask) {
    elen.clear();
    for (int i = 0; i < edges.size(); i++) {
        if (choose_mask[i]) {
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

int dfs(bitset<N> choose_mask, bitset<N> remain_mask) {
    int ret = 0;
    // printf("%d %d\n", choose_mask, remain_mask);
    if (check(choose_mask)) ++ret;
    if (remain_mask == 0) return ret;
    int last = -1;
    for (int i = 0; i < edges.size(); i++) {
        if (choose_mask[i]) last = i;
    }
    for (int i = last + 1; i < edges.size(); i++) {
        if (remain_mask[i]) {
            bitset<N> n_choose_mask = choose_mask;
            n_choose_mask.set(i);
            int u = edges[i].first, v = edges[i].second;
            bitset<N> n_remain_mask = remain_mask;
            n_remain_mask.set(i, 0);
            for (int j = 1; j <= n; j++) {
                if (L[u][j] != 0 && (n_remain_mask[eid[u][j]])) {
                    n_remain_mask.flip(eid[u][j]);
                }
                if (L[v][j] != 0 && (n_remain_mask[eid[v][j]])) {
                    n_remain_mask.flip(eid[v][j]);
                }
            }
            ret += dfs(n_choose_mask, n_remain_mask);
        }
    }
    return ret;
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
        // printf("edge size = %d\n", (int)edges.size());
        bitset<N> choose_mask, remain_mask;
        remain_mask.flip();
        int ans = dfs(choose_mask, remain_mask);
        fprintf(stderr, "Case #%d: %d\n", kase, ans);
        printf("Case #%d: %d\n", kase, ans);
    }
    return 0;
}