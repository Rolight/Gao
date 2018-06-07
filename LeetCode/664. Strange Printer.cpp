#include <string>
#include <vector>

using namespace std;

int f[128][128][128];
int g[128];

class Solution {
    string buf;

   public:
    int strangePrinter(string s) {
        if (s.length() == 0) return 0;
        int n = s.length();
        memset(f, 0, sizeof(f));
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= j; k++) {
                f[j][j][k] = 1;
                // printf("f[%d][%d][%d] = %d\n", j, j, k, f[j][j][k]);
                if (k < j && j - 1 >= 0) {
                    f[j - 1][j][k] = 1 + (int)(s[j - 1] != s[j]);
                    // printf("f[%d][%d][%d] = %d\n", j - 1, j, k, f[j -
                    // 1][j][k]);
                }
            }
            for (int i = j - 2; i >= 0; i--) {
                for (int k = 0; k <= i; k++) {
                    f[i][j][k] = f[i + 1][j][0] + 1;
                    for (int z = i + 1; z <= j; z++) {
                        if (s[z] != s[i]) continue;
                        if (z == i + 1) {
                            f[i][j][k] = min(f[i][j][k], f[z][j][k]);
                        }
                        f[i][j][k] = min(f[i][j][k],
                                         f[i + 1][z][0] + f[z + 1][j][k + 1]);
                    }
                    // printf("f[%d][%d][%d] = %d\n", i, j, k, f[i][j][k]);
                }
            }
        }

        int ans = f[0][n - 1][0];
        return ans;
    }
};