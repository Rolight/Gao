#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;
const int maxm = 21;

int f[maxn][maxm];
int arr[maxn];
int N;

void initRMQ() {
    for(int i = 1; i <= N; i++) f[i][0] = arr[i];
    for(int k = 1; (1 << k) < N; k++) {
        for(int i = 1; i + (1 << k) <= N + 1; i++) {
            f[i][k] = min(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int query(int a, int b) {
    int len = b - a + 1;
    int k = 0;
    while(1 << (k + 1) <= len) ++k;
    return min(f[a][k], f[b - (1 << k) + 1][k]);
}

int main() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) scanf("%d", &arr[i]);
    int k;
    initRMQ();
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }
    return 0;
}