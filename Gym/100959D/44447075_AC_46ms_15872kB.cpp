#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 9, V = N << 1, mod = 1e9 + 7;
int n, a[N], b[N], fac[V], ifac[V];
int dp[N][N], g[N], h[N];
inline void dec(int &x, int y) {
  x -= y;
  if (x < 0) x += mod;
}
inline void inc(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}
inline int C(int n, int m) { return (long long)fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  fac[0] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i < V; i++) ifac[i] = (long long)(mod - mod / i) * ifac[mod % i] % mod;
  for (int i = 1; i < V; i++) fac[i] = (long long)fac[i - 1] * i % mod, ifac[i] = (long long)ifac[i - 1] * ifac[i] % mod;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  for (int i = 1; i <= n; i++) {
    h[i] = (long long)C(i << 1, i) * ((mod + 1) >> 1) % mod;
    g[i] = h[i];
    for (int j = 1; j < i; j++) dec(g[i], (long long)g[j] * h[i - j] % mod * 2 % mod);
  }
  // for (int i = 1; i <= n; i++) cerr << g[i] << " \n"[i == n];
  // for (int i = 1; i <= n; i++) cerr << h[i] << " \n"[i == n];
  dp[0][0] = 1;
  for (int i = 0; i <= n; i++)
    for (int j = i ? 0 : 1; j <= n; j++) {
      if (i) inc(dp[i][j], dp[i - 1][j]);
      if (j) inc(dp[i][j], dp[i][j - 1]);
      // fprintf(stderr, "dp[%d][%d] = %d\n", i, j, dp[i][j]);
      for (int k = 1; k <= n && i >= k && j >= k; k++)
        if (a[i - k + 1] == b[j - k + 1]) {
          dec(dp[i][j], (long long)dp[i - k][j - k] * g[k] % mod);
          // fprintf(stderr, "i=%d j=%d k=%d : %d %d\n", i, j, k, dp[i - k][j - k], g[k]);
        } else {
          break;
        }
      // fprintf(stderr, "dp[%d][%d] = %d\n", i, j, dp[i][j]);
    }
  // for (int i = 0; i <= n; i++)
  //   for (int j = 0; j <= n; j++) {
  //     cout << dp[i][j] << " \n"[j == n];
  //   }
  cout << dp[n][n] << endl;
}