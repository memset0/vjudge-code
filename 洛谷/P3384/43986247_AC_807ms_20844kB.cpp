#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int n, m, rt, mod, a[N], b[N];
int tot, fa[N], dep[N], siz[N], son[N], top[N], id[N];
vector<int> G[N];
inline int add(int x, int y) { return x += y, (x >= mod ? x - mod : x); }
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
  id[u] = ++tot, top[u] = tpt;
  if (siz[u] == 1) return;
  dfs(son[u], tpt);
  for (int v : G[u])
    if (v != fa[u] && v != son[u]) dfs(v, v);
}
struct segment {
  int l, r, mid, len;
  int sum, tag;
} p[N << 2];
inline void pushup(int u, int z) {
  p[u].tag = add(p[u].tag, z);
  p[u].sum = (p[u].sum + (long long)p[u].len * z) % mod;
}
inline void pushdown(int u) {
  if (p[u].tag) {
    pushup(u << 1, p[u].tag);
    pushup(u << 1 | 1, p[u].tag);
    p[u].tag = 0;
  }
}
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1, p[u].len = r - l + 1;
  if (l == r) {
    p[u].sum = b[l] % mod;
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
  p[u].sum = add(p[u << 1].sum, p[u << 1 | 1].sum);
}
void modify(int u, int l, int r, int w) {
  if (p[u].l == l && p[u].r == r) return pushup(u, w);
  pushdown(u);
  if (r <= p[u].mid) {
    modify(u << 1, l, r, w);
  } else if (l > p[u].mid) {
    modify(u << 1 | 1, l, r, w);
  } else {
    modify(u << 1, l, p[u].mid, w);
    modify(u << 1 | 1, p[u].mid + 1, r, w);
  }
  p[u].sum = add(p[u << 1].sum, p[u << 1 | 1].sum);
}
int query(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) return p[u].sum;
  pushdown(u);
  if (r <= p[u].mid) return query(u << 1, l, r);
  if (l > p[u].mid) return query(u << 1 | 1, l, r);
  return add(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m >> rt >> mod;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int u, v, i = 1; i < n; i++) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dep[rt] = 1, dfs(rt), dfs(rt, rt);
  for (int i = 1; i <= n; i++) b[id[i]] = a[i] % mod;
  build(1, 1, n);
  for (int op, x, y, z, i = 1; i <= m; i++) {
    cin >> op >> x;
    if (op == 1) {
      cin >> y >> z, z %= mod;
      while (top[x] != top[y]) {
        if (dep[top[x]] > dep[top[y]]) swap(x, y);
        modify(1, id[top[y]], id[y], z);
        y = fa[top[y]];
      }
      if (dep[x] > dep[y]) swap(x, y);
      modify(1, id[x], id[y], z);
    } else if (op == 2) {
      cin >> y;
      int ans = 0;
      while (top[x] != top[y]) {
        if (dep[top[x]] > dep[top[y]]) swap(x, y);
        ans = add(ans, query(1, id[top[y]], id[y]));
        y = fa[top[y]];
      }
      if (dep[x] > dep[y]) swap(x, y);
      ans = add(ans, query(1, id[x], id[y]));
      cout << ans << endl;
    } else if (op == 3) {
      cin >> z;
      modify(1, id[x], id[x] + siz[x] - 1, z % mod);
    } else {
      cout << query(1, id[x], id[x] + siz[x] - 1) << endl;
    }
    // for (int i = 1; i <= n; i++) cerr << query(1, i, i) << " \n"[i == n];
  }
}