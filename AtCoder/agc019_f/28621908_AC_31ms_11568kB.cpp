#include <bits/stdc++.h>
using namespace std;

const int N = 1e6, mod = 998244353;
int fac[N + 5], ifac[N + 5];

int fpow(int a, int b) {
  int ans = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1)
      ans = 1ll * ans * a % mod;
  return ans;
}

void init() {
  fac[0] = 1;
  for (int i = 1; i <= N; i++)
    fac[i] = 1ll * fac[i - 1] * i % mod;
  ifac[N] = fpow(fac[N], mod - 2);
  for (int i = N - 1; i >= 0; i--)
    ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}

inline int C(const int &n, const int &m) {
  return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
inline int invC(const int &n, const int &m) {
  return 1ll * ifac[n] * fac[m] % mod * fac[n - m] % mod;
}

int main() {
  int n, m;
  init();
  cin >> n >> m;
  int t = min(n, m), ans = 0;
  for (int i = 1; i <= t; i++)
    ans = (ans + 1ll * C(2 * i, i) * C(n + m - 2 * i, n - i)) % mod;
  ans = 1ll * ans * invC(n + m, n) % mod * ifac[2] % mod;
  printf("%d\n", (ans + max(n, m)) % mod);
  return 0;
}