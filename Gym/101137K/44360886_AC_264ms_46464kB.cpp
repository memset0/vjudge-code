#include <bits/stdc++.h>
using namespace std;
const int N = 6e5 + 9;
int n, m, a[N], b[N], fa[N], ch[N][2];
long long dp[N];
vector<tuple<int, int, int>> edg;
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void DP(int u) {
  if (u <= n) {
    dp[u] = (long long)a[u] * b[u];
  } else {
    b[u] = INT_MAX;
    for (int i = 0; i < 2; i++) {
      DP(ch[u][i]);
      b[u] = min(b[u], b[ch[u][i]]);
      dp[u] += dp[ch[u][i]];
    }
    dp[u] = min(dp[u], (long long)a[u] * b[u]);
  }
}
int main() {
#ifdef memset0
  freopen("K.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }
  for (int u, v, w, i = 1; i <= m; i++) {
    cin >> u >> v >> w;
    w = max(w, a[u]);
    w = max(w, a[v]);
    edg.emplace_back(w, u, v);
  }
  sort(edg.begin(), edg.end());
  int tot = n;
  for (int i = 1; i <= n + m; i++) fa[i] = i;
  for (auto [w, u, v] : edg) {
    if (find(u) != find(v)) {
      ++tot;
      a[tot] = w;
      ch[tot][0] = find(u);
      ch[tot][1] = find(v);
      fa[find(u)] = tot;
      fa[find(v)] = tot;
    }
  }
  long long ans = 0;
  for (int i = 1; i <= tot; i++)
    if (find(i) == i) {
      DP(i);
      ans += dp[i];
    }
  cout << ans << endl;
}