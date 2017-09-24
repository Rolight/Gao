#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 1e6 + 10;
int arr[maxn], e, n;

int main() {
    int T; scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d%d", &e, &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &arr[i]);
        }
        std::sort(arr + 1, arr + 1 + n);
        int l = 1, r = n;
        int maxh = 0, h = 0;
        while(l <= r) {
            if (e > arr[l]) {
                ++h;
                e -= arr[l];
                l++;
                maxh = std::max(maxh, h);
            } else if (h > 0) {
                h--;
                e += arr[r];
                r--;
            } else {
                break;
            }
        }
        printf("Case #%d: %d\n", kase, maxh);
    }
    return 0;
}
