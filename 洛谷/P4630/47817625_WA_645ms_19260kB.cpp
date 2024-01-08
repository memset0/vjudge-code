// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.12 14:49:04
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
namespace ringo {
typedef long long ll;

template < class T > inline void read(T &x) {
  x = 0; register char c = getchar(); register bool f = 0;
  while (!isdigit(c)) f ^= c == '-', c = getchar();
  while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
  if (f) x = -x;
}
template < class T > inline void print(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) print(x / 10);
  putchar('0' + x % 10);
}
template < class T > inline void maxd(T &a, T b) { if (b > a) a = b; }
template < class T > inline void mind(T &a, T b) { if (b < a) a = b; }
template < class T > inline void print(T x, char c) { print(x), putchar(c); }

const int N = 1e5 + 10, M = 2e5 + 10;
int n, m, u, v, cnt, tim, top;
int col[N], siz[N], dfn[N], low[N], ins[N], stk[N], vis[N];
ll ans, sum[N];
int tot = 2, hed[N], nxt[M << 1], to[M << 1];

struct edge {
  int u, v;
} e[M];

ll C(int x, int y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  if (y == 2) return (ll)x * (x - 1) / 2;
  return (ll)x * (x - 1) * (x - 2) / 6;
}

void tarjan(int u, int father) {
  dfn[u] = low[u] = ++tim, ins[u] = 1, stk[++top] = u;
  for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
    if (v != father) {
      if (!dfn[v]) tarjan(v, u), low[u] = std::min(low[u], low[v]);
      else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
    }
  if (dfn[u] == low[u])
    for (++cnt; ; ) {
      int v = stk[top--];
      col[v] = cnt, ins[v] = 0, ++siz[cnt];
      if (u == v) break;
    }
}

void dfs(int u, int father) {
  // printf("dfs %lld %lld\n", u, father);
  int tmp = 0;
  vis[u] = 1, sum[u] = siz[u];
  ans += (ll)siz[u] * (siz[u] - 1) * (siz[u] - 2);
  for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
    if (v != father) {
      dfs(v, u), sum[u] += sum[v];
      // printf(">>> %lld %lld %lld\n", 2ll * tmp * sum[v], sum[v] * (sum[v] - 1) * siz[u], 2ll * (siz[u] - 1) * (siz[u] - 1) * sum[v]);
      ans += 2ll * tmp * sum[v], tmp += sum[v];
      ans += 2ll * (sum[v] - 1) * (sum[v] - 1) * siz[u];
      ans += 2ll * (siz[u] - 1) * (siz[u] - 1) * sum[v];
    }
}

void main() {
  read(n), read(m);
  for (int i = 1; i <= m; i++) {
    read(u), read(v), e[i] = (edge){u, v};
    nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
    nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i]) tarjan(i, 0);
  // for (int i = 1; i <= n; i++) print(dfn[i], " \n"[i == n]);
  // for (int i = 1; i <= n; i++) print(low[i], " \n"[i == n]);
  tot = 2, memset(hed, 0, sizeof(hed));
  for (int i = 1; i <= m; i++) {
    u = col[e[i].u], v = col[e[i].v];
    if (u != v) {
      nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
      nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
    }
  }
  // for (int i = 1; i <= n; i++) print(col[i], " \n"[i == n]);
  // for (int i = 1; i <= m; i++) printf("%d %d\n", col[e[i].u], col[e[i].v]);
  for (int i = 1; i <= cnt; i++) if (!vis[i]) dfs(i, 0);
  // for (int i = 1; i <= cnt; i++) print(siz[i], " \n"[i == cnt]);
  // for (int i = 1; i <= cnt; i++) print(sum[i], " \n"[i == cnt]);
  print(ans, '\n');
  // for (int i = 1; i <= cnt; i++)
  //   printf("%lld %lld %lld %lld\n", f[i][0], f[i][1], f[i][2], f[i][3]);

}
} signed main() { return ringo::main(), 0; }