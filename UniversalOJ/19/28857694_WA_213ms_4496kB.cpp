#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
int n, m, s, e, u, v, l, r, dis[N];
short q[N * 20];
bool inq[N], vis[N], tag[N];
vector<int> G[N], F[N];
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin >> n >> m;
  for (int u, v, i = 1; i <= m; i++) {
    cin >> u >> v;
    G[u].push_back(v);
    F[v].push_back(u);
  }
  cin >> s >> e;
  l = r = 1, q[1] = e, vis[e] = 1;
  while (l <= r) {
    u = q[l++];
    for (int i = 0; i < F[u].size(); i++) {
      v = F[u][i];
      if (!vis[v]) {
        vis[v] = 1;
        q[++r] = v;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    tag[i] = true;
    for (int j = 0; j < G[i].size(); j++)
      if (!vis[G[i][j]]) {
        tag[i] = false;
        break;
      };
  }
  memset(dis, 0x3f, sizeof(dis));
  l = r = 1, q[1] = s, inq[s] = 1, dis[s] = 0;
  while (l <= r) {
    u = q[l++], inq[u] = false;
    for (int i = 0; i < G[u].size(); i++) {
      v = G[u][i];
      if (dis[u] + 1 < dis[v] && tag[v]) {
        dis[v] = dis[u] + 1;
        if (!inq[v]) {
          q[++r] = v;
          inq[v] = 1;
        }
      }
    }
  }
  printf("%d\n", dis[e] == dis[0] ? -1 : dis[e]);
}