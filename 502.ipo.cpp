/*
 * [502] IPO
 *
 * https://leetcode.com/problems/ipo/description/
 *
 * algorithms
 * Hard (36.25%)
 * Total Accepted:    7.4K
 * Total Submissions: 20.3K
 * Testcase Example:  '2\n0\n[1,2,3]\n[0,1,1]'
 *
 *
 * Suppose LeetCode will start its IPO soon. In order to sell a good price of
 * its shares to Venture Capital, LeetCode would like to work on some projects
 * to increase its capital before the IPO. Since it has limited resources, it
 * can only finish at most k distinct projects before the IPO. Help LeetCode
 * design the best way to maximize its total capital after finishing at most k
 * distinct projects.
 *
 *
 *
 * You are given several projects. For each project i, it has a pure profit Pi
 * and a minimum capital of Ci is needed to start the corresponding project.
 * Initially, you have W capital. When you finish a project, you will obtain
 * its pure profit and the profit will be added to your total capital.
 *
 *
 *
 * To sum up, pick a list of at most k distinct projects from given projects to
 * maximize your final capital, and output your final maximized capital.
 *
 *
 * Example 1:
 *
 * Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].
 *
 * Output: 4
 *
 * Explanation: Since your initial capital is 0, you can only start the project
 * indexed 0.
 * ⁠            After finishing it you will obtain profit 1 and your capital
 * becomes 1.
 * ⁠            With capital 1, you can either start the project indexed 1 or
 * the project indexed 2.
 * ⁠            Since you can choose at most 2 projects, you need to finish
 * the project indexed 2 to get the maximum capital. ⁠            Therefore,
 * output the final maximized capital, which is 0 + 1 + 3 = 4.
 *
 *
 *
 * Note:
 *
 * You may assume all numbers in the input are non-negative integers.
 * The length of Profits array and Capital array will not exceed 50,000.
 * The answer is guaranteed to fit in a 32-bit signed integer.
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

class Solution {
    struct Node {
        int id_in_capital, captial;
        Node(int id_in_capital, int captial)
            : id_in_capital(id_in_capital), captial(captial) {}
        bool operator<(const Node &x) const { return captial < x.captial; }
    };
    vector<int> cap2id;
    vector<Node> nodes;
    vector<pair<int, int> > maxv;
    int N;

    void init(vector<int> &Captial) {
        nodes.clear();
        for (int i = 0; i < Captial.size(); i++) {
            nodes.push_back(Node(i, Captial[i]));
        }
        sort(nodes.begin(), nodes.end());
        cap2id = vector<int>(Captial.size(), 0);
        for (int i = 0; i < nodes.size(); i++) {
            cap2id[nodes[i].id_in_capital] = i + 1;
        }
        N = cap2id.size();
        maxv = vector<pair<int, int> >(N * 4 + 100, make_pair(0, 0));
    }

    inline void pushup(int rt) {
        maxv[rt] = max(maxv[rt << 1], maxv[rt << 1 | 1]);
    }

    void build(int rt, int l, int r, vector<int> &values) {
        if (l == r) {
            maxv[rt] = make_pair(values[nodes[l - 1].id_in_capital], l);
        } else {
            int mid = (l + r) / 2;
            build(lson, values);
            build(rson, values);
            pushup(rt);
        }
    }

    void update(int rt, int l, int r, int pos, int val) {
        if (l == r) {
            maxv[rt] = make_pair(val, l);
        } else {
            int mid = (l + r) / 2;
            if (pos <= mid)
                update(lson, pos, val);
            else
                update(rson, pos, val);
            pushup(rt);
        }
    }

    pair<int, int> query(int rt, int l, int r, int ql, int qr) {
        if (ql <= l && qr >= r) return maxv[rt];
        int mid = (l + r) / 2;
        pair<int, int> ret = make_pair((int)-1e8, 0);
        if (ql <= mid) ret = max(ret, query(lson, ql, qr));
        if (qr > mid) ret = max(ret, query(rson, ql, qr));
        return ret;
    }

   public:
    int findMaximizedCapital(int k, int W, vector<int> &Profits,
                             vector<int> &Capital) {
        Capital.push_back(W);
        Profits.push_back(0);
        init(Capital);
        build(1, 1, N, Profits);
        int curW = W;
        for (int i = 0; i < k; i++) {
            Node cur_node = Node(-1, curW);
            vector<Node>::iterator iter =
                upper_bound(nodes.begin(), nodes.end(), cur_node);
            int query_pos;
            if (iter == nodes.end()) {
                query_pos = N;
            } else {
                query_pos = iter - nodes.begin();
            }

            pair<int, int> ret = query(1, 1, N, 1, query_pos);
            curW += ret.first;
            update(1, 1, N, ret.second, 0);
        }
        return curW;
    }
};