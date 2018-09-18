#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 256;
int arr[maxn][maxn];
int f[maxn][maxn];

int main() {
    int n; scanf("%d", &n);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            scanf("%d", &arr[i][j]);
            f[i][j] = arr[i][j];
            if(i > 0) f[i][j] = std::max(f[i][j], f[i - 1][j] + arr[i][j]);
            if(i > 0 && j > 0) f[i][j] = std::max(f[i][j], f[i - 1][j - 1] + arr[i][j]);
            ans = std::max(ans, f[i][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}