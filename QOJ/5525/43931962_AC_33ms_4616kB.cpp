#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int mod = 998244353;
int T, n, m;
vector<vector<int>> a, dp;
int main() {
#ifdef memset0
  freopen("I.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m;
    a.resize(n + 2);
    rep(i, 0, n + 1) a[i].resize(m + 2);
    bool fl = true;
    vector<int> l(n + 2, 1), r(n + 2, m + 1);
    rep(i, 1, n) {
      rep(j, 1, m) {
        cin >> a[i][j];
        if (a[i][j] != -1) {
          if (a[i][j] == i + j) {
            r[i] = min(r[i], j);
          } else if (a[i][j] == i + j - 1) {
            l[i] = max(l[i], j + 1);
          } else {
            fl = false;
          }
        }
      }
      if (l[i] > r[i]) fl = false;
      // fprintf(stderr, "i=%d l=%d r=%d\n", i, l[i], r[i]);
    }
    if (!fl) {
      cout << 0 << endl;
      continue;
    }
    dp.swap(a);
    rep(i, 0, n + 1) rep(j, 0, m + 1) dp[i][j] = 0;
    rep(i, l[1], r[1]) dp[1][i] = true;
    rep(i, 2, n) {
      vector<int> sum(m + 2);
      sum[m + 1] = dp[i - 1][m + 1];
      per(j, m, 1) {
        sum[j] = (sum[j + 1] + dp[i - 1][j]) % mod;
        // fprintf(stderr, "%d : %d %d %d\n", j, sum[j], sum[j + 1], dp[i - 1][j]);
      }
      rep(j, l[i], r[i]) { dp[i][j] = sum[j]; }
    }
    // rep(i, 1, n) { rep(j, 1, m + 1) cerr << dp[i][j] << " \n"[j == m + 1]; }
    int ans = 0;
    rep(j, 1, m + 1) ans = (ans + dp[n][j]) % mod;
    cout << ans << endl;
  }
}