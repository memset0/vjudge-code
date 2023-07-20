#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 9;
int T, n, e, m, k, l, r, cnt, q[N], h[N], p[10], dis[N], arr[N];
bool t[N], dp[N][64], ans[2][64];
vector<int> G[N], id[N];
void bfs() {
  l = r = q[1] = dis[1] = 1;
  dp[1][0] = true;
  while (l <= r) {
    int u = q[l++];
    if (id[u].size()) {
      for (int i : id[u]) {
        // cerr << u << " has " << i << endl;
        for (int x = 0; x < 64; x++)
          if (dp[u][x]) {
            // fprintf(stderr, "dp[%d][%d] -> dp[%d][%d]\n", u, x, u, x | (1 << i));
            dp[u][x | (1 << i)] = true;
          }
      }
    }
    for (int v : G[u]) {
      if (!dis[v]) {
        dis[v] = dis[u] + 1;
        q[++r] = v;
      }
      if (dis[v] == dis[u] + 1) {
        for (int x = 0; x < 64; x++)
          if (dp[u][x]) {
            // fprintf(stderr, "dp[%d][%d] -> dp[%d][%d]\n", u, x, v, x);
            dp[v][x] = true;
          }
      }
    }
  }
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cnt = 0;
    cin >> n >> e;
    for (int i = 1; i <= n; i++) {
      dis[i] = arr[i] = 0;
      G[i].clear();
      id[i].clear();
      memset(dp[i], 0, sizeof(dp[i]));
    }
    for (int u, v, i = 1; i <= e; i++) {
      cin >> u >> v;
      G[u].push_back(v);
      G[v].push_back(u);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
      cin >> h[i];
      t[i] = true;
    }
    cin >> k;
    for (int i = 1; i <= k; i++) {
      cin >> p[i];
      t[p[i]] = false;
    }
    for (int i = 1; i <= m; i++) {
      if (t[i]) {
        arr[h[i]]++;
        // has car
      } else {
        id[h[i]].push_back(cnt++);
        // don't has car
      }
    }
    bfs();
    // for (int i = 1; i <= n; i++) cerr << dis[i] << " \n"[i == n];
    // for (int i = 1; i <= n; i++) {
    //   for (int j = 0; j < 63; j++) cerr << dp[i][j];
    //   cerr << endl;
    // }
    memset(ans, 0, sizeof(ans));
    ans[0][0] = true;
    for (int u = 1; u <= n; u++)
      while (arr[u]--) {
        for (int x = 0; x < 64; x++)
          if (dp[u][x]) {
            // fprintf(stderr, "dp[%d][%d] = true\n", u, x);
            for (int y = 0; y < 64; y++)
              if (ans[0][y]) {
                ans[1][x | y] = true;
              }
          }
        for (int x = 0; x < 64; x++) {
          ans[0][x] = ans[1][x];
          ans[1][x] = false;
        }
      }
    int mx = 0;
    for (int x = 0; x < 64; x++)
      if (ans[0][x]) {
        mx = max(mx, (int)bitset<8>(x).count());
      }
    // cerr << "cs=" << c.size() << endl;
    // cerr << "mx=" << mx << endl;
    cout << (k - mx) << endl;
  }
}