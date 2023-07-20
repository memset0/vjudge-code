#include <bits/stdc++.h>
using namespace std;
const int N = 4e3 + 9;
int T, n, m, k, flg[N];
bool ans, vis[N];
vector<pair<int, int>> G[N];

void dfs(int u, int x) {
  if (vis[u]) {
    if (flg[u] != x) ans = false;
    return;
  }
  flg[u] = x;
  vis[u] = true;
  for (const auto &[v, w] : G[u]) {
    dfs(v, x ^ w);
  }
}

bool solve() {
  for (int a, b, c, d, i = 1; i <= k; i++) {
    cin >> a >> b >> c >> d;
    if (b + 1 == d) {
      G[a].emplace_back(n + b, 0);
      G[n + b].emplace_back(a, 0);
    } else {
      G[a].emplace_back(n + b - 1, 1);
      G[n + b - 1].emplace_back(a, 1);
    }
  }
  ans = true;
  for (int u = 1; u <= n + m; u++) {
    if (vis[u]) continue;
    dfs(u, 0);
  }
  return ans;
}

int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m >> k;
    for (int u = 1; u <= n + m; u++) {
      vis[u] = false;
      G[u].clear();
    }
    cout << (solve() ? "YES" : "NO") << "\n";
  }
}