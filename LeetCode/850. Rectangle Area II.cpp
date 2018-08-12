#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef long long LL;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

class Seg {
   public:
    int x, l, r, t;
    Seg(int x, int l, int r, int t) : x(x), l(l), r(r), t(t) {}
    bool operator<(const Seg &s) const { return x < s.x; }
};

class SegNode {
   public:
    int l, r;
    int covered;
    LL cover_len;

    SegNode() : cover_len(0), covered(0) {}
};

const LL mod = 1e9 + 7;

class Solution {
    vector<int> values;
    vector<SegNode> nodes;
    vector<Seg> segs;
    int N;

    void pushUp(int rt) {
        if (nodes[rt].covered > 0) {
            nodes[rt].cover_len = values[nodes[rt].r + 1] - values[nodes[rt].l];
        } else if (nodes[rt].r == nodes[rt].l)
            nodes[rt].cover_len = 0;
        else
            nodes[rt].cover_len =
                nodes[rt << 1].cover_len + nodes[rt << 1 | 1].cover_len;
    }

    void preprocess(vector<vector<int> > &rect) {
        segs.clear();
        values.clear();
        for (int i = 0; i < rect.size(); i++) {
            int x1 = rect[i][0], y1 = rect[i][1], x2 = rect[i][2],
                y2 = rect[i][3];
            segs.push_back(Seg(x1, y1, y2, 1));
            segs.push_back(Seg(x2, y1, y2, -1));
            values.push_back(y1);
            values.push_back(y2);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        sort(segs.begin(), segs.end());
        N = values.size();
        nodes = vector<SegNode>((N + 10) * 4);
    }

    void build(int rt, int l, int r) {
        nodes[rt].l = l;
        nodes[rt].r = r;
        if (l == r) {
            nodes[rt].cover_len = 0;
            nodes[rt].covered = 0;
        } else {
            int mid = (l + r) / 2;
            build(lson);
            build(rson);
            pushUp(rt);
        }
    }

    void update(int rt, int l, int r, int ql, int qr, int val) {
        if (ql <= l && qr >= r) {
            nodes[rt].covered += val;
            pushUp(rt);
            // printf("update %d, %d to %d\n", l, r, now.cover_len);
        } else {
            int mid = (l + r) / 2;
            if (ql <= mid) update(lson, ql, qr, val);
            if (qr > mid) update(rson, ql, qr, val);
            pushUp(rt);
        }
    }

    inline int get_id(int x) {
        return lower_bound(values.begin(), values.end(), x) - values.begin();
    }

   public:
    int rectangleArea(vector<vector<int> > &rectangles) {
        preprocess(rectangles);
        build(1, 0, N - 1);
        LL ans = 0;
        for (int i = 0; i < segs.size() - 1; i++) {
            int ql = get_id(segs[i].l), qr = get_id(segs[i].r);
            update(1, 0, N - 1, ql, qr - 1, segs[i].t);
            printf("cur x = %d, cover_len = %d\n", segs[i].x,
                   nodes[1].cover_len);
            ans += (segs[i + 1].x - segs[i].x) * nodes[1].cover_len;
            ans %= mod;
        }
        return ans;
    }
};