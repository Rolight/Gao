#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

const int maxn = 1e6 + 10;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

using namespace std;

int lazy[maxn << 2], maxv[maxn << 2];
int val[maxn];

void pushUp(int rt) {
    maxv[rt] = max(maxv[rt << 1], maxv[rt << 1 | 1]);
}

void cover(int rt, int l, int r, int val) {
    maxv[rt] = lazy[rt] = val;
}

void pushDown(int rt, int l, int r) {
    if(lazy[rt] == 0) return;
    int mid = (l + r) / 2;
    cover(lson, lazy[rt]);
    cover(rson, lazy[rt]);
    lazy[rt] = 0;
}

void build(int rt, int l, int r) {
    lazy[rt] = 0;
    if(l == r) maxv[rt] = 0;
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
    if(ql <= l && qr >= r) return maxv[rt];
    int ret = 0;
    int mid = (l + r) / 2;
    pushDown(rt, l, r);
    if(ql <= mid) ret = max(ret, query(lson, ql, qr)); 
    if(qr > mid) ret = max(ret, query(rson, ql, qr));
    return ret;
}

int main() {
    int N, L;
    scanf("%d%d", &N, &L);
    vector<int> nums, ql, qr;
    nums.push_back(L);
    for(int i = 0; i < N; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        ql.push_back(a);
        qr.push_back(b);
        nums.push_back(a);
        nums.push_back(b);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    int n = nums.size();
    build(1, 1, n);
    for(int i = 0; i < N; i++) {
        ql[i] = lower_bound(nums.begin(), nums.end(), ql[i]) - nums.begin() + 1;
        qr[i] = lower_bound(nums.begin(), nums.end(), qr[i]) - nums.begin() + 1;
        update(1, 1, n, ql[i], qr[i] - 1, i + 1);
    }
    set<int> st;
    for(int i = 1; i <= n; i++) {
        int ret = query(1, 1, n, i, i);
        if(ret) st.insert(ret);
    }
    printf("%d\n", (int)st.size());
    return 0;
}