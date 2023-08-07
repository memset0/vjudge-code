#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 15;
int n, k, a[N], b[N], c[N];
long long cst[1 << N], dp[N + 1][1 << N];
int main() {
#ifdef memset0
  freopen("C.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i] >> c[i];
  }
  for (int x = 1; x < (1 << n); x++) {
    int aa = INT_MIN, bb = INT_MIN;
    for (int i = 0; i < n; i++)
      if ((x >> i) & 1) {
        aa = max(aa, a[i]);
        bb = max(bb, b[i]);
      }
    for (int i = 0; i < n; i++)
      if ((x >> i) & 1) {
        cst[x] += (long long)c[i] * (aa * bb - a[i] * b[i]);
      }
    // cerr << x << " " << cst[x] << ":" << aa << " " << bb << endl;
  }
  memset(dp, 63, sizeof(dp));
  dp[0][0] = 0;
  for (int x = 0; x < (1 << n); x++) {
    dp[1][x] = cst[x];
    for (int y = x; y != x; (y -= 1) &= x) {
      for (int i = 2; i <= k; i++) {
        dp[i][x] = min(dp[i][x], cst[y] + dp[i - 1][x ^ y]);
      }
    }
  }
  long long ans = LLONG_MAX;
  for (int i = 0; i <= k; i++) ans = min(ans, dp[i][(1 << n) - 1]);
  cout << ans << endl;
}