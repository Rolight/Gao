#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int maxn = 128;
const int maxs = 1 << 16;
const int mask = (1 << 16) - 1;

typedef long long LL;

LL N, K, P;
int A[maxn], B[maxn], C[maxn];
LL f[maxn][maxs + 10];
int one_count[maxs + 10];

int getBitsSum(int val) {
    return val == 0 ? 0 : (val & 1) + getBitsSum(val >> 1);
}

void initOneCount() {
    for (int i = 0; i < maxs; i++) {
        one_count[i] = getBitsSum(i);
    }
}

bool checkLast(int pos, int last) {
    for (int i = 0; i < K; i++) {
        if (B[i] < pos || A[i] > pos) continue;
        int len = pos - A[i] + 1;
        int cur_mask = (1 << len) - 1;
        int cur_one_count = one_count[cur_mask & last];
        if (B[i] == pos && cur_one_count != C[i]) return false;
        if (B[i] > pos && cur_one_count > C[i]) return false;
    }
    return true;
}

LL dfs(int pos, int last) {
    if (pos == N + 1) return f[pos][last] = 1;
    int lim = 1;
    if (f[pos][last] != -1) return f[pos][last];
    LL ret = 0;
    for (int i = 0; i <= lim; i++) {
        int new_last = ((last << 1) | i) & mask;
        if (checkLast(pos, new_last)) {
            ret += dfs(pos + 1, new_last);
            ret = min(ret, P);
        }
    }
    f[pos][last] = ret;
    return ret;
}

string solve() {
    string ans = "";
    int cur_last = 0;
    dfs(1, 0);
    for (int i = 1; i <= N; i++) {
        // try 0
        int next_last = (cur_last << 1) & mask;
        LL lcount = f[i + 1][next_last];
        if (lcount != -1 && lcount >= P) {
            cur_last = next_last;
            ans += '0';
            continue;
        }
        // try 1
        next_last |= 1;
        ans += '1';

        if (lcount != -1) {
            P -= lcount;
        }

        cur_last = next_last;
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    initOneCount();
    for (int kase = 1; kase <= T; kase++) {
        cin >> N >> K >> P;
        memset(f, -1, sizeof(f));
        for (int i = 0; i < K; i++) {
            cin >> A[i] >> B[i] >> C[i];
        }
        cout << "Case #" << kase << ": " << solve() << endl;
    }
    return 0;
}