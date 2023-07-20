#include <bits/stdc++.h>
using namespace std;

int T, n, m;
vector<vector<int>> a, dp;

inline bool check(int x) {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + (a[i][j] <= x);
    }
  // cerr << x << " -> " << dp[n][m] << endl;
  return dp[n][m] == (x + 1);
}

int main() {
#ifdef memset0
  freopen("I.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n >> m;
    a.resize(n + 2), dp.resize(n + 2);
    for (int i = 0; i < a.size(); i++) a[i].resize(m + 2), dp[i].resize(m + 2);

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        cin >> a[i][j];
      }

    int l = 0, r = n * m - 1, mid, ans;
    while (l <= r) {
      mid = (l + r) >> 1;
      check(mid) ? ans = l = mid + 1 : r = mid - 1;
    }
    cout << ans << endl;
  }
}