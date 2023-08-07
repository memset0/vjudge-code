#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 2e5 + 9;
int n;
int tot, fa[N], dep[N], dfn[N], top[N], siz[N], son[N];
vector<int> G[N];
void dfs(int u) {
  siz[u] = 1;
  for (int v : G[u])
    if (v != fa[u]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      dfs(v);
      siz[u] += siz[v];
      if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs(int u, int tpt) {
  top[u] = tpt;
  dfn[u] = ++tot;
  if (siz[u] == 1) return;
  dfs(son[u], tpt);
  for (int v : G[u])
    if (v != fa[u] && v != son[u]) {
      dfs(v, v);
    }
}
inline int lca(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] > dep[top[v]]) {
      swap(u, v);
    }
    v = fa[top[v]];
  }
  return dep[u] < dep[v] ? u : v;
}
int main() {
#ifdef memset0
  freopen("I.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int u, v, i = 1; i < n; i++) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dep[1] = 1;
  dfs(1);
  dfs(1, 1);
  long long ans = 0;
  for (int i = 1; i <= n; i++)
    for (int j = i * 2; j <= n; j += i) {
      int k = lca(i, j);
      // cerr << i << " " << j << " " << k << endl;
      ans += dep[i] + dep[j] - dep[k] * 2 + 1;
    }
  cout << ans << endl;
}