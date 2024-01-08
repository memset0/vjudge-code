#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 9;
int n, f[N], g[N][26], a[N];
int main() {
#ifdef memset0
  freopen("game1.in", "r", stdin);
  freopen("game.out", "w", stdout);
#else
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  string t;
  cin >> n >> t;
  for (int i = 1; i <= n; i++) {
    a[i] = t[i - 1] - 'a';
  }
  for (int i = 1; i <= n; i++) {
    if (g[i - 1][a[i]]) {
      int lst = g[i - 1][a[i]] - 1;
      f[i] = f[lst] + 1;
      for (int j = 0; j < 26; j++) g[i][j] = max(g[i][j], g[lst][j]);
    }
    g[i][a[i]] = i;
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) ans += f[i];
  cout << ans << endl;
}