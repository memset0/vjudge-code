#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (r), i##end = (l); i <= i##end; i--)
using namespace std;
const int N = 1e3 + 9, mod = 998244353;
int n, m, ans, p[2][N][N], sum[2][N][N];
int main() {
#ifdef memset0
  freopen("B.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  rep(i, 1, n) rep(j, 1, m) cin >> p[0][i][j];
  rep(i, 1, n) rep(j, 1, m) cin >> p[1][i][j];
  rep(i, 1, n) rep(j, 1, m) {
    sum[0][i][j] = (sum[0][i][j - 1] + p[0][i][j]) % mod;
    sum[1][i][j] = (sum[1][i - 1][j] + p[1][i][j]) % mod;
  }
  rep(i, 0, n + 1) sum[0][i][m + 1] = sum[1][i][m + 1] = 1;
  rep(i, 0, m + 1) sum[0][n + 1][i] = sum[1][n + 1][i] = 1;
  rep(i, 1, n) rep(j, 1, m) {
    ans = (ans + 1ll * sum[0][i][j - 1] * sum[1][i - 1][j] % mod * (mod + 1 - sum[0][i + 1][j - 1]) % mod * (mod + 1 - sum[1][i - 1][j + 1])) % mod;
    // fprintf(stderr, "%d,%d :: %d %d %d %d\n", i, j, sum[0][i][j - 1], sum[1][i - 1][j], -sum[0][i + 1][j - 1], -sum[1][i - 1][j + 1]);
  }
  cout << (ans + 2) % mod << endl;
}