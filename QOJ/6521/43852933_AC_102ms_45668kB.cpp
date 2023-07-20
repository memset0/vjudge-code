#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int T, n, a[N], sl[N], sr[N], f[N][30], g[N][30];
map<int, vector<int>> L, R;
inline int transfer(int x, int y) { return x ? -1 : y; }
inline int getl(int l, int x) {
  if (L.find(x) != L.end()) {
    return L[x][l];
  }
  L[x] = vector<int>(n + 2);
  auto &f = L[x];
  f[1] = x & a[1];
  for (int i = 2; i <= n; i++) {
    f[i] = max(f[i - 1], x & a[i]);
  }
  return f[l];
}
inline int getr(int r, int x) {
  if (R.find(x) != R.end()) {
    return R[x][r];
  }
  R[x] = vector<int>(n + 2);
  auto &f = R[x];
  f[n] = x & a[n];
  for (int i = n - 1; i >= 1; i--) {
    f[i] = max(f[i + 1], x & a[i]);
  }
  return f[r];
}
int main() {
#ifdef memset0
  freopen("G.in", "r", stdin);
#endif
  cin >> T;
  a[-1] = (1 << 30) - 1;
  while (T--) {
    L.clear(), R.clear();
    int ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      sl[i] = i == 1 ? a[1] : (sl[i - 1] & a[i]);
    }
    for (int i = n; i >= 1; i--) {
      sr[i] = i == n ? a[n] : (sr[i + 1] & a[i]);
    }
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < 30; j++)
        if (!(a[i] & (1 << j))) {
          // fprintf(stderr, "f[%d][%d] = %d %d\n", i, j, f[i - 1][j], i);
          f[i][j] = transfer(f[i - 1][j], i);
        } else {
          f[i][j] = f[i - 1][j];
        }
    memset(g[n + 1], 0, sizeof(g[n + 1]));
    for (int i = n; i >= 1; i--)
      for (int j = 0; j < 30; j++)
        if (!(a[i] & (1 << j))) {
          g[i][j] = transfer(g[i + 1][j], i);
        } else {
          g[i][j] = g[i + 1][j];
        }
    for (int l = 1, r = 2; l < n; l++, r++) {
      vector<pair<int, int>> xx, yy;
      for (int i = 0; i < 30; i++)
        if (f[l][i] && f[l][i] != -1) xx.emplace_back(f[l][i], 0);
      for (int i = 0; i < 30; i++)
        if (g[r][i] && g[r][i] != -1) yy.emplace_back(g[r][i], 0);
      sort(xx.begin(), xx.end()), xx.erase(unique(xx.begin(), xx.end()), xx.end());
      sort(yy.begin(), yy.end()), yy.erase(unique(yy.begin(), yy.end()), yy.end());
      for (auto &[x, w] : xx) {
        for (int i = 0; i < 30; i++)
          if (!f[l][i] || f[l][i] == x) w |= 1 << i;
      }
      for (auto &[y, w] : yy) {
        for (int i = 0; i < 30; i++)
          if (!g[r][i] || g[r][i] == y) w |= 1 << i;
      }
      // cerr << "===== " << l << " " << r << " =====" << endl;
      // for (int i = 0; i < 10; i++) cerr << f[l][i] << " \n"[i == 9];
      // for (int i = 0; i < 10; i++) cerr << g[r][i] << " \n"[i == 9];
      ans = max(ans, sl[l] + sr[r]);
      ans = max(ans, getl(l, sr[r]) + getr(r, sl[l]));
      for (const auto &[x, w1] : xx) {
        ans = max(ans, (a[x] & sr[r]) + getr(r, w1));
      }
      for (const auto &[y, w2] : yy) {
        ans = max(ans, (a[y] & sl[l]) + getl(l, w2));
      }
      for (const auto &[x, w1] : xx)
        for (const auto &[y, w2] : yy) {
          // fprintf(stderr, ">> %d %d : %d (%d,%d,%d) %d (%d,%d,%d)\n", l, r, x, w1, a[y], w1 & a[y], y, w2, a[x], w2 & a[x]);
          ans = max(ans, (w1 & a[y]) + (w2 & a[x]));
        }
      // cerr << endl;
    }
    cout << ans << endl;
  }
}