#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
const LL mod = 1e9 + 7;

class Solution {
   public:
    int kInversePairs(int n, int k) {
        vector<LL> tmp(k + 1, 0);
        vector<vector<LL> > f(n + 1, tmp);
        vector<LL> ssum(k + 1, 1);
        f[1][0] = 1;
        for (int i = 2; i <= n; i++) {
            int cur_m = min(k, (i - 1) * i / 2);
            f[i][0] = 1;
            for (int j = 1; j <= cur_m; j++) {
                f[i][j] = ssum[j];
                int t = j - min(i - 1, j);
                if (t > 0) {
                    f[i][j] -= ssum[t - 1];
                    while (f[i][j] < 0) f[i][j] += mod;
                }
            }
            ssum[0] = f[i][0];
            for (int j = 1; j <= k; j++) {
                ssum[j] = (f[i][j] + ssum[j - 1]) % mod;
            }
        }
        return f[n][k];
    }
};