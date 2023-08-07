#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const int N = 5e3 + 9;
int n, mod, ans, C[N][N], pw[N];
ll f[N], g[N];
int main() {
#ifdef memset0
  freopen("H.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> mod;
	pw[0] = 1;
	for (int i = 1; i < N; i++) pw[i] = 4ll * pw[i-1] % mod;
  for (int i = 0; i < N; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) C[i][j] = ((ll)C[i - 1][j] + C[i - 1][j - 1]) % mod;
  }
  for (int i = 0; i <= n; i++)
    for (int j = 0; (i + j) * 2 <= n; j++) {
      (f[i + j] += (ll)C[i * 2 + j * 2][i * 2] * C[i * 2][i] % mod * C[j * 2][j] % mod) %= mod;
    }
  for (int i = 1; i * 2 <= n; i++) {
    g[i] = f[i];
    for (int j = 1; j < i; j++) {
      (g[i] -= f[j] * g[i - j] % mod) %= mod;
    }
  }
  // for (int i = 1; i <= (n >> 1); i++) cout << f[i] << " \n"[i == (n >> 1)];
  // for (int i = 1; i <= (n >> 1); i++) cout << g[i] << " \n"[i == (n >> 1)];
  ll ans = (ll)(n + 1) * pw[n] % mod;
  for (int i = 1; i <= (n >> 1); i++) {
    // cout << i << " :: " << g[i] << " " << (n - i * 2 + 1) << endl;
    (ans -= (ll)(n - i * 2 + 1) * g[i] % mod * pw[n - i * 2] % mod) %= mod;
  }
  cout << (ans + mod) % mod << endl;
}