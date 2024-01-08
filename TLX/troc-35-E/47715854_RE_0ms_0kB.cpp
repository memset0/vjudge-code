#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
const int N = 4e5 + 9, mod = 998244353;
int T, n, m, fac[N], ifac[N];
int C(int n, int m) {
  if (n < m) return 0;
  return (long long)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  fac[0] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i < N; i++) ifac[i] = (long long)(mod - mod / i) * ifac[mod % i] % mod;
  for (int i = 1; i < N; i++) fac[i] = (long long)fac[i - 1] * i % mod, ifac[i] = (long long)ifac[i - 1] * ifac[i] % mod;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    long long ans = 0;
    // cerr << "! " << n << " " << m << " > " << ans << endl;
    for (int k = m - (n - 1) / 2; k < m; k++) {
      // 和比 m 小的情况，可以任意安排
      ans += C(k + n - 1, n - 1);
    }
    // for (int k = 1; (k << 1) <= n; k++) {
    //   // 和比 m 大的情况，如果大 k，至少要有 2k 个位置非 0
    //   ans += C(m + k + n - 1, n - 1);
    //   for (int j = 1; j < (k << 1); j++) {
    //     fprintf(stderr, "AAA j=%d k=%d => %d * %d\n", j, k, C(n, j), C(m + k - 1, j - 1));
    //     ans -= (long long)C(n, j) * C(m + k - 1, j - 1) % mod;
    //   }
    // }
    for (int k = 1; (k << 1) <= n; k++) {
      ans += C(m + k + n - 1, n - 1);
    }
    for (int j = 1; j <= n; j++) {
      int l = j / 2 + 1, r = n / 2;
      if (l <= r) {
        ans -= (long long)C(n, j) * C(m + r, j) % mod;
        ans += (long long)C(n, j) * C(m + l - 1, j) % mod;
        // fprintf(stderr, "+= %d\n-= %d\n", C(m + r + 1, j), C(m + l, j));
        // for (int k = j / 2 + 1; k <= n / 2; k++) {
        //   fprintf(stderr, "BBB j=%d k=%d => %d * %d\n", j, k, C(n, j), C(m + k - 1, j - 1));
        //   // sum += C(m + k - 1, j - 1);
        // }
      }
    }
    cout << (ans % mod + mod) % mod << endl;
  }
}