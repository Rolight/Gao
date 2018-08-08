#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

const int mod = 1e9 + 7;

class Solution {
    int N;
    vector<int> sumv, lazy;
    void build() {
        int n = (N + 10);
        sumv = vector<int>(n * 4, 0);
        lazy = vector<int>(n * 4, 0);
    }

    void pushDown(int rt, int l, int r) {
        if (lazy[rt] == 0) return;
        int mid = (l + r) / 2;
        int llen = (mid - l + 1), rlen = r - mid;
        sumv[rt << 1] += lazy[rt] * llen;
        sumv[rt << 1 | 1] += lazy[rt] * rlen;
        sumv[rt << 1] %= mod;
        sumv[rt << 1 | 1] %= mod;
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1] %= mod;
        lazy[rt << 1 | 1] += lazy[rt];
        lazy[rt << 1 | 1] %= mod;
        lazy[rt] = 0;
    }

    void pushUp(int rt) { sumv[rt] = sumv[rt << 1] + sumv[rt << 1 | 1]; }

    void update(int rt, int l, int r, int ql, int qr, int val) {
        if (ql <= l && qr >= r) {
            lazy[rt] += val;
            sumv[rt] += val * (r - l + 1);
            lazy[rt] %= mod;
            sumv[rt] %= mod;
        } else {
            int mid = (l + r) / 2;
            pushDown(rt, l, r);
            if (ql <= mid) update(lson, ql, qr, val);
            if (qr > mid) update(rson, ql, qr, val);
            pushUp(rt);
        }
    }

    int query(int rt, int l, int r, int pos) {
        if (l == r) return sumv[rt];
        int mid = (l + r) / 2;
        pushDown(rt, l, r);
        if (pos <= mid) return query(lson, pos);
        return query(rson, pos);
    }

   public:
    int uniqueLetterString(string S) {
        N = S.length();
        build();
        vector<int> pos[26];
        int ans = 0;
        for (int i = 0; i < N; i++) {
            int cur = S[i] - 'A';
            ans = (ans + (1 + i + 1) * (i + 1) / 2) % mod;
            if (pos[cur].size() == 1) {
                int ql = 1, qr = pos[cur][0] + 1;
                update(1, 1, N, ql, qr, 2);
            } else if (pos[cur].size() >= 2) {
                int psize = pos[cur].size();
                int ql = pos[cur][psize - 2] + 2, qr = pos[cur][psize - 1] + 1;
                update(1, 1, N, ql, qr, 2);
                ql = 1;
                qr = pos[cur][psize - 2] + 1;
                update(1, 1, N, ql, qr, 1);
            }
            pos[cur].push_back(i);
            ans -= sumv[1];
            while (ans < 0) ans += mod;
            ans %= mod;
        }
        return ans;
    }
};

/*
BBABABABABAACACBACBUISBCUSIC
581
*/