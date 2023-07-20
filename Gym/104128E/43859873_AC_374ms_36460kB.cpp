#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int T, n, cur, tim, a[N], fa[N], dfn[N], dep[N], jp[N][20], vfa[N];
long long ans = 0;
vector<int> todo, G[N], E[N], h[N];
struct Segment {
  int l, r, mid, min;
} p[N << 2];
inline bool cmp(int u, int v) { return dfn[u] < dfn[v]; }
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  if (l == r) {
    p[u].min = a[l];
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
  p[u].min = min(p[u << 1].min, p[u << 1 | 1].min);
}
int query(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) return p[u].min;
  if (r <= p[u].mid) return query(u << 1, l, r);
  if (l > p[u].mid) return query(u << 1 | 1, l, r);
  return min(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
}
inline void conn(int u, int v) {
  todo.push_back(u);
  todo.push_back(v);
  E[u].push_back(v);
  E[v].push_back(u);
}
inline int lca(int u, int v) {
  if (dep[u] > dep[v]) swap(u, v);
  for (int i = 19; i >= 0; i--)
    if (dep[jp[v][i]] >= dep[u] && jp[v][i]) v = jp[v][i];
  if (u == v) return u;
  for (int i = 19; i >= 0; i--)
    if (jp[u][i] != jp[v][i] && jp[u][i] && jp[v][i]) u = jp[u][i], v = jp[v][i];
  return jp[u][0];
}
void dfs(int u) {
  dfn[u] = ++tim;
  h[dep[u]].push_back(u);
  for (int v : G[u])
    if (v != fa[u]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      dfs(v);
    }
}
long long vdfs(int u) {
  if (dep[u] == cur) {
    return a[1];
  }
  int deg = 0;
  long long sum = 0;
  for (int v : E[u])
    if (v != vfa[u]) {
      ++deg;
      vfa[v] = u;
      sum += min<long long>(vdfs(v), query(1, cur - dep[v] + 1, cur - dep[u]));
    }
  sum = min<long long>(sum, a[cur - dep[u] + 1]);
  // cerr << "vdfs " << u << " " << sum << endl;
  return sum;
}
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    tim = ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      h[i].clear(), G[i].clear();
    }
    build(1, 1, n);
    for (int u, v, i = 1; i < n; i++) {
      cin >> u >> v;
      G[u].push_back(v);
      G[v].push_back(u);
    }
    dep[1] = 1, dfs(1);
    for (int i = 1; i <= n; i++) jp[i][0] = fa[i];
    for (int i = 1; i < 20; i++)
      for (int j = 1; j <= n; j++) {
        jp[j][i] = jp[jp[j][i - 1]][i - 1];
      }
    for (int i = 1; i <= n; i++)
      if (h[i].size()) {
        // cerr << "curdep = " << i << endl;
        // for (int x : h[i]) cerr << x << " ";
        // cerr << endl;
        cur = i;
        vector<int> &H = h[i];
        sort(H.begin(), H.end(), cmp);
        vector<int> V;
        for (int i = 0; i + 1 < H.size(); i++) {
          V.push_back(H[i]);
          V.push_back(lca(H[i], H[i + 1]));
        }
        V.push_back(H.back());
        V.push_back(1);
        sort(V.begin(), V.end(), cmp);
        V.erase(unique(V.begin(), V.end()), V.end());
        for (int i = 0; i + 1 < V.size(); i++) {
          conn(lca(V[i], V[i + 1]), V[i + 1]);
        }
        ans += vdfs(1);
        // cerr << ">> ans = " << ans << endl;
        for (int x : todo) {
          E[x].clear();
        }
				todo.clear();
      } else {
        break;
      }
    cout << ans << endl;
  }
}