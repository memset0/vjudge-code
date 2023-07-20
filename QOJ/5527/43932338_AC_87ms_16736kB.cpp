#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 2e5 + 9;
int T, n, m;
vector<int> G[N];

int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
int scc[N], sc; // 结点 i 所在 SCC 的编号
int sz[N];      // 强连通 i 的大小

void tarjan(int u) {
  low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
  for (int v : G[u]) {
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (in_stack[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++sc;
    while (s[tp] != u) {
      in_stack[s[tp--]] = 0;
    }
    in_stack[s[tp--]] = 0;
  }
}

int main() {
#ifdef memset0
  freopen("K.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n >> m;
    sc = dfncnt = 0;
    rep(i, 1, n) {
      dfn[i] = 0;
      G[i].clear();
    }
    for (int u, v, i = 1; i <= m; i++) {
      cin >> u >> v;
      G[u].push_back(v);
    }
    rep(i, 1, n) if (!dfn[i]) tarjan(i);
    // rep(i, 1, n) cerr << dfn[i] << " \n"[i == n];
    // rep(i, 1, n) cerr << low[i] << " \n"[i == n];
    cout << (sc == 1 ? "yes" : "no") << endl;
  }
}