#include <bits/stdc++.h>
#define debug(x) cerr << #x << ": " << x << endl;
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 2e3 + 9;
int T, n, a[N], b[N], fa[N], dep[N];
bool tag[N];
long long ans;
vector<int> son[N], F[N], G[N];
struct circle {
  int x, y, r;
  inline bool contain(const circle &rhs) {
    if (r < rhs.r) return false;
    return rhs.r + sqrtl((long long)(x - rhs.x) * (x - rhs.x) + (long long)(y - rhs.y) * (y - rhs.y)) <= r;
  }
} c[N];
void dfs(int u, vector<int> &cur) {
  int sum = 0, max = 0, cnt = 0;
  for (int i = 1; i <= dep[u]; i++) {
    sum += i & 1 ? a[u] : b[u];
    if (sum > max) max = sum;
  }
  ans += max;
  // fprintf(stderr, "dfs %d dep=%d cur=%d => max=%d\n", u, dep[u], (int)cur.size(), max);
  // for (int x : cur) cerr << x << " ";
  // cerr << endl;
  sum = cnt = 0;
  vector<int> pos;
  for (int i = 0; i < cur.size(); i++) {
    if (sum == max) pos.push_back(i);
    if (tag[cur[i]]) {
      ++cnt;
      sum += cnt & 1 ? a[u] : b[u];
    }
  }
  // debug(cnt);
  // debug(sum);
  // debug(max);
  if (sum == max) pos.push_back(cur.size());
  assert(pos.size());
  for (int i = pos.size() - 1; i >= 0; i--) {
    if (!i || !pos[i] || u < cur[pos[i] - 1]) {
      cur.insert(cur.begin() + pos[i], u);
      break;
    }
  }
  // for (int x : cur) cerr << x << " ";
  // cerr << endl;
  tag[u] = true;
  for (int v : son[u]) {
    dep[v] = dep[u] + 1;
    dfs(v, cur);
  }
  tag[u] = false;
}
int main() {
#ifdef memset0
  freopen("B.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    fill(fa + 1, fa + n + 1, 0);
    rep(i, 1, n) {
      cin >> c[i].x >> c[i].y >> c[i].r >> a[i] >> b[i];
      son[i].clear();
      F[i].clear(), G[i].clear();
    }
    rep(i, 1, n) rep(j, 1, n) if (i != j && c[i].contain(c[j])) {
      G[i].push_back(j);
      F[j].push_back(i);
    }
    rep(i, 1, n) if (F[i].size()) {
      int mi = -1;
      size_t mv = n + 1;
      for (int j : F[i])
        if (G[j].size() < mv) {
          mv = G[j].size();
          mi = j;
        }
      fa[i] = mi;
      // cerr << mi << " -> " << i << endl;
      son[mi].push_back(i);
    }

    ans = 0;
    vector<vector<int>> vec;
    priority_queue<pair<int, int>> q;
    for (int i = 1; i <= n; i++)
      if (!fa[i]) {
        vector<int> cur;
        dep[i] = 0;
        dfs(i, cur);
        q.push(make_pair(-cur.back(), vec.size()));
        vec.push_back(cur);
      }

    vector<int> sol;
    while (q.size()) {
      auto it = q.top();
      q.pop();
      sol.push_back(-it.first);
      int i = it.second;
      vec[i].pop_back();
      if (vec[i].size()) {
        q.push(make_pair(-vec[i].back(), i));
      }
    }

    cout << ans << endl;
    assert(sol.size() == n);
    for (int i = 0; i < n; i++) cout << sol[i] << " \n"[i + 1 == n];
  }
}