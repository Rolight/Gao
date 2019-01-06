#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long LL;
const LL mod = 1e9 + 7;
LL f[102][102];
LL A[102][102];
LL g[102];

class Solution {
    LL dfs(LL N, LL L, LL K) {
        if(N > L) return 0;
        if(N == 1 && K == 0) return 1;
        if(N == 1 && L == 1) return 1;
        if(N == 1) return 0;
        if(f[N][L] != -1) return f[N][L];
        return f[N][L] = (dfs(N, L - 1, K) * max(N - K, 0LL) % mod + dfs(N - 1, L - 1, K) * N % mod) % mod;
    }
public:
    int numMusicPlaylists(int N, int L, int K) {
        memset(f, -1, sizeof(f));
        return dfs(N, L, K);
    }
};