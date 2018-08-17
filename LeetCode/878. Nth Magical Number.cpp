#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;

const LL mod = 1e9 + 7;

class Solution {
    LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }

    LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }

   public:
    int nthMagicalNumber(int N, int A, int B) {
        vector<LL> nums;
        LL lc = lcm(A, B);
        LL P = lc / A + lc / B - 1, S = N / P, R = N % P;
        for (int i = 1; i < lc / A; i++) nums.push_back(A * i);
        for (int i = 1; i < lc / B; i++) nums.push_back(B * i);
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        LL ans = S * lc % mod;
        if (R != 0) ans = (ans + nums[R - 1]) % mod;
        return ans;
    }
};