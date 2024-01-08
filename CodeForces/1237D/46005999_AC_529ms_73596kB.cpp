#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 9, K = 20;
int n, offset, a[N], mx[N][K], mn[N][K], ans[N];
bool f[N][K];
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[n + i] = a[i];
    a[n * 2 + i] = a[i];
    a[n * 3 + i] = a[i];
  }
  n = n << 2;
  for (int i = 1; i < n; i++) {
    mx[i][0] = max(a[i], a[i + 1]);
    mn[i][0] = min(a[i], a[i + 1]);
  }
  for (int j = 1; j < K; j++)
    for (int i = 1; i <= n; i++) {
      if (i + (1 << j) <= n) {
        mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
        mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
      }
    }
  for (int i = 1; i <= n; i++) { f[i][0] = i < n && ((a[i] + 1) >> 1) <= a[i + 1]; }
  for (int j = 1; j < K; j++) {
    for (int i = 1; i <= n; i++) {
      if (i + (1 << j) > n) { continue; }
      if (f[i][j - 1] && f[i + (1 << (j - 1))][j - 1]) {
        if (((mx[i][j - 1] + 1) >> 1) <= mn[i + (1 << (j - 1))][j - 1]) { f[i][j] = true; }
      }
      // fprintf(stderr, "f[%d][%d]=%d | %d %d %d %d\n", i, j, f[i][j], f[i][j - 1], f[i + (1 << (j - 1))][j - 1], mx[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
    }
  }

  for (int i = 1; i <= n; i++) {
    ans[i] = i;
    int pre = a[i];
    for (int j = K - 1; j >= 0; j--)
      if (ans[i] + (1 << j) <= n) {
        if (f[ans[i]][j] && ((pre + 1) >> 1) <= mn[ans[i]][j]) {
          // cerr << "choose " << j << " " << pre << " " << mn[ans[i]][j] << " " << f[ans[i]][j] << endl;
          pre = max(pre, mx[ans[i]][j]);
          ans[i] += 1 << j;
        }
      }
    // fprintf(stderr, "i=%d ans[%d]=%d\n", i, i, ans[i]);
  }

  n >>= 2;
  for (int i = 1; i <= n; i++) {
    ans[i] = ans[i] - i + 1;
    if (ans[i] > n * 2) ans[i] = -1;
    cout << ans[i] << " \n"[i == n];
  }
}