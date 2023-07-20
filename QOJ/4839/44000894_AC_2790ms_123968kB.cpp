#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 9;
int n, rt, all, tot, tim, fa[N], siz[N], mxp[N], dfn[N], ans[N];
bool vis[N];
vector<int> G[N], d[N];
vector<tuple<int, int, int, int>> qry;
namespace ini {
int tot, fa[N], dfn[N], siz[N];
long long sum, pre[N];
void dfs(int u) {
  dfn[u] = ++tot;
  siz[u] = 1;
  for (int v : G[u])
    if (v != fa[u]) {
      fa[v] = u;
      dfs(v);
      siz[u] += siz[v];
    }
}
void push(int u, int x) {
  pre[dfn[u]] += x;
  pre[dfn[u] + 1] -= x;
}
void push(int u, int v, int x) {
  if (v == fa[u]) {
    pre[0] += x;
    pre[dfn[u]] -= x;
    pre[dfn[u] + siz[u]] += x;
  } else {
    pre[dfn[v]] += x;
    pre[dfn[v] + siz[v]] -= x;
  }
}
inline void push(int u, int v, int w, int x) {
  // fprintf(stderr, "push %d %d %d : %d\n", u, v, w, x);
  pre[0] += x;
  push(u, v, -x);
  // for (int i = 0; i <= n; i++) cerr << pre[i] << " \n"[i == n];
  push(u, w, -x);
  // for (int i = 0; i <= n; i++) cerr << pre[i] << " \n"[i == n];
}
void init() {
  dfs(1);
  // for (int i = 1; i <= n; i++) cerr << dfn[i] << " \n"[i == n];
  // for (int i = 1; i <= n; i++) cerr << siz[i] << " \n"[i == n];
}
void solve() {
  // for (int i = 0; i <= n; i++) cerr << pre[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) pre[i] += pre[i - 1];
  // for (int i = 0; i <= n; i++) cerr << pre[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) ans[i] += pre[dfn[i]];
}
} // namespace ini
struct CountNode {
  int n, tim, s[N << 1];
  vector<int> ans, valx, valy;
  vector<pair<int, int>> nod;
  vector<tuple<int, int, int>> qry;
  inline void add(int k) {
    for (; k <= n; k += k & -k) s[k]++;
  }
  inline void ask(int k, int &x) {
    for (; k; k -= k & -k) x += s[k];
  }
  inline void addNode(int x, int y) {
    // cerr << "counter::addNode " << x << " " << y << endl;
    nod.emplace_back(x, y);
    valx.push_back(x), valy.push_back(y);
  }
  inline void addQuery(int x, int y) {
    // cerr << "counter::addQuery " << x << " " << y << endl;
    qry.emplace_back(x, y, qry.size());
    // valx.push_back(x), valy.push_back(y);
  }
  inline int getQuery() {
    // cerr << "counter::getQuery " << ans[tim] << endl;
    return ans[tim++];
  }
  void init() {
    // cerr << "counter::init" << endl;
    tim = 0, nod.clear(), qry.clear(), valx.clear(), valy.clear();
  }
  void solve() {
    ans.resize(qry.size());
    fill(ans.begin(), ans.end(), 0);
    if (!nod.size() || !qry.size()) return;
    if (nod.size() < 5) {
      for (auto &[xx, yy] : nod) {
        for (auto &[x, y, i] : qry) {
          if (xx <= x && yy <= y) ans[i]++;
        }
      }
      return;
    }
    valx.push_back(0);
    valy.push_back(0);
    // cerr << "counter::solve " << nod.size() << " " << qry.size() << endl;
    sort(valx.begin(), valx.end());
    sort(valy.begin(), valy.end());
    valx.erase(unique(valx.begin(), valx.end()), valx.end());
    valy.erase(unique(valy.begin(), valy.end()), valy.end());
    n = valy.size();
    fill(s, s + n + 1, 0);
    for (auto &[x, y] : nod) {
      x = upper_bound(valx.begin(), valx.end(), x) - valx.begin();
      y = upper_bound(valy.begin(), valy.end(), y) - valy.begin();
      // cerr << "node " << x << " " << y << endl;
    }
    for (auto &[x, y, i] : qry) {
      x = upper_bound(valx.begin(), valx.end(), x) - valx.begin();
      y = upper_bound(valy.begin(), valy.end(), y) - valy.begin();
      // cerr << "query " << x << " " << y << " " << i << endl;
    }
    sort(nod.begin(), nod.end());
    sort(qry.begin(), qry.end());
    int i = 0, j = 0;
    for (int x = 1; x <= valx.size(); x++) {
      while (i < nod.size() && nod[i].first == x) {
        add(nod[i].second), i++;
      }
      while (j < qry.size() && get<0>(qry[j]) == x) {
        ask(get<1>(qry[j]), ans[get<2>(qry[j])]), j++;
      }
    }
  }
} counter;
void getroot(int u) {
  siz[u] = 1, mxp[u] = 0;
  for (int v : G[u])
    if (!vis[v] && v != fa[u]) {
      fa[v] = u;
      getroot(v);
      siz[u] += siz[v];
      mxp[u] = max(mxp[u], siz[v]);
    }
  mxp[u] = max(mxp[u], all - siz[u]);
  if (!rt || mxp[u] < mxp[rt]) rt = u;
}
void getnode(int u, vector<int> &cur) {
  // cerr << "get node " << u << endl;
  cur.push_back(u);
  dfn[u] = ++tot, siz[u] = 1;
  for (int v : G[u]) {
    if (!vis[v] && v != fa[u]) {
      fa[v] = u;
      getnode(v, cur);
      siz[u] += siz[v];
    }
  }
}
void getquery(int u) {
  // cerr << "get query " << u << endl;
  for (int v : G[u])
    if (!vis[v] && v != fa[u]) {
      counter.addQuery(dfn[v] + siz[v] - 1, u - 1);
      counter.addQuery(dfn[v] - 1, u - 1);
      getquery(v);
    }
}
void pushans(int u) {
  // cerr << "push ans " << u << " " << w << " " << tot << endl;
  for (int v : G[u])
    if (!vis[v] && v != fa[u]) {
      int cur = counter.getQuery();
      cur -= counter.getQuery();
      ini::push(u, v, fa[u], cur);
      pushans(v);
    }
}
void solve(int u) {
  // cerr << "=== solve " << u << " ===" << endl;
  vis[u] = 1;
  vector<int> ch;
  tot = 1, dfn[u] = siz[u] = 1;
  for (int v : G[u]) {
    if (!vis[v]) ch.push_back(v);
  }
  counter.init();
  for (int k = 0; k < ch.size(); k++) {
    int v = ch[k];
    fa[v] = u;
    d[k].clear(), getnode(v, d[k]);
    siz[u] += siz[v];
  }
  set<pair<int, int>> st;
  for (int i = 0; i < ch.size(); i++) {
    sort(d[i].begin(), d[i].end());
    for (int x : d[i])
      if ((long long)x * u < n) {
        counter.addNode(dfn[x], x * u);
      }
    for (int x : d[i]) {
      for (auto &[y, j] : st) {
        if ((long long)x * y >= n) break;
        for (int y : d[j])
          if ((long long)x * y < n) {
            counter.addNode(dfn[x], x * y);
            counter.addNode(dfn[y], x * y);
            if ((long long)x * y < u) {
              ini::push(u, ch[i], ch[j], 1);
            }
          } else {
            break;
          }
      }
    }
    st.insert(make_pair(d[i][0], i));
  }
  qry.clear(), tim = 0;
  for (int v : ch) getquery(v);
  counter.solve();
  for (int v : ch) pushans(v);
  // cerr << tim << " " << qry.size() << endl;
  for (int v : ch) {
    rt = 0, all = siz[v], getroot(v), solve(rt);
  }
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
  // freopen("2.in", "r", stdin);
  // freopen("2.out", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int u, v, i = 1; i < n; i++) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  ini::init();
  rt = 0, all = n, getroot(1), solve(rt);
  ini::solve();
  long long tot = (long long)n * (n - 1) / 2 + n;
  // for (int i = 1; i <= n; i++) cerr << ans[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) cout << (tot - ans[i]) << '\n';
  cerr << "time: " << clock() / (double)CLOCKS_PER_SEC << endl;
}