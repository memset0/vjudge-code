#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
typedef std::string str;
typedef long long ll;
typedef std::pair<ll, ll> pii;
bool umax(int &a, int t) {
  if (t > a) return a = t, 1;
  return 0;
}
const int MAXN = 10011;
struct one {
  int d, s, dex;
  bool operator<(const one &you) const { return s - d < you.s - you.d; }
} a[MAXN];
int f[511][MAXN], pre[511][MAXN];

void print(int n, int m) {
  n = pre[n][m];
  if (!n) return;
  print(n - 1, m - a[n].s);
  printf("%d ", a[n].dex);
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].d, &a[i].s), a[i].dex = i;
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i) {
    memcpy(f[i], f[i - 1], sizeof f[i]), memcpy(pre[i], pre[i - 1], sizeof pre[i]);
    for (int j = 0; j <= m - a[i].d; ++j)
      if (umax(f[i][j + a[i].s], f[i - 1][j] + 1)) pre[i][j + a[i].s] = i;
    //  printf("consider (%d,%d)\n",a[i].d,a[i].s);
    //  for(int j=0;j<=m;++j)printf("%d ",f[i][j]);
    //  puts("");
  }
  int ans = 0, rest = 0;
  for (int j = 0; j <= m; ++j)
    if (umax(ans, f[n][j])) rest = j;
  printf("%d\n", ans);
  print(n, rest);
  return 0;
}