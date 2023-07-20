#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using Val = __int128;
const int N = 40, n = 36;
int T, k, a[N];
ull x;
Val f[N], dp[N][N];
template <class T> inline void chkmin(T &x, T y) {
  if (y < x) x = y;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin >> T;
  f[0] = 1;
  for (int i = 1; i <= n + 1; i++) f[i] = f[i - 1] * 10;
  while (T--) {
    memset(a, 0, sizeof(a));
    memset(dp, 63, sizeof(dp));
    cin >> x >> k;
    for (int i = 1; i <= n; i++) {
      a[i] = x % 10;
      x /= 10;
    }

    if (k == 0) {
      ull y = 1;
      for (int i = 1; i <= n + 1; i++)
        if (a[i] < 9) {
          cout << y << endl;
          break;
        } else {
          y *= 10;
        }
      continue;
    }

    for (int i = 1; i <= n; i++)
      if (a[i]) {
        int d = 0;
        while (a[i + d + 1] == 9) ++d;
        dp[i + d][1 + d] = f[i - 1] * (10 - a[i]);
      }
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < k; j++)
        if (dp[i][j] != dp[0][0]) {
          for (int v = i + 1; v <= n; v++) {
            int x = v == i + 1 ? a[v] + 1 : a[v];
            if (!x) continue;
            int d = 0;
            while (a[v + d + 1] == 9) ++d;
            chkmin(dp[v + d][j + d + 1], dp[i][j] + f[v - 1] * (10 - x));
            // fprintf(stderr, "dp[%d][%d] -> dp[%d][%d](%d) : %llu + %llu * %d : %llu\n", i, j, v + d, j + d + 1, d, dp[i][j], f[v - 1], 10 - x, dp[v + d][j + d + 1]);
          }
        }

    // for (int i = 1; i <= n; i++)
    //   for (int j = 1; j <= k; j++)
    //     if (dp[i][j] != dp[0][0]) {
    //       printf("dp[%d][%d] = %llu\n", i, j, dp[i][j]);
    //     }

    Val ans = dp[0][0];
    for (int i = 1; i <= n; i++) {
      chkmin(ans, dp[i][k]);
    }

    vector<int> out;
    while (ans) {
      out.push_back(ans % 10);
      ans /= 10;
    }
    for (auto it = out.rbegin(); it != out.rend(); it++) {
      cout << *it;
    }
    cout << endl;
  }
}