#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
enum Way { U, D, L, R };
int n;
long long tim, dis[N];
vector<int> tx, ty, vx[N], vy[N];
vector<pair<int, int>> G[N];
priority_queue<pair<long long, int>> q;
inline int iabs(int x) { return x < 0 ? -x : x; }
inline char getname(Way w) {
  if (w == U) return 'U';
  if (w == D) return 'D';
  if (w == L) return 'L';
  if (w == R) return 'R';
  return ' ';
}
struct robot {
  int x, y, id, xt, yt;
  Way w;
  inline int dis(const robot &rhs) const { return iabs(rhs.x - x) + iabs(rhs.y - y); }
  inline pair<long long, long long> move(long long d) const {
    if (w == U) return {(long long)x, y + d};
    if (w == D) return {(long long)x, y - d};
    if (w == L) return {x - d, (long long)y};
    if (w == R) return {x + d, (long long)y};
    return {0, 0};
  }
} a[N];
void solve(vector<int> &v, bool fl) {
  if (v.empty()) return;
  sort(v.begin(), v.end(), [&](int i, int j) { return a[i].x == a[j].x ? a[i].y < a[j].y : a[i].x < a[j].x; });
  // for (int i = 0; i < v.size(); i++) cout << a[v[i]].x << " " << a[v[i]].y << " " << v[i] << endl;
  for (int i = 0; i < v.size(); i++) {
    if ((!fl && a[v[i]].w == U) || (fl && a[v[i]].w == R)) {
      for (int j = i + 1; j < v.size(); j++)
        if (a[v[j]].w != a[v[i]].w) {
          // fprintf(stderr, "%c %d -> %d : %d\n", getname(a[v[i]].w), v[i], v[j], a[v[i]].dis(a[v[j]]));
          G[v[i]].emplace_back(v[j], a[v[i]].dis(a[v[j]]));
        } else {
          G[v[i]].emplace_back(v[j], a[v[i]].dis(a[v[j]]));
          break;
        }
    }
    if ((!fl && a[v[i]].w == D) || (fl && a[v[i]].w == L)) {
      for (int j = i - 1; j >= 0; j--)
        if (a[v[j]].w != a[v[i]].w) {
          // fprintf(stderr, "%c %d -> %d : %d\n", getname(a[v[i]].w), v[i], v[j], a[v[i]].dis(a[v[j]]));
          G[v[i]].emplace_back(v[j], a[v[i]].dis(a[v[j]]));
        } else {
          G[v[i]].emplace_back(v[j], a[v[i]].dis(a[v[j]]));
          break;
        }
    }
  }
}
int main() {
#ifdef memset0
  freopen("I.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> tim;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> a[i].x >> a[i].y >> s;
    tx.push_back(a[i].x);
    ty.push_back(a[i].y);
    if (s[0] == 'U') a[i].w = U;
    if (s[0] == 'D') a[i].w = D;
    if (s[0] == 'L') a[i].w = L;
    if (s[0] == 'R') a[i].w = R;
  }
  sort(tx.begin(), tx.end()), tx.erase(unique(tx.begin(), tx.end()), tx.end());
  sort(ty.begin(), ty.end()), ty.erase(unique(ty.begin(), ty.end()), ty.end());
  for (int i = 1; i <= n; i++) {
    a[i].xt = lower_bound(tx.begin(), tx.end(), a[i].x) - tx.begin() + 1;
    a[i].yt = lower_bound(ty.begin(), ty.end(), a[i].y) - ty.begin() + 1;
    vx[a[i].xt].push_back(i);
    vy[a[i].yt].push_back(i);
  }
  for (int i = 1; i <= tx.size(); i++) solve(vx[i], 0);
  for (int i = 1; i <= ty.size(); i++) solve(vy[i], 1);
  fill(dis + 1, dis + n + 1, tim + 1);
  dis[1] = 0;
  q.push({0, 1});
  while (q.size()) {
    auto [d, u] = q.top();
    q.pop();
    if (dis[u] + d) continue;
    for (const auto &[v, w] : G[u]) {
      if (dis[u] + w < dis[v]) {
        dis[v] = dis[u] + w;
        q.push({-dis[v], v});
      }
    }
  }
  // for (int i = 1; i <= n; i++) cout << dis[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) {
    if (dis[i] < tim) {
      auto it = a[i].move(tim - dis[i]);
      cout << it.first << " " << it.second << endl;
    } else {
      cout << a[i].x << " " << a[i].y << endl;
    }
  }
}