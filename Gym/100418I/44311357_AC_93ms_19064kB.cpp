#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int n, fa[N];
long long f[N][2], g[N][2], h[N][2], sum[N];
vector<int> G[N];
void dfs1(int u) {
  f[u][0] = 1;
  long long pre = 0;
  for (int v : G[u])
    if (v != fa[u]) {
      fa[v] = u;
      dfs1(v);
      f[u][0] += f[v][0];

      g[u][0] += f[v][0] + pre * f[v][0];
      pre += f[v][0];
      // fprintf(stderr, "u=%d v=%d pre=%lld g[u][0]=%lld\n", u, v, pre, g[u][0]);

      sum[u] += sum[v];
    }
  sum[u] += g[u][0];
}
void dfs2(int u) {
  long long pre[2] = {0, 0}, tot = 0;
  for (int v : G[u])
    if (v != fa[u]) {
      tot += sum[v];
    }
  for (int v : G[u])
    if (v != fa[u]) {
      dfs2(v);
      f[u][1] += sum[v];
      f[u][1] += f[v][1];
      f[u][1] += f[v][0] * (tot - sum[v]);

      g[u][1] += pre[0] * f[v][1];
      g[u][1] += pre[1] * f[v][0];
      // fprintf(stderr, "u=%d v=%d pre=%lld,%lld g[u][1]=%lld\n", u, v, pre[0], pre[1], g[u][1]);
      pre[0] += f[v][0];
      pre[1] += f[v][1];

      g[u][1] += f[v][1];
      g[u][1] += f[v][0] * (tot - sum[v]);
      // fprintf(stderr, "u=%d v=%d pre=%lld,%lld g[u][1]=%lld\n", u, v, pre[0], pre[1], g[u][1]);
    }
}
void dfs3(int u) {
  long long pre = 0;
  for (int v : G[u])
    if (v != fa[u]) {
      dfs3(v);
      h[u][0] += pre * sum[v];
      pre += sum[v];
    }
}
void dfs4(int u) {
  long long pre[2] = {0, 0}, tot = 0;
  for (int v : G[u])
    if (v != fa[u]) {
      tot += sum[v];
    }
  for (int v : G[u])
    if (v != fa[u]) {
      dfs4(v);
      h[u][1] += f[v][0] * (tot - sum[v]) * pre[0];
      h[u][1] -= f[v][0] * pre[1];
      pre[0] += f[v][0];
      pre[1] += f[v][0] * sum[v];
    }
}
int main() {
#ifdef memset0
  // freopen("I.in", "r", stdin);
  freopen("data.txt", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int u, v, i = 1; i < n; i++) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs1(1);
  dfs2(1);
  dfs3(1);
  dfs4(1);
#ifdef memset0
  cerr << "f[i][0] : ";
  for (int i = 1; i <= n; i++) cerr << f[i][0] << " \n"[i == n];
  cerr << "f[i][1] : ";
  for (int i = 1; i <= n; i++) cerr << f[i][1] << " \n"[i == n];
  cerr << "g[i][0] : ";
  for (int i = 1; i <= n; i++) cerr << g[i][0] << " \n"[i == n];
  cerr << "g[i][1] : ";
  for (int i = 1; i <= n; i++) cerr << g[i][1] << " \n"[i == n];
  cerr << "h[i][0] : ";
  for (int i = 1; i <= n; i++) cerr << h[i][0] << " \n"[i == n];
  cerr << "h[i][1] : ";
  for (int i = 1; i <= n; i++) cerr << h[i][1] << " \n"[i == n];
  cerr << "sum[i]  : ";
  for (int i = 1; i <= n; i++) cerr << sum[i] << " \n"[i == n];
#endif
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += h[i][0] + h[i][1] + g[i][1];
    // fprintf(stderr, "i=%d :: g1=%lld h0=%lld h1=%lld\n", i, g[i][1], h[i][0], h[i][1]);
  }
  cout << ans << endl;
}