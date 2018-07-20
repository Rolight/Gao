#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

class Solution {
   public:
    LL f(LL x, LL v) {
        LL ret = 0;
        for (LL i = v; i <= x; i *= v) {
            LL cur_count = 0;
            ret += x / i;
        }
        return ret;
    }

    LL f(LL x) { return f(x, 5); }

    int preimageSizeFZF(int K) {
        LL lb = -1, ub = -1;
        LL l = 0, r = 1e18;

        // find lower bound
        while (l <= r) {
            LL mid = (l + r) / 2;
            if (f(mid) >= K) {
                lb = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        // find upper bound
        l = 0;
        r = 1e18;
        while (l <= r) {
            LL mid = (l + r) / 2;
            if (f(mid) > K) {
                ub = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ub - lb;
    }
};