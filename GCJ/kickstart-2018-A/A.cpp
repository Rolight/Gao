#include <cstdio>
#include <cstring>

typedef long long LL;

bool even(LL n) {
  while (n > 0) {
    if ((n % 10) % 2 == 1)
      return false;
    n /= 10;
  }
  return true;
}

LL f[1000];
LL p10[20], p1[20];

void init() {
  p10[0] = 1;
  p1[0] = 1;
  for (int i = 1; i <= 17; i++) {
    p10[i] = p10[i - 1] * 10;
    p1[i] = p1[i - 1] + p10[i];
  }
}

LL abs(LL n) {
  if (n < 0)
    return -n;
  return n;
}

LL gao(LL n) {
  if (n < 10)
    return n % 2;
  int pos = 0, h = 0;
  LL tmp = n;
  while (tmp > 0) {
    pos++;
    if (tmp < 10)
      h = tmp;
    tmp /= 10;
  }
  if (h % 2 == 0)
    return gao(n - p10[pos - 1] * h);
  LL res1 = p10[pos - 1] * (h + 1) - n;
  LL res2 = n - (p10[pos - 1] * (h - 1) + 8 * p1[pos - 2]);
  if (h == 9)
    return res2;
  if (res1 < res2)
    return res1;
  else
    return res2;
}

int main() {
  init();
  int T;
  scanf("%d", &T);
  for (int kase = 1; kase <= T; kase++) {
    LL n;
    scanf("%lld", &n);
    LL ans = gao(n);
    printf("Case #%d: %lld\n", kase, ans);
  }
  return 0;
}
