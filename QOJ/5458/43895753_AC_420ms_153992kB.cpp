#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 9;
int n, m, q;
// long long ans[N];
struct node {
  int x, y;
  node() {}
  explicit node(int _x, int _y) { x = _x, y = _y; }
  friend bool operator<(const node &u, const node &v) { return u.x < v.x || (u.x == v.x && u.y > v.y); }
};
vector<node> con[N];
vector<pair<int, int>> G[N];
// vector<tuple<int, int, int>> qry[N];
inline vector<node> merge(const vector<node> &a, const vector<node> &b) {
  if (!a.size()) return b;
  if (!b.size()) return a;
  node u;
  vector<node> res;
  for (int i = 0, j = 0; i < a.size() || j < b.size();) {
    if (j == b.size()) {
      u = a[i++];
    } else if (i == a.size()) {
      u = b[j++];
    } else if (a[i] < b[j]) {
      u = a[i++];
    } else {
      u = b[j++];
    }
    while (res.size() > 1 && 1ll * (res[res.size() - 2].x - res[res.size() - 1].x) * (res[res.size() - 1].y - u.y) <= 1ll * (res[res.size() - 2].y - res[res.size() - 1].y) * (res[res.size() - 1].x - u.x)) {
      res.pop_back();
    }
    res.push_back(u);
  }
  return res;
}
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int u, v, w, i = 1; i <= m; i++) {
    cin >> u >> v >> w;
    G[v].emplace_back(u, w);
  }
  con[1].push_back(node(0, 0));
  for (int i = 2; i <= n; i++) {
    for (const auto &[j, w] : G[i]) {
      vector<node> t = con[j];
      if (w) {
        for (auto &x : t) x.y++;
      } else {
        for (auto &x : t) x.x++;
      }
      con[i] = merge(con[i], t);
    }
    // fprintf(stderr, "con[%d] = ", i);
    // for (auto &it : con[i]) cerr << it.x << "," << it.y << " ";
    // cerr << endl;
  }
  cin >> q;
  for (int a, b, x, i = 1; i <= q; i++) {
    cin >> a >> b >> x;
    long long ans = LONG_LONG_MAX;
    for (const auto &it : con[x]) {
      ans = min(ans, (long long)a * it.x + (long long)b * it.y);
    }
    cout << ans << endl;
  }
}