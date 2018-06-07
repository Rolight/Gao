#include <cstring>
#include <vector>

using namespace std;
class Solution {
    int calc(int n, int m, int val) {
        // find how many number smaller than val
        int ret = 0;
        for (int i = 1; i <= n; i++) {
            int t = val / i;
            if (val % i == 0) {
                t -= 1;
            }
            if (t > m) {
                t = m;
            }
            ret += t;
        }
        return ret;
    }

   public:
    int findKthNumber(int m, int n, int k) {
        int l = 1, r = n * m;
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (calc(mid) >= k - 1) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};