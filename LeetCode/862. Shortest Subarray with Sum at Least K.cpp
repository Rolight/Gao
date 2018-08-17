#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 5e4 + 10;

typedef long long LL;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

class Solution {
    vector<LL> ssum;
    vector<LL> maxv;
    int N;

    void pushUp(int rt) { maxv[rt] = max(maxv[rt << 1], maxv[rt << 1 | 1]); }

    void build(int rt, int l, int r) {
        if (l == r)
            maxv[rt] = ssum[l - 1];
        else {
            int mid = (l + r) / 2;
            build(lson);
            build(rson);
            pushUp(rt);
        }
    }

    LL query(int rt, int l, int r, int ql, int qr) {
        // cout << rt << " " << l << " " << r << " " << ql << " " << qr << endl;
        if (ql <= l && r <= qr) return maxv[rt];
        int mid = (l + r) / 2;
        LL ret = -1e17;
        if (ql <= mid) ret = max(ret, query(lson, ql, qr));
        if (qr > mid) ret = max(ret, query(rson, ql, qr));
        return ret;
    }

   public:
    int shortestSubarray(vector<int> &A, int K) {
        ssum.clear();
        ssum.push_back(A[0]);
        for (int i = 1; i < A.size(); i++) ssum.push_back(ssum.back() + A[i]);
        N = A.size();
        maxv = vector<LL>((N + 2) * 4);
        build(1, 1, N);
        int ans = -1;
        LL cur_sum = 0;
        for (int i = 0; i < N; i++) {
            int min_len = 1, max_len = N - i;
            while (min_len <= max_len) {
                int mid_len = (min_len + max_len) / 2;
                LL cur_ret = query(1, 1, N, i + 1, i - 1 + mid_len + 1);
                cur_ret -= cur_sum;
                if (cur_ret >= K) {
                    if (ans == -1 || ans > mid_len) {
                        ans = mid_len;
                    }
                    max_len = mid_len - 1;
                } else {
                    min_len = mid_len + 1;
                }
            }
            cur_sum += A[i];
        }
        return ans;
    }
};
