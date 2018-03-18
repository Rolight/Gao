#include <algorithm>
#include <cstdio>
#include <cstring>

const int maxn = 20000 + 10;
const int maxk = 50000 + 10;

int n, k;
double v[maxn], vsum[maxn];

double gao() {
  memset(vsum, 0, sizeof(vsum));
  double ans = 0;
  std::sort(v + 1, v + 1 + n);
  double cur_exp = 0;
  for (int i = 1; i <= n; i++) {
    vsum[i] = vsum[i - 1] + v[i];
  }
  if (k == 0) {
    return vsum[n] / n;
  } else {
    double ep = vsum[n] / n;
    for (int kk = 1; kk <= k; kk++) {
      double cur_ep = 0;
      int rnk = std::lower_bound(v + 1, v + 1 + n, ep) - v;
      cur_ep += (rnk - 1) * ep / n;
      cur_ep += (vsum[n] - vsum[rnk - 1]) / n;
      ep = ans = cur_ep;
    }
    return ans;
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int kase = 1; kase <= T; kase++) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%lf", &v[i]);
    }
    double ans = gao();
    printf("Case #%d: %.15f\n", kase, ans);
  }
  return 0;
}
