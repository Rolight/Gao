#include <cstdio>
#include <algorithm>

const int maxn = 1e6 + 10;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

using namespace std;

int minv[maxn << 2];
int val[maxn];

void pushUp(int rt) {
    minv[rt] = min(minv[rt << 1], minv[rt << 1 | 1]);
}

void build(int rt, int l, int r) {
    if(l == r) minv[rt] = val[l];
    else {
        int mid = (l + r) / 2;
        build(lson);
        build(rson);
        pushUp(rt);
    }
}

void update(int rt, int l, int r, int pos, int val) {
    if(l == r) minv[rt] = val;
    else {
        int mid = (l + r) / 2;
        if(pos <= mid) update(lson, pos, val);
        else update(rson, pos, val);
        pushUp(rt);
    }
}

int query(int rt, int l, int r, int ql, int qr) {
    if(ql <= l && qr >= r) return minv[rt];
    int ret = 1e9;
    int mid = (l + r) / 2;
    if(ql <= mid) ret = min(query(lson, ql, qr), ret);
    if(qr > mid) ret = min(query(rson, ql, qr), ret);
    return ret;
}

int main() {
    int n, buf;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    build(1, 1, n);
    int q; 
    scanf("%d", &q);
    int cmd, a, b;
    for(int i = 0; i < q; i++) {
        scanf("%d%d%d", &cmd, &a, &b);
        if(cmd == 1) update(1, 1, n, a, b);
        else printf("%d\n", query(1, 1, n, a, b));
    }
    return 0;
}