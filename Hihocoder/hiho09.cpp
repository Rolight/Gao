#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

const int maxn = 1024;
const int maxm = 5;
const int maxs = 1 << 5;
const LL mod = 1e9 + 7;

int n, m;
LL f[maxn][maxm][maxs];

int main() {
    scanf("%d%d", &n, &m);
    int smask = (1 << m) - 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == 0 && j == 0) {
                f[i][j][(smask << 1) & smask] = 1;
                continue;
            }
            for(int s = 0; s < (1 << m); s++) {
                if(i == 0 && (s >> j) != (smask >> j)) continue;
                if(j > 0) {
                    if((s & 1) == 0 && (s & (1 << (m - 1))) != 0) {
                        f[i][j][(s << 1 | 3) & smask] += f[i][j - 1][s];
                    }
                    if((s & (1 << (m - 1))) == 0) {
                        f[i][j][(s << 1 | 1) & smask] += f[i][j - 1][s];
                    } else  {
                        f[i][j][(s << 1) & smask] += f[i][j - 1][s];
                    }
                } else {
                    if((s & (1 << (m - 1))) == 0) {
                        f[i][j][(s << 1 | 1) & smask] += f[i - 1][m - 1][s];
                    } else {
                        f[i][j][(s << 1) & smask] += f[i - 1][m - 1][s];
                    }
                }
            }
            for(int s = 0; s < (1 << m); s++) {
                // printf("%d %d %d: %lld\n", i, j, s, f[i][j][s]);
                f[i][j][s] %= mod;
            }
        }
    }
    printf("%lld\n", f[n - 1][m - 1][smask]);
    return 0;
}