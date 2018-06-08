#include <map>
#include <vector>

using namespace std;

typedef long long LL;

class Solution {
    struct tuple {
        LL a, b, c, val;
        tuple() : a(0), b(0), c(0), val(0) {}
        tuple(LL a, LL b, LL c, LL val) : a(a), b(b), c(c), val(val) {}
        bool operator<(const tuple &x) {
            return make_pair(make_pair(val, -a), make_pair(-b, -c)) <
                   make_pair(make_pair(x.val, -x.a), make_pair(-x.b, -x.c));
        }
    };
    vector<LL> ssum;

    LL subsum(int l, int r) {
        LL ret = ssum[r];
        if (l > 0) ret -= ssum[l - 1];
        return ret;
    }

   public:
    vector<int> maxSumOfThreeSubarrays(vector<int> &nums, int k) {
        ssum.clear();
        ssum.push_back(nums[0]);
        vector<tuple> ff(4);
        vector<vector<tuple> > f(nums.size(), ff);
        for (int i = 1; i < nums.size(); i++) {
            ssum.push_back(ssum.back() + nums[i]);
        }
        tuple ans;

        f[0][1] = tuple(0, 0, 0, subsum(0, k - 1));
        for (int i = 1; i + k <= nums.size(); i++) {
            for (int j = 1; j <= 3; j++) {
                // printf("%d %d\n", i, j);
                if (i < (j - 1) * k) break;
                if (i >= k && j > 1) {
                    tuple cur = f[i - k][j - 1];
                    cur.val += subsum(i, i + k - 1);
                    if (j == 2) cur.b = i;
                    if (j == 3) cur.c = i;
                    f[i][j] = cur;
                } else if (j == 1) {
                    tuple cur(i, 0, 0, subsum(i, i + k - 1));
                    f[i][j] = cur;
                }
                if (f[i][j] < f[i - 1][j]) {
                    f[i][j] = f[i - 1][j];
                }
                if (j == 3 && ans < f[i][j]) {
                    ans = f[i][j];
                }
                // printf("f[%d][%d] = (%lld, %lld, %lld) = %lld\n", i, j,
                //        f[i][j].a, f[i][j].b, f[i][j].c, f[i][j].val);
            }
        }
        vector<int> aa;
        aa.push_back(ans.a);
        aa.push_back(ans.b);
        aa.push_back(ans.c);
        return aa;
    }
};