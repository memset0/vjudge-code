#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 1e6 + 9;
int T, tot, n, q, x, y, a[N], fa[N], dfn[N], idfn[N], siz[N], mn[N << 2], mx[N << 2], tag[N << 2];
string op;
vector<int> son[N];
void dfs(int u) {
  dfn[u] = ++tot;
  idfn[dfn[u]] = u;
  siz[u] = 1;
  for (int v : son[u]) {
    dfs(v);
    siz[u] += siz[v];
  }
}
inline void pushup(int u, int x) { mn[u] += x, mx[u] += x, tag[u] += x; }
inline void pushdown(int u) {
  if (tag[u]) {
    pushup(u << 1, tag[u]);
    pushup(u << 1 | 1, tag[u]);
    tag[u] = 0;
  }
}
inline void maintain(int u) {
  mx[u] = max(mx[u << 1], mx[u << 1 | 1]);
  mn[u] = min(mn[u << 1], mn[u << 1 | 1]);
}
void build(int u, int l, int r) {
  tag[u] = 0;
  if (l == r) {
    mx[u] = mn[u] = a[idfn[l]];
    return;
  }
  int mid = (l + r) >> 1;
  build(u << 1, l, mid);
  build(u << 1 | 1, mid + 1, r);
  maintain(u);
}
void modify(int u, int ql, int qr, int x, int l, int r) {
  if (ql == l && qr == r) {
    pushup(u, x);
    return;
  }
  pushdown(u);
  int mid = (l + r) >> 1;
  if (qr <= mid) {
    modify(u << 1, ql, qr, x, l, mid);
  } else if (ql > mid) {
    modify(u << 1 | 1, ql, qr, x, mid + 1, r);
  } else {
    modify(u << 1, ql, mid, x, l, mid);
    modify(u << 1 | 1, mid + 1, qr, x, mid + 1, r);
  }
  maintain(u);
}
constexpr pair<int, int> merge(const pair<int, int> &a, const pair<int, int> &b) { return {min(a.first, b.first), max(a.second, b.second)}; }
pair<int, int> query(int u, int ql, int qr, int l, int r) {
  if (ql == l && qr == r) return {mn[u], mx[u]};
  pushdown(u);
  int mid = (l + r) >> 1;
  if (qr <= mid) return query(u << 1, ql, qr, l, mid);
  if (ql > mid) return query(u << 1 | 1, ql, qr, mid + 1, r);
  return merge(query(u << 1, ql, mid, l, mid), query(u << 1 | 1, mid + 1, qr, mid + 1, r));
}
int main() {
#ifdef memset0
  freopen("I.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n, tot = 0;
    rep(i, 1, n) { son[i].clear(); }
    rep(i, 2, n) {
      cin >> fa[i];
      son[fa[i]].push_back(i);
    }
    rep(i, 1, n) { cin >> a[i]; }
    dfs(1), assert(n == tot);
    build(1, 1, n);
    cin >> q;
    rep(i, 1, q) {
      cin >> op >> x;
      if (op == "R") {
        cin >> y;
        modify(1, dfn[x], dfn[x] + siz[x] - 1, y, 1, n);
      } else {
        auto it = query(1, dfn[x], dfn[x] + siz[x] - 1, 1, n);
        // cerr << "! " << it.first << " " << it.second << endl;
        cout << it.second - it.first << '\n';
      }
    }
  }
}