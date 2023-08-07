#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 5e3 + 9, K = 109, M = 19;
int T, n, m, a[N], dp[K][N];
inline void upd(int &x, int y) {
  if (y > x) x = y;
}
int main() {
#ifdef memset0
  freopen("H.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 0; i < K; i++) fill(dp[i], dp[i] + n + 1, -1);
    for (int i = 1; i <= m; i++) cin >> a[i];
    dp[0][0] = 0;
    for (int i = 0; i + 1 < K; i++)
      for (int j = 0; j <= n; j++)
        if (~dp[i][j]) {
          for (int u = 1; u <= m; u++) {
            int k = j + (i + 1) * a[u];
            if (k <= n) {
              // fprintf(stderr, "dp[%d][%d] -> dp[%d][%d] : %d\n", i, j, i + 1, k, a[u]);
              upd(dp[i + 1][k], dp[i][j] + a[u]);
            }
          }
        }
    int ans = -1;
    for (int i = 0; i < K; i++) ans = max(ans, dp[i][n]);
    cout << ans << endl;
  }
}