#include <cstdio>
#include <cstring>
#include <set>

#define lson rt<<1, l, mid
#define rson rt<<1 | 1, mid + 1, r

const int maxn = 1e5 + 10;

int sum[maxn << 2], n;
int arr[maxn];

inline void pushup(int rt) {
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void build(int rt, int l, int r) {
    if (l == r) {
        sum[rt] = 1;
    } else {
        int mid = (l + r) / 2;
        build(lson);
        build(rson);
        pushup(rt);
    }
}

void update(int rt, int l, int r, int pos, int v) {
    if (l == r) {
        sum[rt] = v;
    } else {
        int mid = (l + r) / 2;
        if (pos <= mid) {
            update(lson, pos, v);
        } else {
            update(rson, pos, v);
        }
        pushup(rt);
    }
}

int query(int val) {
    int rt = 1, l = 1, r = n;
    while (l <= r) {
        int lsum = sum[rt << 1];
        int mid = (l + r) >> 1;
        if (l == r) {
            return l;
        }
        if (val <= lsum) {
            r = mid;
            rt = rt << 1;
        } else {
            val -= lsum;
            l = mid + 1;
            rt = rt << 1 | 1;
        }
    }
    return -1;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        build(1, 1, n);
        bool bad = true;
        int maxv = n, minv = 1;
        for(int i = n; i > 2; i--) {
            int pivot = (i - 1) / 2;
            int pos = query(pivot);
            // printf("pivot = %d\n", pivot);
            // printf("pos = %d, arr[pos] = %d\n", pos, arr[pos]);
            if (arr[pos] == maxv) {
                update(1, 1, n, pos, 0);
                maxv--;
            } else if (arr[pos] == minv) {
                update(1, 1, n, pos, 0);
                minv++;
            } else {
                bad = false;
                break;
            }
        }
        printf("Case #%d: %s\n", kase, bad ? "YES" : "NO");
    }
    return 0;
}
