/*
 * [391] Perfect Rectangle
 *
 * https://leetcode.com/problems/perfect-rectangle/description/
 *
 * algorithms
 * Hard (27.45%)
 * Total Accepted:    14.2K
 * Total Submissions: 51.8K
 * Testcase Example:  '[[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]'
 *
 *
 * Given N axis-aligned rectangles where N > 0, determine if they all together
 * form an exact cover of a rectangular region.
 *
 *
 *
 * Each rectangle is represented as a bottom-left point and a top-right point.
 * For example, a unit square is represented as [1,1,2,2]. (coordinate of
 * bottom-left point is (1, 1) and top-right point is (2, 2)).
 *
 *
 *
 * Example 1:
 *
 * rectangles = [
 * ⁠ [1,1,3,3],
 * ⁠ [3,1,4,2],
 * ⁠ [3,2,4,4],
 * ⁠ [1,3,2,4],
 * ⁠ [2,3,3,4]
 * ]
 *
 * Return true. All 5 rectangles together form an exact cover of a rectangular
 * region.
 *
 *
 *
 *
 *
 *
 * Example 2:
 *
 * rectangles = [
 * ⁠ [1,1,2,3],
 * ⁠ [1,3,2,4],
 * ⁠ [3,1,4,2],
 * ⁠ [3,2,4,4]
 * ]
 *
 * Return false. Because there is a gap between the two rectangular
 * regions.
 *
 *
 *
 *
 *
 *
 * Example 3:
 *
 * rectangles = [
 * ⁠ [1,1,3,3],
 * ⁠ [3,1,4,2],
 * ⁠ [1,3,2,4],
 * ⁠ [3,2,4,4]
 * ]
 *
 * Return false. Because there is a gap in the top center.
 *
 *
 *
 *
 *
 *
 * Example 4:
 *
 * rectangles = [
 * ⁠ [1,1,3,3],
 * ⁠ [3,1,4,2],
 * ⁠ [1,3,2,4],
 * ⁠ [2,2,4,4]
 * ]
 *
 * Return false. Because two of the rectangles overlap with each other.
 *
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct Seg {
    int x, up, down, val;
    Seg(int x, int up, int down, int val)
        : x(x), up(up), down(down), val(val) {}
    bool operator<(const Seg &seg) const { return x < seg.x; }
};

struct SegTreeNode {
    int l, r;
    int cnt, cover_len;
};

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

class Solution {
    vector<Seg> segs;
    vector<int> values;
    vector<SegTreeNode> seg_node;
    int N;

    inline int getID(int x) {
        return lower_bound(values.begin(), values.end(), x) - values.begin() +
               1;
    }

    inline void _build(int rt, int l, int r) {
        if (l == r) {
            seg_node[rt].l = values[l - 1];
            seg_node[rt].r = values[l];
        } else {
            int mid = (l + r) / 2;
            _build(lson);
            _build(rson);
            seg_node[rt].l = seg_node[rt << 1].l;
            seg_node[rt].r = seg_node[rt << 1 | 1].r;
            push_up(rt, l, r);
        }
    }

    inline void build() {
        N = values.size() - 1;
        seg_node = vector<SegTreeNode>(values.size() * 4 + 10);
        _build(1, 1, N);
    }

    inline void push_up(int rt, int l, int r) {
        if (seg_node[rt].cnt > 0) {
            seg_node[rt].cover_len = seg_node[rt].r - seg_node[rt].l;
        } else if (l != r) {
            seg_node[rt].cover_len =
                seg_node[rt << 1].cover_len + seg_node[rt << 1 | 1].cover_len;
        } else {
            seg_node[rt].cover_len = 0;
        }
        // cout << "seg_node(" << seg_node[rt].l << ", " << seg_node[rt].r <<
        // ")" << endl; cout << "seg_node[" << rt << "].cover_len = " <<
        // seg_node[rt].cover_len << endl;
    }

    inline void update(int rt, int l, int r, int ql, int qr, int val) {
        if (ql <= l && qr >= r) {
            seg_node[rt].cnt += val;
            push_up(rt, l, r);
        } else {
            int mid = (l + r) / 2;
            if (ql <= mid) update(lson, ql, qr, val);
            if (qr > mid) update(rson, ql, qr, val);
            push_up(rt, l, r);
        }
    }

   public:
    bool isRectangleCover(vector<vector<int> > &rectangles) {
        segs.clear();
        values.clear();
        long long min_x = 1e16, min_y = 1e16, max_x = -1e16, max_y = -1e16;
        long long input_total_area = 0;
        for (int i = 0; i < rectangles.size(); i++) {
            long long dx = rectangles[i][0], dy = rectangles[i][1],
                      ux = rectangles[i][2], uy = rectangles[i][3];
            segs.push_back(Seg(dx, uy, dy, 1));
            segs.push_back(Seg(ux, uy, dy, -1));
            values.push_back(dx);
            values.push_back(dy);
            values.push_back(uy);
            values.push_back(ux);

            min_x = min(min(dx, ux), min_x);
            max_x = max(max(dx, ux), max_x);
            min_y = min(min(dy, uy), min_y);
            max_y = max(max(dy, uy), max_y);
            input_total_area += (ux - dx) * (uy - dy);
        }
        // discretization
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());

        sort(segs.begin(), segs.end());
        build();
        // cout << "build finished" << endl;
        long long total_area = 0;
        for (int i = 0; i < segs.size(); i++) {
            // cout << "cur_x is " << segs[i].x << endl;
            if (i > 0) {
                long long delta_x = segs[i].x - segs[i - 1].x;
                int delta_y = seg_node[1].cover_len;
                // cout << "delta_x: " << delta_x << ", delta_y: " << delta_y <<
                // endl;
                total_area += delta_x * delta_y;
            }
            // cout << "update: " << segs[i].down << ", " << segs[i].up << " "
            // << segs[i].val << endl;
            update(1, 1, N, getID(segs[i].down), getID(segs[i].up) - 1,
                   segs[i].val);
        }

        long long expect_area = (max_x - min_x) * (max_y - min_y);
        // cout << total_area << " " << expect_area << input_total_area << endl;
        return expect_area == total_area && total_area == input_total_area;
    }
};
