/*
 * [354] Russian Doll Envelopes
 *
 * https://leetcode.com/problems/russian-doll-envelopes/description/
 *
 * algorithms
 * Hard (32.58%)
 * Total Accepted:    29.4K
 * Total Submissions: 90K
 * Testcase Example:  '[[5,4],[6,4],[6,7],[2,3]]'
 *
 * You have a number of envelopes with widths and heights given as a pair of
 * integers (w, h). One envelope can fit into another if and only if both the
 * width and height of one envelope is greater than the width and height of the
 * other envelope.
 *
 *
 * What is the maximum number of envelopes can you Russian doll? (put one
 * inside other)
 *
 *
 * Example:
 * Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes
 * you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 *
 */
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

class Solution {
    vector<int> maxv, values;
    void build(int size) { maxv = vector<int>(size * 4 + 10, 0); }
    void update(int rt, int l, int r, int pos, int v) {
        if (l == r) {
            maxv[rt] = max(maxv[rt], v);
        } else {
            int mid = (l + r) / 2;
            if (pos <= mid)
                update(lson, pos, v);
            else
                update(rson, pos, v);
            maxv[rt] = max(maxv[rt << 1], maxv[rt << 1 | 1]);
        }
    }
    int query(int rt, int l, int r, int ql, int qr) {
        if (ql <= l && qr >= r) return maxv[rt];
        int mid = (l + r) / 2;
        int ret = 0;
        if (ql <= mid) ret = max(ret, query(lson, ql, qr));
        if (qr > mid) ret = max(ret, query(rson, ql, qr));
        return ret;
    }

    void discretization(vector<pair<int, int> > &envelopes) {
        values.clear();
        values.push_back(0);
        for (int i = 0; i < envelopes.size(); i++) {
            values.push_back(envelopes[i].first);
            values.push_back(envelopes[i].second);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
    }

    inline int getID(int x) {
        return lower_bound(values.begin(), values.end(), x) - values.begin() +
               1;
    }

   public:
    int maxEnvelopes(vector<pair<int, int> > &envelopes) {
        discretization(envelopes);
        for (int i = 0; i < envelopes.size(); i++) {
            pair<int, int> env = envelopes[i];

            env.second = -env.second;
            envelopes[i] = env;
        }
        build(values.size());
        sort(envelopes.begin(), envelopes.end());

        int N = values.size();
        for (int i = 0; i < envelopes.size(); i++) {
            int cur_pos = getID(-envelopes[i].second);
            int cur_val = query(1, 1, N, 1, cur_pos - 1);
            // printf("curval is %d, maxv %d\n", cur_val, maxv[1]);
            update(1, 1, N, cur_pos, cur_val + 1);
        }
        return maxv[1];
    }
};
