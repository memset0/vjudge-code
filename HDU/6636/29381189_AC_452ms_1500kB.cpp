#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define lowbit(x) (x & (-x))
#define MP make_pair
#define fi first
#define se second
#define ls(x) (x << 1)
#define rs(x) ((x << 1) | 1)
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define down(i, r, l) for (int i = r; i >= l; i--)
#define fore(i, x) for (int i = head[x]; i; i = e[i].next)
#define SZ(v) (int)v.size()

typedef long long ll;
typedef pair<int, int> pr;
const int maxn = 1e6 + 10;
const int inf = 1e9;

int n, m;
int weight[maxn], belong[maxn];

struct node {
  vector<int> c, k, lim;

  node() {}
  node(int n) { c.assign(n, 0), k.assign(n, 0), lim.assign(n, 0); }

  bool check(const vector<int> &used) {
    rep(i, 0, SZ(lim) - 1) lim[i] = c[i] - k[i];
    rep(i, 0, SZ(used) - 1) {
      if (used[i])
        lim[belong[i]]--;
    }
    for (auto x : lim)
      if (x < 0)
        return 0;
    return 1;
  }
};
struct graph {
  vector<vector<pr>> e;
  int n;

  graph() {}
  graph(int _n) { n = _n, e.assign(n, vector<pr>(0)); }

  void adde(int x, int y, int id) {
    e[x].PB({y, id});
    e[y].PB({x, id});
  }
  bool check(const vector<int> &used) {
    vector<int> vis(n);
    function<void(int)> dfs = [&](int x) {
      vis[x] = 1;
      for (auto &y : e[x]) {
        if (!used[y.se] && !vis[y.fi])
          dfs(y.fi);
      }
    };
    dfs(1);
    for (auto x : vis)
      if (!x)
        return 0;
    return 1;
  }
};

template <class DT, class M1, class M2>
vector<DT> matroid_intersection(int n, DT w[], M1 m1, M2 m2) {
  vector<int> used(n);

  auto find_path = [&]() {
    int S = n, T = n + 1;
    vector<vector<int>> e(n + 2);

    rep(i, 0, n - 1) if (used[i]) {
      rep(j, 0, n - 1) if (!used[j]) {
        used[i] = 0, used[j] = 1;
        if (m1.check(used))
          e[i].PB(j);
        if (m2.check(used))
          e[j].PB(i);
        used[i] = 1, used[j] = 0;
      }
    }
    rep(i, 0, n - 1) if (!used[i]) {
      used[i] = 1;
      if (m1.check(used))
        e[S].PB(i);
      if (m2.check(used))
        e[i].PB(T);
      used[i] = 0;
    }
    vector<DT> dis(n + 2, -inf);
    vector<int> pre(n + 2, -1);
    vector<int> inq(n + 2, 0);
    queue<int> q;
    q.push(S), dis[S] = 0;
    while (q.size()) {
      int x = q.front();
      q.pop();
      inq[x] = 0;
      DT cost = 0;
      if (x < n)
        cost = used[x] ? -w[x] : w[x];
      for (auto y : e[x]) {
        if (dis[y] < dis[x] + cost) {
          dis[y] = dis[x] + cost;
          pre[y] = x;
          if (!inq[y]) {
            q.push(y);
            inq[y] = 1;
          }
        }
      }
    }
    if (pre[T] == -1)
      return false;
    for (int x = pre[T]; x != S; x = pre[x])
      used[x] ^= 1;
    return true;
  };

  while (find_path())
    ;
  return used;
}

bool check(const node &dt) {
  rep(i, 0, m - 1) if (dt.lim[i] != 0) return 0;
  return 1;
}
int main() {
  int cases;
  scanf("%d", &cases);
  while (cases--) {
    scanf("%d %d", &n, &m);
    graph g(n + 1);
    node dt(m);
    int sumw = 0, tot = 0;
    rep(i, 0, m - 1) {
      int c, l, r, w, k;
      scanf("%d%d", &c, &k);
      rep(j, 1, c) {
        scanf("%d %d %d", &l, &r, &w);
        g.adde(l - 1, r, tot);
        belong[tot] = i;
        weight[tot++] = w;
      }
      dt.c[i] = c, dt.k[i] = k;
    }

    vector<int> res =
        matroid_intersection<int, graph, node>(tot, weight, g, dt);
    rep(i, 0, tot - 1) if (!res[i]) sumw += weight[i];
    if (g.check(res) && dt.check(res) && check(dt))
      printf("%d\n", sumw);
    else
      puts("-1");
  }
}