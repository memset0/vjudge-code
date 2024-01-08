#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 9, M = 4e2 + 9;
int n, m, s[N], t[N], f[M][M];
template <class T> inline void updmin(T &x, const T &y) {
  if (y < x) x = y;
}
template <class T> inline void updmax(T &x, const T &y) {
  if (y > x) x = y;
}
int main() {
#ifdef memset0
  freopen("F.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> s[i];
  for (int i = 0; i < n; i++) cin >> t[i];
  memset(f, 63, sizeof(f));
  int p = 0;
  for (int a, b, c, i = 1; i <= m; i++) {
    cin >> a >> b >> c;
    updmax(p, a);
    updmax(p, b);
    updmin(f[a][b], c);
  }
  for (int i = 1; i <= p; i++) f[i][i] = 0;
  for (int k = 1; k <= p; k++)
    for (int i = 1; i <= p; i++)
      for (int j = 1; j <= p; j++) {
        updmin(f[i][j], f[i][k] + f[k][j]);
      }
  for (int i = 1; i <= p; i++)
    for (int j = i + 1; j <= p; j++) {
      f[i][j] = f[j][i] = min(f[i][j], f[j][i]);
    }
  long long ans = LLONG_MAX;
  for (int d = 0; d < n; d++) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
      sum += f[s[i]][t[(i + d) % n]];
    }
    updmin(ans, sum);
  }
  cout << ans << endl;
}