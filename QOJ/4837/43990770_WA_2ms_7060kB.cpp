#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 1e5 + 9;
int T, n, m, ans, f[N], dep[N], vis[N], fa[N], tag[N], mx[N], mn[N];
vector<pair<int, int>> G[N];
inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
inline void merge(int u, int v) {
  u = find(u), v = find(v);
  if (u != v) f[u] = v;
}

void dfs(int u) {
  vis[u] = true;
  for (auto &[v, w] : G[u])
    if (v != fa[u]) {
      if (vis[v]) {
        // cerr << "bridge " << u << " " << v << endl;
        if (dep[v] < dep[u]) {
          tag[u]++;
          tag[v]--;
          merge(u, v);
        }
      } else {
        // cerr << "tree " << u << " " << v << endl;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
        tag[u] += tag[v];
      }
    }
  assert(tag[u] >= 0);
  if (tag[u] > 0 && fa[u]) merge(u, fa[u]);
}

int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int u, v, w, i = 1; i <= m; i++) {
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  for (int i = 1; i <= n; i++) f[i] = i;
  dep[1] = 1, dfs(1);
  fill(mx + 1, mx + n + 1, INT_MIN);
  fill(mn + 1, mn + n + 1, INT_MAX);
  // for (int i = 1; i <= n; i++) cerr << find(i) << " \n"[i == n];
  for (int u = 1; u <= n; u++)
    for (auto &[v, w] : G[u])
      if (find(u) == find(v)) {
        mx[find(u)] = max(mx[find(u)], w);
        mn[find(u)] = min(mn[find(u)], w);
      }
  int ans = INT_MIN;
  for (int i = 1; i <= n; i++)
    if (find(i) == i) {
      if (mx[i] != INT_MIN && mn[i] != INT_MAX) {
        ans = max(ans, mx[i] - mn[i]);
      }
    }
  cout << ans << endl;
}