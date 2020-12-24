// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 2e5 + 10;
int n, m, p, u, k, v, w, l, r, t, ans, tim, flag;
int q[N], id[N], f[N][51], ind[N], ord[N];
long long dis[N], disn[N];
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
    memset(dis, -1, sizeof(dis));
    memset(ind, 0, sizeof(ind));
    memset(disn, -1, sizeof(disn));
    memset(f, 0, sizeof(f));
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
    l = r = 1, q[1] = 1, dis[1] = 0, inq[1] = 1;
    while (l <= r) {
      u = q[(l++) % N], inq[u] = 0;
      for (int i = g.hed[u]; i; i = g.nxt[i]) {
        v = g.to[i];
        if (!~dis[v] || dis[v] > dis[u] + g.val[i]) {
          dis[v] = dis[u] + g.val[i];
          if (!inq[v]) {
            inq[v] = 1;
            q[(++r) % N] = v;
          }
        }
      }
    }
    l = r = 1, q[1] = n, disn[n] = 0, inq[n] = 1;
    while (l <= r) {
      u = q[(l++) % N], inq[u] = 0;
      for (int i = g.hed[u]; i; i = g.nxt[i]) {
        v = g.to[i];
        if (!~disn[v] || disn[v] > disn[u] + g.val[i]) {
          disn[v] = disn[u] + g.val[i];
          if (!inq[v]) {
            inq[v] = 1;
            q[(++r) % N] = v;
          }
        }
      }
    }
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
      if (ind[i] && dis[i] + disn[i] <= dis[n] + k) {
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
