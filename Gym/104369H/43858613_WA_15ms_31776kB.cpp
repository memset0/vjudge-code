#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 9;
int T, n, m, ans, tim, l[N], r[N], x[N], y[N], tag[N];
int dfn[N], low[N], s[N], ins[N], scc[N], tp, sc;
bool fuck[N];
vector<int> G[N], ansL, ansR;
inline void add_edge(int u, int v) { G[u].push_back(v); }
void tarjan(int u) {
  low[u] = dfn[u] = ++tim, s[++tp] = u, ins[u] = 1;
  for (int v : G[u]) {
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (ins[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++sc;
    while (s[tp] != u) {
      scc[s[tp]] = sc;
      ins[s[tp]] = 0;
      --tp;
    }
    scc[s[tp]] = sc;
    ins[s[tp]] = 0;
    --tp;
  }
}
int main() {
#ifdef memset0
  freopen("H.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n >> m, ++n;

    ans = tp = sc = tim = 0;
    fill(tag, tag + n + 3, 0);
    fill(dfn, dfn + n + 3, 0);
    fill(ins, ins + n + 3, 0);
    fill(scc, scc + n + 3, 0);
    for (int i = 1; i <= n; i++) G[i].clear();

    for (int i = 1; i <= m; i++) {
      cin >> l[i] >> x[i] >> r[i] >> y[i];
      tag[l[i]] = max(tag[l[i]], x[i]);
      tag[r[i]] = max(tag[r[i]], y[i]);
      if (x[i] == 1 && y[i] == 1) ansL.push_back(i);
      if (x[i] == 2 && y[i] == 2) ansR.push_back(i);
      if (x[i] == 1 && y[i] == 2) {
        add_edge(l[i], r[i]);
      } else if (x[i] == 2 && y[i] == 1) {
        add_edge(r[i], l[i]);
      } else if (x[i] == 2 && y[i] == 2) {
        add_edge(n, l[i]);
        add_edge(n, r[i]);
      }
    }
    for (int i = 1; i <= n; i++) ans += tag[i];
    cerr << ans << endl;

    for (int i = 1; i <= n; i++)
      if (!dfn[i]) tarjan(i);
    fill(fuck, fuck + sc + 1, 0);
    for (int u = 1; u <= n; u++)
      for (int v : G[u])
        if (scc[u] != scc[v]) {
          fuck[v] = true;
        }
    for (int i = 1; i <= sc; i++)
      if (!fuck[i]) {
        ans--;
      }
    cout << ans << endl;
  }
}