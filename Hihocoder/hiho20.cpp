#include <cstdio>
#include <algorithm>

const int maxn = 1e6 + 10;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

using namespace std;

int sumv[maxn << 2], lazy[maxn << 2];
int val[maxn];

void pushUp(int rt) {
    sumv[rt] = sumv[rt << 1] + sumv[rt << 1 | 1];
}

void cover(int rt, int l, int r, int val) {
    sumv[rt] = (r - l + 1) * val;
    lazy[rt] = val;
}

void pushDown(int rt, int l, int r) {
    if(lazy[rt] == -1) return;
    int mid = (l + r) / 2;
    cover(lson, lazy[rt]);
    cover(rson, lazy[rt]);
    lazy[rt] = -1;
}

void build(int rt, int l, int r) {
    lazy[rt] = -1;
    if(l == r) sumv[rt] = val[l];
    else {
        int mid = (l + r) / 2;
        build(lson);
        build(rson);
        pushUp(rt);
    }
}

void update(int rt, int l, int r, int ql, int qr, int val) {
    if(ql <= l && qr >= r) {
        cover(rt, l, r, val);
    } else {
        pushDown(rt, l ,r);
        int mid = (l + r) / 2;
        if(ql <= mid) update(lson, ql, qr, val);
        if(qr > mid) update(rson, ql, qr, val);
        pushUp(rt);
    }
}

int query(int rt, int l, int r, int ql, int qr) {
    if(ql <= l && qr >= r) return sumv[rt];
    int ret = 0;
    int mid = (l + r) / 2;
    pushDown(rt, l, r);
    if(ql <= mid) ret += query(lson, ql, qr); 
    if(qr > mid) ret += query(rson, ql, qr);
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
    int cmd, a, b, c;
    for(int i = 0; i < q; i++) {
        scanf("%d%d%d", &cmd, &a, &b);
        if(cmd == 1) {
            scanf("%d", &c);
            update(1, 1, n, a, b, c);
        }
        else printf("%d\n", query(1, 1, n, a, b));
    }
    return 0;
}