#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 505;
const int maxm = 1e5 + 10;

int f[maxm];
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        int cost, value; 
        scanf("%d%d", &cost, &value);
        for(int j = m; j >= cost; j--) {
            f[j] = max(f[j - cost] + value, f[j]);
        }
    }
    printf("%d\n", f[m]);
    return 0;
}