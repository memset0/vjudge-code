#include <bits/stdc++.h>

inline int read() {
  char c, _c;
  int x;
  for (c = _c = getchar(); !isdigit(c); c = getchar()) {
    _c = c;
  }
  for (x = 0; isdigit(c); c = getchar()) {
    x = x * 10 + c - '0';
  }
  return _c == '-' ? -x : x;
}

const int mod = 998244353, inv2 = (mod + 1) / 2;
const double eps = 1e-7;

inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int sub(int x, int y) { return x - y >= 0 ? x - y : x - y + mod; }
inline int power(int x, int y) {
  int res = 1;
  for (; y; y >>= 1, x = 1ll * x * x % mod) {
    if (y & 1) {
      res = 1ll * res * x % mod;
    }
  }
  return res;
}

const int N = 3e3 + 5;

int n, m, ans, dp[N], ds[N], a[N * 2], inv[N], fac[N], invf[N];
int f[N][N], g[N][N], w[N][N], v[N][N], ff[N], gg[N];

void init(int n) {
  inv[1] = 1;
  for (int i = 2; i <= n; i++) {
    inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
  }
  fac[0] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = 1ll * fac[i - 1] * i % mod;
  }
  invf[n] = power(fac[n], mod - 2);
  for (int i = n; i >= 1; i--) {
    invf[i - 1] = 1ll * invf[i] * i % mod;
  }
}

void solve() {
  std::vector<int> x;
  for (int i = 1; i < m; i += 2) {
    x.push_back((a[i] % mod + mod) % mod);
  }
  for (int i = 0; i < n; i++) {
    ff[i] = add(f[n - 1][i], 1ll * inv[n - i] * ds[n - i - 1] % mod);
  }
  for (int i = 0; i < n; i++) {
    ans = sub(ans, 1ll * x[i] * ff[i] % mod);
  }
  std::vector<int> y;
  for (int j = 2; j < m; j += 2) {
    y.push_back((a[j] % mod + mod) % mod);
  }
  for (int j = 0; j < n; j++) {
    gg[j] = add(g[n - 1][j], 1ll * dp[n - j - 1] * v[n - j - 1][j] % mod);
  }
  for (int j = 0; j < n; j++) {
    ans = add(ans, 1ll * y[j] * gg[j] % mod);
  }
}

int main() {
  n = 3e3;
  init(n + 3);
  dp[0] = 1;
  dp[1] = inv2;
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      dp[i] = add(dp[i], 1ll * dp[j] * dp[i - j] % mod);
    }
    dp[i] = 1ll * inv2 * sub(1, dp[i]) % mod;
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      ds[i] = add(ds[i], 1ll * dp[j] * dp[i - j] % mod);
    }
  }
  for (m = 0; m <= n; m++) {
    for (int j = 0; j <= n - m; j++) {
      if (j > 0) {
        w[m][j] = w[m][j - 1];
        v[m][j] = v[m][j - 1];
      }
      w[m][j] = add(w[m][j],
                    1ll * dp[j] * inv[m + j + 1] % mod * inv[m + j + 2] % mod);
      v[m][j] = add(v[m][j], 1ll * dp[j] * inv[m + j + 1] % mod);
    }
  }
  for (m = 1; m <= n; m++) {
    for (int i = 0; i < m; i++) {
      f[m][i] = add(f[m - 1][i], 1ll * inv[m - i] * inv[m - i + 1] % mod *
                                     ds[m - i - 1] % mod);
    }
  }
  for (m = 1; m <= n; m++) {
    for (int j = 0; j < m; j++) {
      g[m][j] = add(g[m - 1][j], 1ll * dp[m - j - 1] * w[m - j - 1][j] % mod);
    }
  }
  for (int T = read(); T; T--) {
    n = read();
    m = n * 2 + 1;
    for (int i = 0; i < m; i++) {
      a[i] = read();
    }
    ans = 0;
    solve();
    std::reverse(a, a + m);
    for (int i = 0; i < m; i++) {
      a[i] = -a[i];
    }
    solve();
    ans = 1ll * ans * inv2 % mod;
    printf("%d\n", ans);
  }
  return 0;
}