#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 2e5 + 9;
int n, a[N];
int rt, all, siz[N], mxp[N], vis[N];
vector<pair<int, int>> G[N];
long long ans[N];
struct segment {
  int k;
  long long b;
  inline long long operator()(int x) const { return (long long)k * x + b; }
};
int root, tot = 0;
struct node {
  int ch[2];
  segment s;
} p[N * 22];
inline int newnode() {
  ++tot;
  p[tot].ch[0] = p[tot].ch[1] = 0;
  return tot;
}
void insert(int &u, segment s, int l, int r) {
  if (!u) {
    u = newnode();
    p[u].s = s;
    return;
  }
  if (s(l) <= p[u].s(l) && s(r) <= p[u].s(r)) {
    p[u].s = s;
    return;
  }
  if (s(l) >= p[u].s(l) && s(r) >= p[u].s(r)) return;
  int mid = (l + r) >> 1;
  if (s(mid) < p[u].s(mid)) swap(s, p[u].s);
  if (l == r) return;
  if (s(l) < p[u].s(l)) {
    insert(p[u].ch[0], s, l, mid);
  } else {
    insert(p[u].ch[1], s, mid + 1, r);
  }
}
long long query(int u, int x, int l, int r) {
  if (!u) return LLONG_MAX;
  if (l == r) return p[u].s(x);
  int mid = (l + r) >> 1;
  if (x <= mid) {
    return min(p[u].s(x), query(p[u].ch[0], x, l, mid));
  } else {
    return min(p[u].s(x), query(p[u].ch[1], x, mid + 1, r));
  }
}
void getroot(int u, int fa = -1) {
  siz[u] = 1;
  mxp[u] = 0;
  for (const auto &[v, w] : G[u])
    if (!vis[v] && v != fa) {
      getroot(v, u);
      siz[u] += siz[v];
      mxp[u] = max(mxp[u], siz[v]);
    }
  mxp[u] = max(mxp[u], all - siz[u]);
  if (!rt || mxp[u] < mxp[rt]) rt = u;
}
vector<pair<int, long long>> cur;
void getpath(int u, long long sum, int fa = -1) {
  siz[u] = 1;
  cur.emplace_back(u, sum);
  for (const auto &[v, w] : G[u])
    if (!vis[v] && v != fa) {
      getpath(v, sum + w, u);
      siz[u] += siz[v];
    }
}
void solve(int u) {
  vis[u] = 1;
  cur.clear();
  cur.emplace_back(u, 0ll);
  for (const auto &[v, w] : G[u])
    if (!vis[v]) {
      getpath(v, w);
    }
  root = tot = 0;
  // cerr << "::: solve " << u << endl;
  for (const auto &[u, s] : cur) {
    // cerr << "> " << u << " " << s << endl;
    insert(root, segment{a[u], s}, 1, 1e6);
  }
  for (const auto &[u, s] : cur) {
    ans[u] = min(ans[u], query(root, a[u], 1, 1e6) + s);
  }
  for (const auto &[v, w] : G[u])
    if (!vis[v]) {
      all = siz[v], rt = 0, getroot(v), solve(rt);
    }
}
int main() {
#ifdef memset0
  freopen("K.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ans[i] = (long long)a[i] * a[i];
  }
  for (int u, v, w, i = 1; i < n; i++) {
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  all = n, rt = 0, getroot(1), solve(rt);
  long long sum = 0;
  for (int i = 1; i <= n; i++) {
    // cerr << ans[i] << " \n"[i == n];
    sum += ans[i];
  }
  cout << sum << endl;
}