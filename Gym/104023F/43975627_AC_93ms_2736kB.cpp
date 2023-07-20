#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 309;
const long long INF = 1e16;
int T, n, m, c[N], w[N], fa[N];
long long dis[N][N], mov[N][N], ans[N][N];
vector<int> G[N], ch[N];
vector<tuple<long long, int, int>> edg;

int main() {
#ifdef memset0
  freopen("F.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m;
    rep(i, 1, n) {
      G[i].clear();
      fill(mov[i] + 1, mov[i] + n + 1, INF);
      fill(dis[i] + 1, dis[i] + n + 1, INF);
      fill(ans[i] + 1, ans[i] + n + 1, INF);
    }
    rep(i, 1, n) cin >> c[i];
    rep(i, 1, n) cin >> w[i];
    for (int u, v, i = 1; i <= m; i++) {
      cin >> u >> v;
      G[u].push_back(v);
      G[v].push_back(u);
    }
    rep(i, 1, n) ans[i][i] = 0;
    rep(col, 1, n) {
      vector<int> nod;
      rep(i, 1, n) if (c[i] == col) nod.push_back(i);
      for (int i : nod) dis[i][i] = 0;
      for (int i : nod)
        for (int j : G[i]) {
          dis[i][j] = w[j];
        }
      for (int k : nod)
        for (int i : nod)
          for (int j : nod) {
            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
          }
      for (int i : nod)
        for (int j : nod) {
          dis[i][j] = min(dis[i][j] + w[i], INF);
        }
      for (int i : nod)
        for (int j : nod) {
          ans[i][j] = min(ans[i][j], dis[i][j]);
          for (int k : G[j])
            if (col != c[k]) {
              // fprintf(stderr, "%d[%d] %d[%d] -> %d[%d] :: %lld %d\n", i, c[i], j, c[j], k, c[k], dis[i][j], w[k]);
              mov[i][k] = min(mov[i][k], w[k] + dis[i][j]);
            }
        }
    }

    // rep(i, 1, n) rep(j, 1, n) if (i != j && mov[i][j] != INF) { edg.emplace_back(mov[i][j], i, j); }
    // sort(edg.begin(), edg.end());
    // rep(i, 1, n) fa[i] = i, ch[i] = vector<int>{i};
    // for (const auto &[w, u, v] : edg) {
    //   if (fa[u] != fa[v]) {
    //     if (ch[fa[u]].size() < ch[fa[v]].size()) {
    //       swap(u, v);
    //     }
    //     vector<int> &at = ch[fa[v]];
    //     for (int x : at) {
    //       fa[x] = fa[u];
    //       ch[fa[u]].push_back(x);
    //     }
    //     at.clear();
    //   }
    // }

    // rep(i, 1, n) rep(j, 1, n) if (mov[i][j] != INF) { cerr << i << " -> " << j << " : " << mov[i][j] << endl; }
    rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) mov[i][j] = min(mov[i][j], max(mov[i][k], mov[k][j]));
    rep(i, 1, n) rep(j, 1, n) {
      ans[i][j] = min(ans[i][j], mov[i][j]);
      rep(k, 1, n) if (c[k] == c[j]) {
        // if (mov[i][j] != INF && dis[j][k] != INF) fprintf(stderr, "%d %d %d :: %lld %lld\n", i, j, k, mov[i][j], dis[j][k]);
        ans[i][k] = min(ans[i][k], max(mov[i][j], dis[j][k]));
      }
    }
    rep(i, 1, n) rep(j, 1, n) cout << ans[i][j] << " \n"[j == n];
  }
}