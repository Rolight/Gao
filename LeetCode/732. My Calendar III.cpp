#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

class SegNode {
   public:
    SegNode *lc, *rc;
    int val;
    int lazy;

    SegNode() : lc(NULL), rc(NULL), val(0), lazy(0) {}
};

class MyCalendarThree {
    void delete_tree(SegNode *root) {
        if (root == NULL) return;
        delete_tree(root->lc);
        delete_tree(root->rc);
        delete root;
    }

    void push_up(SegNode *rt) {
        if (rt->lc != NULL) rt->val = max(rt->lc->val, rt->val);
        if (rt->rc != NULL) rt->val = max(rt->rc->val, rt->val);
    }

    void push_down(SegNode *rt) {
        if (rt->lazy == 0) return;
        if (rt->lc == NULL) {
            rt->lc = new SegNode();
        }
        if (rt->rc == NULL) {
            rt->rc = new SegNode();
        }
        rt->lc->lazy += rt->lazy;
        rt->rc->lazy += rt->lazy;
        rt->lc->val += rt->lazy;
        rt->rc->val += rt->lazy;
        rt->lazy = 0;
    }

    void update(SegNode *rt, int l, int r, int ql, int qr) {
        if (ql <= l && qr >= r) {
            rt->lazy += 1;
            rt->val += 1;
        } else {
            int mid = (l + r) / 2;
            push_down(rt);
            if (ql <= mid) {
                if (rt->lc == NULL) rt->lc = new SegNode();
                update(rt->lc, l, mid, ql, qr);
            }
            if (qr > mid) {
                if (rt->rc == NULL) rt->rc = new SegNode();
                update(rt->rc, mid + 1, r, ql, qr);
            }
            push_up(rt);
        }
    }

    SegNode *root;
    int N;

   public:
    MyCalendarThree() {
        root = new SegNode();
        N = 1e9;
    }

    ~MyCalendarThree() { delete_tree(root); }

    int book(int start, int end) {
        update(root, 0, N, start, end - 1);
        return root->val;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree obj = new MyCalendarThree();
 * int param_1 = obj.book(start,end);
 */

int main() {
    MyCalendarThree *c = new MyCalendarThree();
    int l, r;
    while (cin >> l >> r) {
        cout << c->book(l, r) << endl;
    }
    return 0;
}