#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int n, m, fa[N], cst[N], cnt[N], w[N], rt[N], v[N], lc[N], rc[N], npl[N];
long long ans, sum[N];
vector<int> G[N];
int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (v[x] < v[y]) swap(x, y);
  rc[x] = merge(rc[x], y);
  if (npl[lc[x]] < npl[rc[x]]) swap(lc[x], rc[x]);
  npl[x] = npl[rc[x]] + 1;
  return x;
}
void dfs(int u) {
  rt[u] = u, v[u] = cst[u];
  sum[u] = cst[u], cnt[u] = 1;
  for (int v : G[u]) {
    dfs(v);
    rt[u] = merge(rt[u], rt[v]);
    sum[u] += sum[v];
    cnt[u] += cnt[v];
  }
  while (sum[u] > m) {
    --cnt[u];
    sum[u] -= v[rt[u]];
    rt[u] = merge(lc[rt[u]], rc[rt[u]]);
  }
  ans = max(ans, (long long)w[u] * cnt[u]);
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> fa[i] >> cst[i] >> w[i];
    G[fa[i]].push_back(i);
  }
  dfs(1);
  cout << ans << endl;
}