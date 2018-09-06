#include <set>
#include <unordered_map>
#include <map>

using namespace std;


class StackNode {
public:
    int num, freq, pos;
    StackNode(int num, int freq, int pos): num(num), freq(freq), pos(pos) {}
    bool operator < (const StackNode &s) const {
        return make_pair(freq, pos) > make_pair(s.freq, s.pos);
    }
};

class FreqStack {
    unordered_map<int, int> freq;
    unordered_map<int, set<int> > pos;
    set<StackNode> stk;
    int cur;

    int get_pos(int num) {
        set<int> &s_pos = pos[num];
        if(s_pos.size()  == 0) return -1;
        return -(*s_pos.begin());
    }

public:
    FreqStack() {
        freq.clear();
        pos.clear();
        stk.clear();
        cur = 0;
    }
    
    void print_statistic() {
        for(auto g : freq) {
            cout << g.first << ": " << g.second << ", " << get_pos(g.first) << endl;
        }
        cout << " ----- ---- --- " << endl;
    }

    void push(int x) {
        int x_pos = get_pos(x), x_freq = freq[x];
        if(x_pos != -1) {
            StackNode cur(x, x_freq, x_pos);
            stk.erase(cur);
        }
        stk.insert(StackNode(x, x_freq + 1, cur));
        pos[x].insert(-cur);
        freq[x] = x_freq + 1;
        cur++;
        //print_statistic();
    }

    int pop() {
        StackNode res = *stk.begin();
        pos[res.num].erase(-res.pos);
        stk.erase(stk.begin());
        freq[res.num] = res.freq - 1;
        int res_pos = get_pos(res.num);
        if(res_pos != -1) {
            stk.insert(StackNode(res.num, res.freq - 1, res_pos));
        }
        //print_statistic();
        return res.num;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack obj = new FreqStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 */

