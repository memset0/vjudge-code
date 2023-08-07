#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 9;
int n, m, a[N], f[N], g[N], s[N];
inline void add(int k, int x) {
  for (; k <= n + 2; k += k & -k) s[k] = max(s[k], x);
}
inline int ask(int k) {
  int r = -1;
  for (; k; k -= k & -k) r = max(r, s[k]);
  return r;
}
void solve(int *a, int *f) {
  memset(s, -1, (n + 3) << 2);
  for (int i = 1; i <= m; i++) {
    f[i] = ask(a[i]);
    add(a[i] + 1, i);
  }
  // for (int i = 1; i <= m; i++) cerr << a[i] << " \n"[i == m];
  // for (int i = 1; i <= m; i++) cerr << f[i] << " \n"[i == m];
}
int main() {
#ifdef memset0
  freopen("A2.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  vector<int> tmp;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    tmp.push_back(a[i]);
  }
  sort(tmp.begin(), tmp.end());
  tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
  for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1;
    a[i + n] = a[i];
    a[i + n * 2] = a[i];
  }
  m = n * 3;
  solve(a, f);
  reverse(a + 1, a + m + 1);
  solve(a, g);
  reverse(g + 1, g + m + 1);
  for (int i = 1; i <= m; i++)
    if (~g[i]) g[i] = m + 1 - g[i];
  int ans = INT_MAX;
  // for (int i = 1; i <= m; i++) cerr << f[i] << " \n"[i == m];
  // for (int i = 1; i <= m; i++) cerr << g[i] << " \n"[i == m];
  for (int i = 1; i <= m; i++)
    if (f[i] != -1 && g[i] != -1) {
      ans = min(ans, g[i] - f[i]);
    }
  // cerr << "ans = " << ans << endl;
  auto shape = [&](int x) {
    while (x > n) x -= n;
    return x;
  };
  for (int i = 1; i <= m; i++)
    if (f[i] != -1 && g[i] != -1 && g[i] - f[i] == ans) {
      cout << shape(f[i]) << " " << shape(i) << " " << shape(g[i]) << endl;
      return 0;
    }
}