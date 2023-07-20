#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
int T, n, p[N], dp[N];
vector<int> ch[N];
void dfs(int u) {
  if (!ch[u].size()) {
    dp[u] = 1;
    return;
  }
  int mx = 0, sx = -1;
  for (int v : ch[u]) {
    dfs(v);
    if (dp[v] > mx) {
      sx = mx, mx = dp[v];
    } else if (dp[v] > sx) {
      sx = dp[v];
    }
  }
  dp[u] = max(mx, sx + 1);
  // cerr << u << " : " << dp[u] << endl;
}
int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) ch[i].clear();
    for (int i = 1; i <= n; i++) {
      cin >> p[i];
      ch[p[i]].push_back(i);
    }
    dfs(1);
    cout << dp[1] << endl;
  }
}