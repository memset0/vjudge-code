#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 9;
int T, n, m, val[N];
string op;
long long sum[N];
int tot, fa[N], dep[N], siz[N], son[N], top[N], id[N], rid[N];
vector<pair<int, int>> G[N];
void dfs(int u) {
  siz[u] = 1;
  for (auto &[v, w] : G[u])
    if (v != fa[u]) {
      fa[v] = u, dep[v] = dep[u] + 1;
      val[v] = w, sum[v] = sum[u] + val[v];
      dfs(v);
      siz[u] += siz[v];
      if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs(int u, int tpt) {
  id[u] = ++tot, top[u] = tpt, rid[id[u]] = u;
  if (siz[u] == 1) return;
  dfs(son[u], tpt);
  for (auto &[v, w] : G[u])
    if (v != fa[u] && v != son[u]) dfs(v, v);
}
inline int lca(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] > dep[top[v]]) swap(u, v);
    v = fa[top[v]];
  }
  return dep[u] < dep[v] ? u : v;
}
inline int jump(int u, int k) {
  while (k > dep[u] - dep[top[u]]) {
    k -= dep[u] - dep[top[u]] + 1;
    u = fa[top[u]];
  }
  return rid[id[u] - k];
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    tot = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int u, v, w, i = 1; i < n; i++) {
      cin >> u >> v >> w;
      G[u].emplace_back(v, w);
      G[v].emplace_back(u, w);
    }
    dep[1] = 1, dfs(1), dfs(1, 1);
    while (true) {
      int u, v, k, t;
      cin >> op;
      if (op == "DIST") {
        cin >> u >> v, t = lca(u, v);
        cout << (sum[u] + sum[v] - (sum[t] << 1)) << endl;
      } else if (op == "KTH") {
        cin >> u >> v >> k, t = lca(u, v);
        // fprintf(stderr, "u=%d v=%d t=%d k=%d : %d %d %d\n", u, v, t, k, dep[u], dep[v], dep[t]);
        if (k <= dep[u] - dep[t]) {
          cout << jump(u, k - 1) << endl;
        } else if (k == dep[u] - dep[t] + 1) {
          cout << t << endl;
        } else {
          k -= dep[u] - dep[t] + 1;
          cout << jump(v, dep[v] - dep[t] - k) << endl;
        }
      } else {
        break;
      }
    }
  }
}