#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

char buf[32];

class Solution {
    LL l, r;

    bool check(string cur) {
        LL cur_num = 0;
        for(int j = 0; j < cur.size(); j++) cur_num = cur_num * 10 + cur[j] - '0';
        cur_num *= cur_num;
        if(cur_num < l || cur_num > r) return false;
        sprintf(buf, "%lld", cur_num);
        cur = buf;
        for(int i = 0, j = cur.size() - 1; i < j; ++i, --j) {
            if(cur[i] != cur[j]) return false;
        }
        return true;
    }
public:
    int superpalindromesInRange(string L, string R) {
        l = r = 0;
        for(int i = 0; i < L.size(); i++) l = l * 10 + L[i] - '0';
        for(int i = 0; i < R.size(); i++) r = r * 10 + R[i] - '0';

        int ans = 0;
        for(int i = 1; i < 100000; i++) {
            sprintf(buf, "%d", i);
            string cur = buf, cur_1 = buf;
            reverse(cur_1.begin(), cur_1.end());
            ans += check(cur + cur_1);
            cur.pop_back();
            ans += check(cur + cur_1);
        }
        return ans;
    }
};