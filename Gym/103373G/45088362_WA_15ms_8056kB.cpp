#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
int n, root, total, s[N], fa[N], siz[N], mxp[N];
bool vis[N];
long long ans;
vector<int> tmp;
vector<pair<int, int>> G[N];
void add(int k, int x) {
  for (; k < N; k += k & -k) s[k] += x;
}
int ask(int k) {
  int r = 0;
  for (; k; k -= k & -k) r += s[k];
  return r;
}
void getroot(int u) {
  siz[u] = 1, mxp[u] = 0;
  for (auto [v, w] : G[u])
    if (!vis[v] && v != fa[u]) {
      fa[v] = u;
      getroot(v);
      siz[u] += siz[v];
      mxp[u] = max(mxp[u], siz[v]);
    }
  mxp[u] = max(mxp[u], total - siz[u]);
  if (!root || mxp[u] < mxp[root]) root = u;
}
int collect(int u, int x, bool fl) {
  int cnt = 1;
  for (auto [v, w] : G[u])
    if (!vis[v] && v != fa[u]) {
      if (fl == 0 && w >= x) continue;
      if (fl == 1 && w <= x) continue;
      cnt += collect(v, w, fl);
    }
  return cnt;
}
void solve(int u) {
  // cerr << ">>> solve " << u << endl;
  vis[u] = true;
  vector<tuple<int, int, int>> rol;
  for (auto [v, w] : G[u])
    if (!vis[v]) {
      fa[v] = 0;
      int x = collect(v, w, 0);
      int y = collect(v, w, 1);
      ans += x + y;
      add(w, x);
      rol.emplace_back(w, x, y);
      // fprintf(stderr, "%d %d %d : %d %d : %d\n", u, v, w, x, y, ask(w - 1));
    }
  for (auto [w, x, y] : rol) {
    ans += (long long)ask(w - 1) * y;
  }
  for (auto [w, x, y] : rol) {
    add(w, -x);
  }
  for (auto [v, w] : G[u])
    if (!vis[v]) {
      root = 0, total = siz[v];
      getroot(v);
      solve(root);
    }
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int u, v, w, i = 1; i < n; i++) {
    cin >> u >> v >> w;
    tmp.push_back(w);
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  sort(tmp.begin(), tmp.end());
  tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
  for (int u = 1; u <= n; u++)
    for (auto &[v, w] : G[u]) {
      w = lower_bound(tmp.begin(), tmp.end(), w) - tmp.begin() + 1;
      // if (u < v) cerr << "edge " << u << " " << v << " " << w << endl;
    }
  root = 0, total = n;
  getroot(1);
  solve(root);
  cout << ans << endl;
}