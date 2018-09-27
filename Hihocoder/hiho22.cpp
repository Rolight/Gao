#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

const int maxn = 1e6 + 10;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

using namespace std;

int lazy_addv[maxn << 2], lazy_cover[maxn << 2], sumv[maxn << 2];
int val[maxn];

void pushUp(int rt) {
    sumv[rt] = sumv[rt << 1] + sumv[rt << 1 | 1];
}

void cover(int rt, int l, int r, int val) {
    sumv[rt] = (r - l + 1) * val;
    lazy_cover[rt] = val;
    lazy_addv[rt] = 0;
}

void addv(int rt, int l, int r, int val) {
    sumv[rt] += (r - l + 1) * val;
    lazy_addv[rt] += val;
}

void pushDown(int rt, int l, int r) {
    int mid = (l + r) / 2;
    if(lazy_cover[rt] != -1) {
        cover(lson, lazy_cover[rt]);
        cover(rson, lazy_cover[rt]);
        lazy_cover[rt] = -1;
    } 
    if(lazy_addv[rt] != 0) {
        addv(lson, lazy_addv[rt]);
        addv(rson, lazy_addv[rt]);
        lazy_addv[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    lazy_cover[rt] = -1;
    lazy_addv[rt] = 0;
    if(l == r) sumv[rt] = val[l];
    else {
        int mid = (l + r) / 2;
        build(lson);
        build(rson);
        pushUp(rt);
    }
}

void update_cover(int rt, int l, int r, int ql, int qr, int val) {
    if(ql <= l && qr >= r) {
        cover(rt, l, r, val);
    } else {
        pushDown(rt, l ,r);
        int mid = (l + r) / 2;
        if(ql <= mid) update_cover(lson, ql, qr, val);
        if(qr > mid) update_cover(rson, ql, qr, val);
        pushUp(rt);
    }
}

void update_addv(int rt, int l, int r, int ql, int qr, int val) {
    if(ql <= l && qr >= r) {
        addv(rt, l, r, val);
    } else {
        pushDown(rt, l ,r);
        int mid = (l + r) / 2;
        if(ql <= mid) update_addv(lson, ql, qr, val);
        if(qr > mid) update_addv(rson, ql, qr, val);
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
    int N, L;
    scanf("%d%d", &N, &L);
    ++N;
    for(int i = 1; i <= N; i++) scanf("%d", &val[i]);
    build(1, 1, N);
    // for(int j = 1; j <= N; j++) printf("%d ", query(1, 1, N, j, j)); puts("");
    for(int i = 1; i <= L; i++) {
        int cmd, ql, qr, val;
        scanf("%d%d%d%d", &cmd, &ql, &qr, &val);
        ++ql;
        ++qr;
        if(cmd == 0) update_addv(1, 1, N, ql, qr, val);
        else update_cover(1, 1, N, ql, qr, val);
        // for(int j = 1; j <= N; j++) printf("%d ", query(1, 1, N, j, j)); puts("");
        printf("%d\n", sumv[1]);
    }
    return 0;
}