#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

const LL mod = 1e9 + 7;
const int maxn = 205;
LL f[maxn][maxn];
class Solution {
public:
    int numPermsDISequence(string S) {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for(int i = 1; i <= S.size(); i++) {
            char curS = S[i - 1];
            if(curS == 'D') {
                for(int j = 0; j <= i; j++) {
                    for(int k = j; k <= i; k++) {
                        f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
                    }
                }
            } else {
                for(int j = 0; j <= i; j++) {
                    for(int k = 0; k < j; k++) {
                        f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
                    }
                }
            }
        }
        LL ans = 0;
        for(int i = 0; i <= S.size(); i++) {
            ans = (ans + f[S.size()][i]) % mod;
        }
        return ans;
    }
};