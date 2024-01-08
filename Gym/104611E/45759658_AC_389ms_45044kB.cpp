#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
const int N = 2e5 + 9, mod = 1e9 + 7;
int n, m, tot, fa[N], dfn[N], idfn[N], dep[N], son[N], top[N], siz[N];
vector<int> G[N];
inline void dec(int &x, int y) {
  x -= y;
  if (x < 0) x += mod;
}
inline void inc(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}
inline pair<int, int> merge(const pair<int, int> &a, const pair<int, int> &b) {
  auto it = make_pair(a.first + b.first, a.second + b.second);
  if (it.first >= mod) it.first -= mod;
  if (it.second >= mod) it.second -= mod;
  return it;
}
struct segtree {
  struct node {
    int l, r, mid;
    int b, k;
  } p[N << 2];
  void build(int u, int l, int r) {
    p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
    if (l == r) {
      return;
    }
    build(u << 1, l, p[u].mid);
    build(u << 1 | 1, p[u].mid + 1, r);
  }
  void modify(int u, int x, int k, int b) {
    inc(p[u].k, k);
    inc(p[u].b, b);
    if (p[u].l == p[u].r) {
      return;
    }
    if (x <= p[u].mid) {
      modify(u << 1, x, k, b);
    } else {
      modify(u << 1 | 1, x, k, b);
    }
  }
  pair<int, int> query(int u, int l, int r) {
    if (p[u].l == l && p[u].r == r) {
      return make_pair(p[u].k, p[u].b);
    }
    if (r <= p[u].mid) return query(u << 1, l, r);
    if (l > p[u].mid) return query(u << 1 | 1, l, r);
    return merge(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
  }
} seg[2];
set<tuple<int, int, int, int>> st;
void dfs(int u) {
  siz[u] = 1;
  for (int v : G[u]) {
    dep[v] = dep[u] + 1;
    dfs(v);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs(int u, int tpt) {
  top[u] = tpt;
  dfn[u] = ++tot;
  idfn[dfn[u]] = u;
  if (siz[u] == 1) return;
  dfs(son[u], tpt);
  for (int v : G[u])
    if (v != son[u]) {
      dfs(v, v);
    }
}
void upsolve(int u, int x, int k) {
  // fprintf(stderr, "upsolve %d %d %d\n", u, x, k);
  x = (x - (long long)k * dep[u]) % mod;
  if (x < 0) x += mod;
  if (k < 0) k += mod;
  seg[dep[u] & 1].modify(1, dfn[u], k, x);
}
int query(int u) {
  long long res = 0;
  pair<int, int> s[2];
  memset(s, 0, sizeof(s));
  for (int t = u; t; t = fa[top[t]]) {
    s[0] = merge(s[0], seg[0].query(1, dfn[top[t]], dfn[t]));
    s[1] = merge(s[1], seg[1].query(1, dfn[top[t]], dfn[t]));
  }
  // fprintf(stderr, "query %d > [%d %d] [%d %d]\n", u, s[0].first, s[0].second, s[1].first, s[1].second);
  res += (long long)dep[u] * s[0].first + s[0].second;
  res -= (long long)dep[u] * s[1].first + s[1].second;
  if (dep[u] & 1) res *= -1;
  return res %= mod, res < 0 ? res + mod : res;
}
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 2; i <= n; i++) {
    cin >> fa[i];
    G[fa[i]].push_back(i);
  }
  dep[1] = 1;
  dfs(1);
  dfs(1, 1);
  for (int x = 0; x < 2; x++) {
    seg[x].build(1, 1, n);
  }
  for (int op, v, x, k, i = 1; i <= m; i++) {
    cin >> op >> v;
    if (op == 1) {
      cin >> x >> k;
      upsolve(v, x, k);
      st.insert(make_tuple(dfn[v], v, x, k));
    } else if (op == 2) {
      cout << query(v) << endl;
    } else {
      decltype(st)::iterator it;
      while (it = st.upper_bound(make_tuple(dfn[v], -1, -1, -1)), it != st.end() && get<0>(*it) < dfn[v] + siz[v]) {
        const auto &[_, v, x, k] = *it;
        upsolve(v, -x, -k);
        st.erase(it);
      }
    }
  }
}