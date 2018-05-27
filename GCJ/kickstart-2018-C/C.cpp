#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const int maxn = 1e6 + 10;
const int maxk = 1e4 + 10;
const LL mod = 1e9 + 7;

LL A[maxn];
LL N, K;
LL x1, y1, C, D, E1, E2, F;
LL Countj[maxn];
LL T[maxn];

LL quick_pow(LL a, LL k)
{
    LL ret = 1;
    while (k)
    {
        if (k % 2 == 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod;
        k /= 2;
    }
    return ret;
}

LL inv(LL a) { return quick_pow(a, mod - 2); }

LL gao()
{
    // 计算等比数列的和
    T[1] = K;
    for (int i = 2; i <= N; i++)
    {
        LL cur = quick_pow(i, K + 1) - i;
        while (cur < 0)
            cur += mod;
        cur %= mod;
        LL dim = inv(i - 1);
        cur = (cur * dim) % mod;
        T[i] = cur;
    }

    LL ans = 0, front = N + 1, tail = 0;
    for (int i = 1; i <= N; i++)
    {
        --front;
        tail = (tail + T[i]) % mod;
        ans += A[i] * (front * tail % mod) % mod;
        ans %= mod;
    }
    cerr << ans << endl;
    return ans;
}

int main()
{
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; ++kase)
    {
        cin >> N >> K;
        cin >> x1 >> y1 >> C >> D >> E1 >> E2 >> F;
        A[1] = (x1 + y1) % F;
        LL cx = x1, cy = y1;
        for (int i = 2; i <= N; i++)
        {
            LL nx = (C * cx + D * cy + E1) % F;
            LL ny = (D * cx + C * cy + E2) % F;
            A[i] = (nx + ny) % F;
            cx = nx;
            cy = ny;
        }
        LL ans = gao();
        cout << "Case #" << kase << ": " << ans << endl;
    }
    return 0;
}