#include <bits/stdc++.h>
#define rep(i, st, ed) for (int i = st; i <= ed; ++i)
#define drp(i, st, ed) for (int i = st; i >= ed; --i)

const int N = 5e5 + 9, mod = 1e9 + 7;

long long a[N + 1], b[N + 1], c[N + 1], inv[N + 1];

long long fpow(long long x, long long dep) {
  if (dep == 0)
    return 1;
  if (dep == 1)
    return x;
  long long tmp = fpow(x, dep / 2);
  if (dep % 2)
    return tmp * tmp % mod * x % mod;
  return tmp * tmp % mod;
}

void solve(long long n, long long m) {
  if (n <= m + 2) {
    printf("%lld\n", a[n]);
    return;
  }
  n = n % mod;
  b[0] = c[m + 3] = 1;
  rep(i, 1, m + 2) b[i] = b[i - 1] * (n - i) % mod;
  drp(i, m + 2, 1) c[i] = c[i + 1] * (n - i) % mod;
  long long ans = 0, rec = 1;
  rep(i, 2, m + 2) rec = rec * (1 - i) % mod;
  rec = fpow(rec, mod - 2);
  rep(i, 1, m + 2) {
    ans = (ans + a[i] * b[i - 1] % mod * c[i + 1] % mod * rec % mod) % mod;
    rec = rec * (i - m - 2) % mod * inv[i] % mod;
  }
  printf("%lld\n", (ans + mod) % mod);
}

int main(void) {
  rep(i, 1, N) inv[i] = fpow(i, mod - 2);
  int T;
  scanf("%d", &T);
  while (T--) {
    long long n, m;
    scanf("%lld%lld", &n, &m);
    rep(i, 1, m + 2) a[i] = (a[i - 1] + fpow(i, m)) % mod;
    solve(n, m);
  }
  return 0;
}