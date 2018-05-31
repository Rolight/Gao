#include <string>
#include <vector>

using namespace std;

typedef long long LL;
const LL mod = 1e9 + 7;

class Solution {
   public:
    int numDecodings(string s) {
        int len = s.length();
        vector<LL> f(len + 1, 0);
        f[0] = 1;
        for (int i = 1; i <= len; i++) {
            int spos = i - 1;
            if (s[spos] >= '7' && s[spos] <= '9') {
                if (spos == 0) {
                    f[i] = f[i - 1];
                } else if (s[spos - 1] == '1') {
                    f[i] = f[i - 2] + f[i - 1];
                } else if (s[spos - 1] == '*') {
                    f[i] = f[i - 2] + f[i - 1];
                } else {
                    f[i] = f[i - 1];
                }
            } else if (s[spos] == '0') {
                if (spos == 0)
                    f[i] = 0;
                else if (s[spos - 1] == '1' || s[spos - 1] == '2') {
                    f[i] = f[i - 2];
                } else if (s[spos - 1] == '*') {
                    f[i] = f[i - 2] * 2;
                }
            } else if (s[spos] >= '1' && s[spos] <= '6') {
                if (spos == 0 || s[spos - 1] == '0' ||
                    (s[spos - 1] >= '3' && s[spos - 1] <= '9'))
                    f[i] = f[i - 1];
                else if (s[spos - 1] >= '1' && s[spos - 1] <= '2') {
                    f[i] = f[i - 1] + f[i - 2];
                } else if (s[spos - 1] == '*') {
                    f[i] = f[i - 1] + 2 * f[i - 2];
                }
            } else if (s[spos] == '*') {
                if (spos == 0 || s[spos - 1] == '0')
                    f[i] = 9 * f[i - 1];
                else if (s[spos - 1] == '1') {
                    f[i] = f[i - 1] * 9 + f[i - 2] * 9;
                } else if (s[spos - 1] == '2') {
                    f[i] = f[i - 1] * 9 + f[i - 2] * 6;
                } else if (s[spos - 1] >= '3' && s[spos - 1] <= '9') {
                    f[i] = f[i - 1] * 9;
                } else if (s[spos - 1] == '*') {
                    f[i] = f[i - 1] * 9 + f[i - 2] * (9 + 6);
                }
            }
            // cout << f[i] << " ";
            f[i] %= mod;
        }
        return f[len];
    }
};