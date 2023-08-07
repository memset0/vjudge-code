#include <bits/stdc++.h>
using namespace std;
const int N = 1.2e4 + 10;
int n, m, tr[N], f[2][N], g[2][N];
char s[N][N];
vector<int> V[N];
long long ans;
inline void add(int x, int y) {
  for (int i = x; i <= m; i += i & -i) tr[i] += y;
}
inline int ask(int x) {
  int s = 0;
  for (int i = x; i > 0; i -= i & (-i)) s += tr[i];
  return s;
}
void solve() {
  int now = 1, pre = 0;
  memset(f, 0, N << 3), memset(g, 0, N << 3);
  for (int t = 3; t <= n; t += 2, swap(now, pre)) {
    memset(tr, 0, N << 2), memset(f[now], 0, N << 2), memset(g[now], 0, N << 2);
    int L = 0;
    for (int i = 1; i <= m; i++)
      if (s[t][i] == 'x') {
        if (i > 2 && (s[t - 1][i - 1] == '\\' || s[t - 1][i - 1] == '/')) f[now][i] = f[pre][i - 2] + 1;
        else
          f[now][i] = 0;
        if (i < m && (s[t - 1][i + 1] == '\\' || s[t - 1][i + 1] == '/')) g[now][i] = g[pre][i + 2] + 1;
        else
          g[now][i] = 0;
        if (s[t][i - 1] == '-') L++;
        else
          L = 0;
        int tmp = min(L, f[now][i]);
        if (tmp) ans += ask(i) - ask(i - tmp * 4 - 1);
        for (int j = 0; j < V[i].size(); j++) add(V[i][j], -1);
        V[i].clear();
        if (g[now][i]) {
          add(i, 1);
          if (i + g[now][i] * 4 <= m) V[i + g[now][i] * 4].push_back(i);
        }
      }
  }
}
void my_gets(char *s) {
  int c = getchar();
  while (c != '\n' && ~c) {
    *s++ = c;
    c = getchar();
  }
  *s++ = '\0';
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  scanf("%d%d\n", &n, &m), n = (n << 1) - 1, m = m << 1;
  for (int i = 1; i <= n; i++) my_gets(s[i] + 1);
  solve();
  reverse(s + 1, s + n + 1);
  solve();
  printf("%lld\n", ans);
}