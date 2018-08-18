#include <algorithm>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;

class Solution {
   public:
    int profitableSchemes(int G, int P, vector<int> &group,
                          vector<int> &profit) {
        vector<int> pcnt(P + 1, 0);
        vector<vector<int> > f(G + 1, pcnt);

        int N = group.size();

        f[0][0] = 1;

        for (int cur = 0; cur < N; cur++) {
            int curg = group[cur], curp = profit[cur];
            for (int g = G - curg; g >= 0; g--) {
                for (int p = P; p >= 0; p--) {
                    f[g + curg][min(p + curp, P)] += f[g][p];
                    f[g + curg][min(p + curp, P)] %= mod;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i <= G; i++) ans = (ans + f[i][P]) % mod;
        return ans;
    }
};