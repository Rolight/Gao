#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

const LL mod = 1e9 + 7;

class Solution {
    LL fast_pow(LL x) {
        LL ret = 1, n = 2;
        while (x) {
            if (x & 1) {
                ret = (ret * n) % mod;
            }
            x /= 2;
            n = (n * n) % mod;
        }
        return ret;
    }

   public:
    int sumSubseqWidths(vector<int> &A) {
        int N = A.size();
        LL inv = fast_pow(mod - 2);
        if (N == 1) return 0;
        LL ans = 0, cur_sum = 0;
        sort(A.begin(), A.end());
        for (int i = N - 2; i >= 0; i--) {
            cur_sum =
                (cur_sum + (A[N - 1] - A[i]) * fast_pow(N - 1 - i - 1)) % mod;
        }
        // cout << cur_sum << endl;
        ans += cur_sum;
        for (int i = N - 2; i >= 1; i--) {
            // cout << "-" << A[i + 1] - A[i] << " * " << sum[i] << endl;
            cur_sum -=
                (A[i + 1] - A[i]) * ((fast_pow(i + 1) - 1 + mod) % mod) % mod;
            while (cur_sum < 0) cur_sum += mod;
            cur_sum %= mod;
            cur_sum = (cur_sum * inv) % mod;
            // cout << cur_sum << endl;
            ans = (ans + cur_sum) % mod;
        }
        return ans;
    }
};