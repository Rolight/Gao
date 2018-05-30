#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

class Solution {
    vector<int> limits;
    vector<vector<int> > f;

    void get_limits(int num) {
        limits.clear();
        while (num > 0) {
            limits.push_back(num % 2);
            num /= 2;
        }
    }

    int dfs(int pos, int last, int bound) {
        if (pos == 0) return 1;
        if (!bound && f[pos][last] != -1) return f[pos][last];
        int m = bound ? limits[pos - 1] : 1;
        if (last == 1) m = 0;
        int ret = 0;
        for (int i = 0; i <= m; i++) {
            ret += dfs(pos - 1, i, bound && i == limits[pos - 1]);
        }
        if (!bound) f[pos][last] = ret;
        return ret;
    }

   public:
    int findIntegers(int num) {
        vector<int> tmp(2, -1);
        f = vector<vector<int> >(64, tmp);
        get_limits(num);
        return dfs(limits.size(), 0, true);
    }
};