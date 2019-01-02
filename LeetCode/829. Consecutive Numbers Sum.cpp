typedef long long LL;

class Solution {
  public:
    int consecutiveNumbersSum(int N) {
        int ans = 0;
        for (LL i = 1; i * i <= N; i++) {
            if (N % i == 0 && (N / i) % 2 == 1) {
                if (i + N / i / 2 <= N) {
                    ans++;
                }
            }
            if (N % i == 0 && i != N / i && i % 2 == 1) {
                if (N / i + i / 2 <= N) {
                    ans++;
                }
            }
        }
        N *= 2;
        for (LL i = 1; i * i <= N; i++) {
            if (N % i == 0 && (N / i) % 2 == 1 && i % 2 == 1) {
                if (i + N / i / 2 <= N) {
                    ans++;
                }
            }
            if (N % i == 0 && i != N / i && i % 2 == 1 && (N / i) % 2 == 1) {
                if (N / i + i / 2 <= N) {
                    ans++;
                }
            }
        }
        return ans;
    }
};