#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 1e4 + 10;
const int INF = 1e9;
int T, n;
int f[maxn];

int main() {
    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d", &n);
        for(int i = 0; i <= n; i++) {
            f[i] = INF;
        }
        f[0] = 0;
        for(int i = 1; i * i <= n; i++) {
            for(int j = i * i; j <= n; j++) {
                f[j] = std::min(f[j], f[j - i * i] + 1);
            }
        }
        printf("Case #%d: %d\n", kase, f[n]);
    }
    return 0;
}
