#include "bits/stdc++.h"
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 309, M = 5e4 + 9;
int T, n, m, x, pre[M], id[N][N];
bool found, vis[M];
long long sum, dis[M];
set<int> ban[M];
vector<pair<int, int>> anst;
vector<int> ans;
pair<int, int> at[M];
vector<pair<int, int>> G[M];
priority_queue<pair<long long, int>> q;

struct graph {
  int beg[M], nxt[M * 6], to[M * 6], tot;
  bool used[M * 6];
  int cur[M];
  void init(int m) {
    memset(beg, 0, (m + 5) * sizeof(int));
    memset(cur, 0, (m + 5) * sizeof(int));
    tot = 1;
  }
  void aa(int u, int v) {
    nxt[++tot] = beg[u];
    cur[u] = beg[u] = tot;
    used[tot] = false;
    to[tot] = v;
  }
  void ae(int u, int v) {
    // cerr<<"AE "<<u<<" "<<v<<endl;
    aa(u, v), aa(v, u);
  }
} g;

vector<int> dij() {
  memset(vis, 0, m + 5);
  memset(pre, 0, (m + 5) << 2);
  memset(dis, 63, (m + 5) << 3);
  dis[1] = 0;
  q.push(make_pair(0, 1));
  while (q.size()) {
    int u = q.top().second;
    q.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto it : G[u]) {
      if (dis[u] + it.second < dis[it.first]) {
        dis[it.first] = dis[u] + it.second;
        pre[it.first] = u;
        q.push(make_pair(-dis[it.first], it.first));
      }
    }
  }
  vector<int> p = {m};
  int u = m;
  while (u != 1) {
    u = pre[u];
    p.push_back(u);
  }
  return p;
}

void dfs1(int x, int fa) {
  for (int &i = g.cur[x]; i; i = g.nxt[i]) {
    if (g.used[i]) continue;
    g.used[i] = g.used[i ^ 1] = true;
    int y = g.to[i];
    dfs1(y, x);
  }
  if (fa >= 0) anst.emplace_back(x, fa);
}

int main() {
#ifdef memset0
  freopen("J.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n, m = sum = 0;
    rep(i, 1, n) rep(j, 1, i) {
      at[++m] = make_pair(i, j);
      id[i][j] = m;
      G[m].clear(), ban[m].clear();
    }
    rep(i, 1, n - 1) rep(j, 1, i) {
      cin >> x, sum += x;
      G[id[i][j]].emplace_back(id[i + 1][j], x);
      G[id[i + 1][j]].emplace_back(id[i][j], x);
    }
    rep(i, 1, n - 1) rep(j, 1, i) {
      cin >> x, sum += x;
      G[id[i][j]].emplace_back(id[i + 1][j + 1], x);
      G[id[i + 1][j + 1]].emplace_back(id[i][j], x);
    }
    rep(i, 1, n - 1) rep(j, 1, i) {
      cin >> x, sum += x;
      G[id[i + 1][j]].emplace_back(id[i + 1][j + 1], x);
      G[id[i + 1][j + 1]].emplace_back(id[i + 1][j], x);
    }

    vector<int> path = dij();
    rep(i, 1, (int)path.size() - 1) {
      ban[path[i - 1]].insert(path[i]);
      ban[path[i]].insert(path[i - 1]);
    }
    g.init(m);
    rep(u, 1, m) {
      for (const auto &[v, w] : G[u])
        if (!ban[u].count(v) && u < v) {
          g.ae(u, v);
        }
    }

    anst.clear();
    dfs1(m, -1);

    ans.clear();
    ans.push_back(anst.front().first);
    for (int i = 0; i < anst.size(); i++) {
      ans.push_back(anst[i].second);
    }

    cout << (sum - dis[m]) << endl;
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
      cout << at[ans[i]].first << ' ' << at[ans[i]].second;
      if (i + 1 == ans.size()) {
        cout << endl;
      } else {
        cout << ' ';
      }
    }
  }
}