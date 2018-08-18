#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 10000 + 1;
const int maxk = 100 + 1;

int f[maxn][maxk];

int calc(int n, int k, int pivot) {
    return max(f[pivot - 1][k - 1], f[n - pivot][k]) + 1;
}

void init() {
    if (f[2][1] != 0) return;
    int N = 10000;
    int K = 100;
    for (int i = 1; i <= K; i++) {
        f[2][i] = 2;
        f[1][i] = 1;
    }
    for (int i = 3; i <= N; i++) {
        f[i][1] = i;
        for (int j = 2; j <= K; j++) {
            int pivot = i;
            int l = 1, r = i;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (f[mid - 1][j - 1] <= f[i - mid][j]) {
                    pivot = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            f[i][j] = min(calc(i, j, 1), calc(i, j, i));
            f[i][j] = min(f[i][j], calc(i, j, pivot));
            if (pivot < j) f[i][j] = min(f[i][j], calc(i, j, pivot + 1));
        }
    }
}

class Solution {
   public:
    int superEggDrop(int K, int N) {
        init();
        return f[N][K];
    }
};