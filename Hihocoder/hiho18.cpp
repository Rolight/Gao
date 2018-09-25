#include <cstdio>
#include <cstring>
#include <list>
#include <vector>

using namespace std;

struct Block {
    int lpos, rpos;
    int minv;
    vector<int> data;

    Block(int lpos, int init_val): lpos(lpos), rpos(lpos), minv(init_val) {
        data.push_back(init_val);
    }
};

const int maxn = 10000 + 10;
const int maxb = 100;

typedef list<Block> BL;

void push_back(BL &bl, int val) {
    if(bl.size() == 0) {
        bl.push_back(Block(1, val));
        return;
    }
    int back_size = bl.back().data.size();
    if(back_size >= maxb) {
        bl.push_back(Block(bl.back().rpos + 1, val));
    } else {
        bl.back().data.push_back(val);
        bl.back().rpos++;
        bl.back().minv = min(bl.back().minv, val);
    }
}

int query(BL &bl, int ql, int qr) {
    int ret = 1e9;
    for(BL::iterator iter = bl.begin(); iter !=  bl.end(); ++iter) {
        if(iter->rpos < ql) continue;
        if(iter->lpos > qr) break;
        if(ql <= iter->lpos && qr >= iter->rpos) ret = min(ret, iter->minv);
        else if(iter->lpos <= ql && iter->rpos >= qr) {
            for(int i = ql - iter->lpos; i <= qr - iter->lpos; i++) {
                ret = min(ret, iter->data[i]);
            }
        }
        else if(ql <= iter->rpos && qr > iter->rpos) {
            for(int i = ql - iter->lpos; i < iter->data.size() && i <= qr - iter->lpos; i++) {
                ret = min(ret, iter->data[i]);
            }
        } else if(ql < iter->lpos && qr >= iter->lpos) {
            for(int i = 0; i <= qr - iter->lpos; i++) {
                ret = min(ret, iter->data[i]);
            }
        }
    }
    return ret;
}

void update(BL &bl, int pos, int val) {
    for(BL::iterator iter = bl.begin(); iter !=  bl.end(); ++iter) {
        if(iter->lpos <= pos && iter->rpos >= pos) {
            iter->data[pos - iter->lpos] = val;
            iter->minv = val;
            for(int i = 0; i < iter->data.size(); i++) {
                iter->minv = min(iter->minv, iter->data[i]);
            }
        }
    }
}

int main() {
    int n, buf;
    BL bl;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &buf);
        push_back(bl, buf);
    }
    int q; 
    scanf("%d", &q);
    int cmd, a, b;
    for(int i = 0; i < q; i++) {
        scanf("%d%d%d", &cmd, &a, &b);
        if(cmd == 1) update(bl, a, b);
        else printf("%d\n", query(bl, a, b));
    }
    return 0;
}