#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 2e5 + 10;
int n, m, p, u, k, v, w, l, r, t, ans, tim, flag;
int q[N], id[N], f[N][51], ind[N], ord[N], dis[N], disn[N];
bool inq[N];
struct graph {
  int tot, hed[N], nxt[M], to[M], val[M];
  inline void add_edge(int u, int v, int w) {
    nxt[tot] = hed[u], to[tot] = v, val[tot] = w;
    hed[u] = tot++;
  }
} h, g, z;
inline bool cmp(int a, int b) {
  if (dis[a] != dis[b])
    return dis[a] < dis[b];
  return ord[a] < ord[b];
}
void dij(int s, int *dis, graph &g) {
  priority_queue<pair<int, int>> q;
  dis[s] = 0, q.push(make_pair(0, s));
  while (q.size()) {
    auto it = q.top();
    q.pop();
    if (it.first + dis[it.second])
      continue;
    int u = it.second;
    // printf(">> %d\n", u);
    for (int i = g.hed[u]; i; i = g.nxt[i]) {
      int v = g.to[i], w = g.val[i];
      // printf("%d -> %d : %d\n", u, v, w);
      if (!~dis[v] || dis[u] + w < dis[v]) {
        dis[v] = dis[u] + w;
        q.push(make_pair(-dis[v], v));
      }
    }
  }
  // for (int i = 1; i <= n; i++)
  //   printf("%d%c", dis[i], " \n"[i == n]);
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    z.tot = h.tot = g.tot = 2, ans = tim = flag = 0;
    memset(h.hed, 0, sizeof(h.hed));
    memset(g.hed, 0, sizeof(g.hed));
    memset(z.hed, 0, sizeof(z.hed));
    memset(f, 0, sizeof(f));
    memset(ind, 0, sizeof(ind));
    memset(dis, -1, sizeof(dis));
    memset(disn, -1, sizeof(disn));
    cin >> n >> m >> k >> p;
    for (int i = 1; i <= m; i++) {
      cin >> u >> v >> w;
      g.add_edge(u, v, w);
      h.add_edge(v, u, w);
      if (!w) {
        z.add_edge(u, v, 0);
        ind[v]++;
      }
    }
    dij(1, dis, g);
    dij(n, disn, h);
    l = 1, r = 0;
    for (int i = 1; i <= n; i++)
      if (!ind[i])
        q[++r] = i;
    while (l <= r) {
      u = q[l++], ord[u] = ++tim;
      for (int i = z.hed[u]; i; i = z.nxt[i]) {
        v = z.to[i];
        if (ind[v]) {
          ind[v]--;
          if (!ind[v])
            q[++r] = v;
        }
      }
    }
    for (int i = 1; i <= n; i++)
      if (~dis[i] && ~disn[i] && ind[i] && dis[i] + disn[i] <= dis[n] + k) {
        printf("-1\n");
        flag = 1;
        break;
      }
    if (flag)
      continue;
    for (int i = 1; i <= n; i++)
      id[i] = i;
    sort(id + 1, id + n + 1, cmp);
    f[1][0] = 1;
    for (int q = 0; q <= k; q++)
      for (int i = 1; i <= n; i++) {
        u = id[i];
        if (!~dis[u])
          continue;
        for (int j = h.hed[u]; j; j = h.nxt[j]) {
          v = h.to[j];
          if (!~dis[v])
            continue;
          w = dis[v] + h.val[j] - dis[u];
          (f[u][q] += q >= w ? f[v][q - w] : 0) %= p;
        }
      }
    for (int i = 0; i <= k; i++)
      (ans += f[n][i]) %= p;
    printf("%d\n", ans);
  }
}
