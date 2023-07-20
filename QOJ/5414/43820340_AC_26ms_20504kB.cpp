#include <bits/stdc++.h>
using namespace std;
const int N = 1024;
int T, n, m, k, l, sum[N << 1][N << 1];
string s;
int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n >> m >> k >> s, l = max(n, m) + 5;
    int x = 0, y = 0;
    int xl = 1, xr = n, yl = 1, yr = m;
    for (int i = -l - 3; i <= l + 3; i++) {
      fill(sum[i + N] + N - l - 3, sum[i + N] + N + l + 3, 0);
    }
    sum[N][N] = 1;
    for (int i = 0; i < s.length(); i++) {
      switch (s[i]) {
      case 'U':
        --x;
        break;
      case 'D':
        ++x;
        break;
      case 'L':
        --y;
        break;
      case 'R':
        ++y;
        break;
      }
      xl = max(xl, 1 - x), xr = min(xr, n - x);
      yl = max(yl, 1 - y), yr = min(yr, m - y);
      if (x > -l && y > -l && x <= l && y <= l) {
        // if (!sum[x + N][y + N]) {
        //   cerr << "pin " << x << " " << y << endl;
        // }
        sum[x + N][y + N] = 1;
      }
    }
    for (int i = -l + 1; i <= l; i++)
      for (int j = -l + 1; j <= l; j++) {
        sum[N + i][N + j] += sum[N + i - 1][N + j];
        sum[N + i][N + j] += sum[N + i][N + j - 1];
        sum[N + i][N + j] -= sum[N + i - 1][N + j - 1];
        // fprintf(stderr, "sum[%d][%d] = %d\n", i, j, sum[i + N][j + N]);
      }
    // cerr << xl << " " << xr << " , " << yl << " " << yr << endl;
    int res = xl <= xr && yl <= yr ? (xr - xl + 1) * (yr - yl + 1) : 0;
    // cerr << "res = " << res << endl;
    if (res == 0) {
      cout << (k == 0 ? n * m : 0) << endl;
      continue;
    } else if (k > res) {
      cout << 0 << endl;
      continue;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        int cnt = sum[N + i - xl][N + j - yl];
        cnt -= sum[N + i - xr - 1][N + j - yl];
        cnt -= sum[N + i - xl][N + j - yr - 1];
        cnt += sum[N + i - xr - 1][N + j - yr - 1];
        // fprintf(stderr, "%d %d query[%d,%d][%d,%d] = %d : %d %d %d %d\n", i, j, i - xr, i - xl, j - yr, j - yl, cnt, sum[N + xr - i][N + yr - j], -sum[N + xl - 1 - i][N + yr - j], -sum[N + xr - i][N + yl - 1 - j], sum[N + xl - 1 - i][N + yl - 1 - j]);
        if (res - cnt == k) {
          // cerr << "find " << i << " " << j << endl;
          ans++;
        }
      }
    cout << ans << endl;
  }
}