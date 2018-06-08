#include <algorithm>
#include <map>
#include <vector>

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

using namespace std;

typedef long long LL;

class Solution {
    vector<int> values;
    vector<LL> maxv, lazy;
    int N;

    void discretization(vector<pair<int, int> > &posisitons) {
        values.clear();
        for (int i = 0; i < posisitons.size(); i++) {
            values.push_back(posisitons[i].first);
            values.push_back(posisitons[i].first + posisitons[i].second - 1);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        N = values.size() + 1;
    }

    void build() {
        maxv = vector<LL>(N * 4 + 10, 0);
        lazy = maxv;
    }

    inline int get_id(int x) {
        return lower_bound(values.begin(), values.end(), x) - values.begin() +
               1;
    }

    inline void pushUp(int rt) {
        maxv[rt] = max(maxv[rt << 1], maxv[rt << 1 | 1]);
    }

    inline void pushDown(int rt) {
        if (lazy[rt] == 0) return;
        int lc = rt << 1, rc = rt << 1 | 1;
        maxv[lc] = maxv[rc] = lazy[rt];
        lazy[lc] = lazy[rc] = lazy[rt];
        lazy[rt] = 0;
    }

    void update(int rt, int l, int r, int ql, int qr, LL val) {
        if (ql <= l && qr >= r) {
            lazy[rt] = maxv[rt] = val;
        } else {
            int mid = (l + r) / 2;
            pushDown(rt);
            if (ql <= mid) update(lson, ql, qr, val);
            if (qr > mid) update(rson, ql, qr, val);
            pushUp(rt);
        }
    }

    LL query(int rt, int l, int r, int ql, int qr) {
        if (ql <= l && qr >= r) return maxv[rt];
        LL ret = 0;
        pushDown(rt);
        int mid = (l + r) / 2;
        if (ql <= mid) ret = max(ret, query(lson, ql, qr));
        if (qr > mid) ret = max(ret, query(rson, ql, qr));
        return ret;
    }

   public:
    vector<int> fallingSquares(vector<pair<int, int> > &positions) {
        discretization(positions);
        build();
        vector<int> ans;
        for (int i = 0; i < positions.size(); i++) {
            int ql = get_id(positions[i].first),
                qr = get_id(positions[i].first + positions[i].second - 1);
            int height = positions[i].second;
            int cur_height = query(1, 1, N, ql, qr);
            height += cur_height;
            update(1, 1, N, ql, qr, height);
            ans.push_back(maxv[1]);
        }
        return ans;
    }
};