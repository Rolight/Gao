#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1024;
const int maxs = 1 << 10;

int f[maxn][maxs];
int n, m, q;
int w[maxn];
int bcount[maxs];

inline int get_bitcount(int x) {
    return x == 0 ? 0 : get_bitcount(x >> 1) + (x & 1);
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for(int i = 0; i < maxs; i++) bcount[i] = get_bitcount(i);
    int smask = (1 << m) - 1;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < (1 << m); j++) {
            int &not_clean = f[i][smask & (j << 1)];
            int &clean = f[i][smask & (j << 1 | 1)];
            not_clean = max(not_clean, f[i - 1][j]);
            if(bcount[smask & (j << 1 | 1)] <= q) {
                clean = max(clean, f[i - 1][j] + w[i]);
            }
            ans = max(ans, not_clean);
            ans = max(ans, clean);
        }
        // printf("%d: %d\n", i, ans);
    }
    printf("%d\n", ans);
    return 0;
}