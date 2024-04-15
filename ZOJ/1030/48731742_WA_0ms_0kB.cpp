#include <bits/stdc++.h>
#define maxn 300
#define pb push_back
#define mp make_pair
using namespace std;

const int INF = ~0u >> 1;
typedef pair<int, int> P;

const double PI = acos(-1.0);
const double EPS = 1e-10;
vector<pair<double, int>> g[maxn];

int k, T, d, u, v, Len, n;
int ans;
double x[maxn], y[maxn];
int mark[maxn][maxn];

bool check(double a, double b) {
  if (b > a + EPS) return b + EPS < a + PI;
  else
    return b + EPS < a - PI;
}

void dfs(int u, int v) {
  vector<pair<double, int>>::iterator it;
  for (it = g[v].begin(); it->second != u; it++)
    ;
  double w = it->first;
  if (it == g[v].begin()) it = --g[v].end();
  else
    it--;

  if (mark[v][it->second] == -1) {
    mark[v][it->second] = mark[u][v] + 1;
    dfs(v, it->second);
  } else {
    if (mark[v][it->second] != -2 && mark[u][v] - mark[v][it->second] + 1 == Len && check(it->first, w)) ans++;
  }
  mark[u][v] = -2;
}

int main() {
  cin >> T;
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 1; i <= n; i++) {
      scanf("%d", &u);
      scanf("%lf%lf", &x[u], &y[u]);
      scanf("%d", &d);
      for (int j = 0; j < d; j++) {
        scanf("%d", &v);
        g[u].pb(mp(0, v));
      }
    }
    vector<pair<double, int>>::iterator it;
    scanf("%d", &Len);
    for (int i = 1; i <= n; i++) {
      for (it = g[i].begin(); it != g[i].end(); it++) {
        it->first = atan2(y[it->second] - y[i], x[it->second] - x[i]);
      }
      sort(g[i].begin(), g[i].end());
    }
    ans = 0;
    memset(mark, -1, sizeof(mark));
    for (int i = 1; i <= n; i++) {
      for (it = g[i].begin(); it != g[i].end(); it++) {
        if (mark[i][it->second] == -1) {
          mark[i][it->second] = 0;
          dfs(i, it->second);
        }
      }
    }
    printf("%dn", ans);
  }
  return 0;
}