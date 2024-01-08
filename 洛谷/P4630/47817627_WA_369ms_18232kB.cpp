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
int pas[N], son[N], col[N], siz[N], dfn[N], low[N], ins[N], stk[N], vis[N];
int tot = 2, hed[N], nxt[M << 1], to[M << 1];
ll ans;

struct edge {
  int u, v;
} e[M];

inline void newEdge(int u, int v) {
  nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
  nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
}

void tarjan(int u, int father) {
  dfn[u] = low[u] = ++tim, ins[u] = 1, stk[++top] = u;
  for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
    if (v != father) {
      if (!dfn[v]) {
        tarjan(v, u);
        low[u] = std::min(low[u], low[v]);
      } else if (ins[v]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
  if (dfn[u] == low[u])
    for (++cnt; ; ) {
      int v = stk[top--];
      col[v] = cnt, ins[v] = 0, ++siz[cnt];
      if (u == v) break;
    }
}

void dfs(int u, int father, int n) {
  int sum = 0; vis[u] = 1;
  if (u <= n) siz[u] = 1;
  for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
    if (v != father) {
      dfs(v, u, n);
      siz[u] += siz[v];
      if (v > n) sum += siz[v];
    }
  if (u > n) {
    ans += son[u] * (son[u] - 1) * (son[u] - 2);
    ans += 2ll * (son[u] - 1) * (son[u] - 1) * (n - son[u]);
    ans += son[u] * (n - sum - son[u]) * (siz[u] - son[u]);
    // printf("%d : %d\n", u, son[u] * (son[u] - 1) * (son[u] - 2));
    // printf("%d : %d\n", u, 2ll * (son[u] - 1) * (son[u] - 1) * (n - son[u]));
    // printf("%d :: %d %d\n", u, (n - sum - son[u]), (siz[u] - son[u]));
    for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
      if (v != father && v > n) {
        // printf("%d -> %d :: %d\n", u, v, son[u] * siz[v] * (n - son[u] - siz[v]));
        ans += son[u] * siz[v] * (n - son[u] - siz[v]);
      }
  }
}

void main() {
  read(n), read(m);
  for (int i = 1; i <= m; i++) {
    read(u), read(v), e[i] = (edge){u, v};
    newEdge(u, v);
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i]) {
      int old = tim;
      tarjan(i, 0);
      pas[i] = tim - old;
    }
  tot = 2, memset(hed, 0, sizeof(hed));
  for (int i = 1; i <= n; i++) {
    newEdge(i, n + col[i]);
    ++son[n + col[i]];
  }
  // for (int i = 1; i <= n; i++) print(col[i], " \n"[i == n]);
  for (int i = 1; i <= m; i++) {
    u = e[i].u, v = e[i].v;
    if (col[u] != col[v]) {
      newEdge(n + col[u], n + col[v]);
    }
  }
  for (int i = 1; i <= n + cnt; i++)
    if (!vis[i]) {
      dfs(i, 0, pas[i]);
    }
  // for (int i = 1; i <= n + cnt; i++) print(siz[i], " \n"[i == n + cnt]);
  print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }