#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long LL;

class RangeModule {
    class SegNode {
       public:
        SegNode *lc, *rc;
        bool val;
        SegNode() : lc(NULL), rc(NULL), val(false) {}
    };

    typedef SegNode *PSegNode;
    SegNode *root;
    int N;

    void pushUp(PSegNode now) {
        if (now->lc != NULL && now->rc != NULL) {
            now->val = now->lc->val && now->rc->val;
        } else {
            now->val = false;
        }
    }

    void pushDown(PSegNode now) {
        if (now == NULL || now->val == false) return;
        if (now->lc == NULL) {
            now->lc = new SegNode();
        }
        if (now->rc == NULL) {
            now->rc = new SegNode();
        }
        now->lc->val = true;
        now->rc->val = true;
    }

    void addRange(PSegNode now, int l, int r, int ql, int qr) {
        if (ql <= l && qr >= r) {
            now->val = true;
            // printf("%d %d val is %d\n", l, r, now->val);
        } else {
            if (now->val) return;
            pushDown(now);
            int mid = (l + r) / 2;
            if (ql <= mid) {
                if (now->lc == NULL) now->lc = new SegNode();
                addRange(now->lc, l, mid, ql, qr);
            }
            if (qr > mid) {
                if (now->rc == NULL) now->rc = new SegNode();
                addRange(now->rc, mid + 1, r, ql, qr);
            }
            pushUp(now);
            // printf("%d %d val is %d\n", l, r, now->val);
        }
    }

    PSegNode deleteRange(PSegNode now, int l, int r, int ql, int qr) {
        if (ql <= l && qr >= r) {
            // printf("remove %d %d\n", l, r);
            delete_tree(now);
            return NULL;
        } else {
            int mid = (l + r) / 2;
            pushDown(now);
            if (ql <= mid && now->lc != NULL) {
                now->lc = deleteRange(now->lc, l, mid, ql, qr);
            }
            if (qr > mid && now->rc != NULL) {
                now->rc = deleteRange(now->rc, mid + 1, r, ql, qr);
            }
            pushUp(now);
            // printf("%d %d update to %d\n", l, r, now->val);
            return now;
        }
    }

    bool queryRange(PSegNode now, int l, int r, int ql, int qr) {
        if (now == NULL) return false;
        if (ql <= l && r <= qr) {
            // printf("%d %d ret is %d\n", l, r, now->val);
            return now->val;
        } else {
            int mid = (l + r) / 2;
            bool ret = true;
            pushDown(now);
            if (ql <= mid) ret = ret && queryRange(now->lc, l, mid, ql, qr);
            if (qr > mid) ret = ret && queryRange(now->rc, mid + 1, r, ql, qr);
            // printf("%d %d ret is %d %d %d mid is %d\n", l, r, ret, ql, qr,
            // mid);
            return ret;
        }
    }

    void delete_tree(SegNode *cur) {
        if (cur->lc != NULL) delete_tree(cur->lc);
        if (cur->rc != NULL) delete_tree(cur->rc);
        delete cur;
    }

   public:
    RangeModule() {
        root = new SegNode();
        N = 1e9 + 10;
    }

    ~RangeModule() { delete_tree(root); }

    void addRange(int left, int right) {
        addRange(root, 1, N, left, right - 1);
    }

    bool queryRange(int left, int right) {
        return queryRange(root, 1, N, left, right - 1);
    }

    void removeRange(int left, int right) {
        deleteRange(root, 1, N, left, right - 1);
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule obj = new RangeModule();
 * obj.addRange(left,right);
 * bool param_2 = obj.queryRange(left,right);
 * obj.removeRange(left,right);
 */
