#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9, M = 509;
int n, m, target, id[N], w[N], fa[N], dep[N], lazy[N], leaf[N], lca[M][M];
bool found;
vector<int> G[N];
vector<int> leaves[N];
vector<pair<int, pair<int, int>>> values;
inline int abs(int x) { return x < 0 ? -x : x; }
void dfs(int u) {
  if (G[u].size() == 1) {
    leaves[u].push_back(u);
  }
  for (int v : G[u])
    if (v != fa[u]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      dfs(v);
      for (int x : leaves[u])
        for (int y : leaves[v]) {
          lca[id[x]][id[y]] = lca[id[y]][id[x]] = u;
        }
      for (int y : leaves[v]) {
        leaves[u].push_back(y);
      }
    }
}
void solve(int u) {
  for (int v : G[u])
    if (v != fa[u]) {
      solve(v);
      lazy[u] += lazy[v];
    }
  if (lazy[u] == target) {
    found = true;
    // cerr << "found: " << u << endl;
  }
}
inline bool check(int x) {
  // cerr << "check " << x << endl;
  target = found = 0;
  fill(lazy, lazy + n + 1, 0);
  for (int i = 0; i < values.size(); i++)
    if (values[i].first > x) {
      target++;
      auto [x, y] = values[i].second;
      int u = leaf[x], v = leaf[y], t = lca[x][y];
      // cerr << ">>" << u << " " << v << " " << t << endl;
      lazy[u]++;
      lazy[v]++;
      lazy[t]--;
      lazy[fa[t]]--;
    }
  solve(1);
  // cerr << "found = " << found << endl;
  return found;
}
int main() {
#ifdef memset0
  freopen("F.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> w[i];
  for (int u, v, i = 1; i < n; i++) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for (int i = 1; i <= n; i++)
    if (G[i].size() == 1) {
      leaf[++m] = i;
      id[i] = m;
    }
  // cerr << "m = " << m << endl;
  dep[1] = 1, dfs(1);
  for (int i = 1; i <= m; i++)
    for (int j = i + 1; j <= m; j++) {
      // cerr << leaf[i] << " " << leaf[j] << " " << abs(w[leaf[i]] - w[leaf[j]]) << endl;
      values.emplace_back(abs(w[leaf[i]] - w[leaf[j]]), make_pair(i, j));
    }
  sort(values.begin(), values.end());
  int l = 0, r = (int)values.size() - 1, mid, ans = 0;
  if (check(0)) {
    cout << 0 << endl;
    return 0;
  }
  while (l <= r) {
    mid = (l + r) >> 1;
    if (check(values[mid].first)) {
      ans = values[mid].first;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << endl;
}