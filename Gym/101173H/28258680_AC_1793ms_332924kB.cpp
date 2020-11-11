#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define re register
#define file(a)                                                                \
  freopen(a ".in", "r", stdin);                                                \
  freopen(a ".out", "w", stdout)
inline int gi() {
  int f = 1, sum = 0;
  char ch = getchar();
  while (ch > '9' || ch < '0') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    sum = (sum << 3) + (sum << 1) + ch - '0';
    ch = getchar();
  }
  return f * sum;
}
const int N = 1010, Inf = 1e9 + 10;
int sum[N][N], n, a[N][N], len[N][N];
int wa[4] = {0, 1, 1, -1}, lk[4] = {1, 0, 0, 0};
const int maxn = 1000010;
int front[maxn], to[maxn << 2], nxt[maxn << 2], w[maxn << 2], cnt, f[maxn][21],
    dep[maxn], valm[maxn][21], vis[maxn];
void Add(int u, int v, int val) {
  to[++cnt] = v;
  nxt[cnt] = front[u];
  front[u] = cnt;
  w[cnt] = val;
}
int id(int x, int y) { return (x - 1) * n + y; }
int Sum(int a1, int b1, int a2, int b2) {
  return sum[a2][b2] + sum[a1 - 1][b1 - 1] - sum[a2][b1 - 1] - sum[a1 - 1][b2];
}
bool check(int x, int y, int len) {
  if (x - len <= 0 || x + len > n || y - len <= 0 || y + len > n)
    return false;
  if (Sum(x - len, y - len, x + len, y + len))
    return false;
  return true;
}
int F[maxn];
struct node {
  int u, v, w;
  bool operator<(const node &b) const { return w > b.w; }
} e[maxn << 2];
int find(int x) {
  if (F[x] != x)
    F[x] = find(F[x]);
  return F[x];
}
void init() {
  for (re int i = 1; i <= n; i++)
    for (re int j = 1; j <= n; j++)
      sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + a[i][j];
  for (re int i = 1; i <= n; i++)
    for (re int j = 1; j <= n; j++)
      if (!a[i][j]) {
        int l = 0, r = n / 2, ans = 0;
        while (l <= r) {
          int mid = (l + r) >> 1;
          if (check(i, j, mid)) {
            ans = mid;
            l = mid + 1;
          } else
            r = mid - 1;
        }
        len[i][j] = ans * 2 + 1;
      }
  for (re int i = 1; i <= n; i++)
    for (re int j = 1; j <= n; j++)
      for (re int k = 0; k < 2; k++) {
        int x = i + wa[k], y = j + lk[k];
        if (x <= 0 || x > n || y <= 0 || y > n)
          continue;
        e[++cnt] = (node){id(i, j), id(x, y), min(len[i][j], len[x][y])};
      }
  sort(e + 1, e + cnt + 1);
  for (re int i = 1; i <= n * n; i++)
    F[i] = i;
  for (re int i = 1; i <= cnt; i++) {
    int u = find(e[i].u), v = find(e[i].v);
    if (u != v) {
      F[v] = u;
      Add(e[i].u, e[i].v, e[i].w);
      Add(e[i].v, e[i].u, e[i].w);
    }
  }
}
void dfs(int u, int fa) {
  if (vis[u])
    return;
  dep[u] = dep[fa] + 1;
  f[u][0] = fa;
  vis[u] = 1;
  for (re int i = front[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa)
      continue;
    valm[v][0] = w[i];
    dfs(v, u);
  }
}
int lca(int u, int v) {
  int res = Inf;
  if (dep[u] < dep[v])
    swap(u, v);
  for (re int i = 20; ~i; i--)
    if (dep[u] - (1 << i) >= dep[v]) {
      res = min(res, valm[u][i]);
      u = f[u][i];
    }
  if (u == v)
    return res;
  for (re int i = 20; ~i; i--)
    if (f[u][i] != f[v][i]) {
      res = min(res, min(valm[u][i], valm[v][i]));
      u = f[u][i], v = f[v][i];
    }
  return min(res, min(valm[u][0], valm[v][0]));
}
int query(int a1, int b1, int a2, int b2) {
  int A = id(a1, b1), B = id(a2, b2);
  return lca(A, B);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  n = gi();
  for (re int i = 1; i <= n; i++)
    for (re int j = 1; j <= n; j++) {
      char ch = getchar();
      while (ch != '#' && ch != '.')
        ch = getchar();
      a[i][j] = ch == '#';
    }
  init();
  dfs(1, 1);
  for (re int i = 1; i <= 20; i++)
    for (re int j = 1; j <= n * n; j++) {
      f[j][i] = f[f[j][i - 1]][i - 1];
      valm[j][i] = min(valm[f[j][i - 1]][i - 1], valm[j][i - 1]);
    }
  int Q = gi();
  while (Q--) {
    int a1 = gi(), b1 = gi(), a2 = gi(), b2 = gi();
    printf("%d\n", query(a1, b1, a2, b2));
  }
  return 0;
}
