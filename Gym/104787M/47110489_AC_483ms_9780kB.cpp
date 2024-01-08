// AC Onsite

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); i++)
using namespace std;
const int maxn = 3e5;
const int inf = 1e9;
const int mod = 998244353;
typedef long long ll;
#define pb push_back
int n;
bool ok[maxn];
vector<int> g[maxn];
int dp[maxn][2];
void dfs(int v, int p = -1) {
  dp[v][0] = dp[v][1] = 0;
  dp[v][ok[v]] = 1;
  for (int u : g[v]) {
    if (u == p)
      continue;
    dfs(u, v);
    ll x = 1ll * dp[v][0] * dp[u][0] + 2ll * dp[v][0] * dp[u][1];
    ll y = 1ll * dp[v][0] * dp[u][1] + 1ll * dp[v][1] * dp[u][0] +
           2ll * dp[v][1] * dp[u][1];
    dp[v][0] = x % mod;
    dp[v][1] = y % mod;
  }
}
int main() {
  cin >> n;
  int o = 1;
  rep(i, 1, n) {
    int v, u;
    cin >> v >> u;
    g[v].pb(u);
    g[u].pb(v);
    o = 499122177ll * o % mod;
  }
  fill(ok, ok + n + 1, 1);
  rep(i, 1, n) {
    int v;
    cin >> v;
    for (int u : g[v])
      if (ok[u])
        o = 2ll * o % mod;
    ok[v] = 0;
    dfs(1);
    cout << (1ll * dp[1][1] * o) % mod << "\n";
  }
  return 0;
}