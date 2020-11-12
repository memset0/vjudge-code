#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)

using namespace std;

typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef long long ll;

template <typename _T> inline void read(_T &f) {
  f = 0;
  _T fu = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') {
      fu = -1;
    }
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    f = (f << 3) + (f << 1) + (c & 15);
    c = getchar();
  }
  f *= fu;
}

template <typename T> void print(T x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x < 10)
    putchar(x + 48);
  else
    print(x / 10), putchar(x % 10 + 48);
}

template <typename T> void print(T x, char t) {
  print(x);
  putchar(t);
}

const int N = 10005, md = 998244353;

inline int add(int x, int y) {
  x += y;
  if (x >= md)
    x -= md;
  return x;
}

inline int sub(int x, int y) {
  x -= y;
  if (x < 0)
    x += md;
  return x;
}

inline int mul(int x, int y) { return 1ll * x * y % md; }

inline int fpow(int x, int y) {
  int ans = 1;
  while (y) {
    if (y & 1)
      ans = mul(ans, x);
    y >>= 1;
    x = mul(x, x);
  }
  return ans;
}

vector<int> a[N], b[N];
int low[N], dfn[N], st[N], fac[N], inv[N], siz[N], f[N];
int T, n, m, rt, oldn, top, cnt;

void tarjan(int u) {
  st[++top] = u;
  low[u] = dfn[u] = ++cnt;
  for (int i = 0; i < (int)a[u].size(); i++) {
    int v = a[u][i];
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        int tmp = 0;
        ++n;
        while (tmp != v) {
          tmp = st[top--];
          b[n].push_back(tmp);
        }
        b[u].push_back(n);
      }
    } else
      low[u] = min(low[u], dfn[v]);
  }
}

inline int C(int n, int m) {
  if (n < 0 || m < 0 || n < m)
    return 0;
  return mul(fac[n], mul(inv[m], inv[n - m]));
}

void dfs1(int u) {
  for (int i = 0; i < (int)b[u].size(); i++)
    dfs1(b[u][i]);
  siz[u] = 0;
  if (u <= oldn) {
    f[u] = 1;
    for (int i = 0; i < (int)b[u].size(); i++) {
      int v = b[u][i];
      f[u] = mul(f[u], mul(f[v], inv[siz[v]]));
      siz[u] += siz[v];
    }
    f[u] = mul(f[u], fac[siz[u]]);
    ++siz[u];
  } else {
    f[u] = 0;
    int len = b[u].size(), sumf = 1;
    for (int i = 0; i < len; i++)
      sumf = mul(sumf, f[b[u][i]]), siz[u] += siz[b[u][i]];
    for (int i = len / 2, now = 1; i >= 0; i--, now = md - now) {
      int sum = 1, sumsiz = 0;
      for (int j = i - 1; j >= 0; j--)
        sum = mul(sum, C(sumsiz + siz[b[u][j]] - 1, sumsiz)),
        sumsiz += siz[b[u][j]];
      sum = mul(sum, C(siz[u], sumsiz));
      sumsiz = 0;
      for (int j = i; j < len; j++)
        sum = mul(sum, C(sumsiz + siz[b[u][j]] - 1, sumsiz)),
        sumsiz += siz[b[u][j]];
      // if (u == 7) fprintf(stderr, "sum = %d, sumsiz = %d, siz[u] = %d\n",
      // sum, sumsiz, siz[u]);
      f[u] = add(f[u], mul(now, sum));
    }
    f[u] = mul(f[u], sumf);
  }
  // fprintf(stderr, "f[%d] = %d\n", u, f[u]);
}

int main() {
  // freopen("input.txt", "r", stdin);
  fac[0] = 1;
  for (int i = 1; i <= 10000; i++)
    fac[i] = mul(fac[i - 1], i);
  inv[10000] = fpow(fac[10000], md - 2);
  for (int i = 10000; i >= 1; i--)
    inv[i - 1] = mul(inv[i], i);
  read(T);
  while (T--) {
    for (int i = 1; i <= n; i++)
      low[i] = dfn[i] = st[i] = 0, a[i].clear(), b[i].clear();
    cnt = 0;
    read(n);
    read(m);
    read(rt);
    oldn = n;
    for (int i = 1; i <= m; i++) {
      int u, v;
      read(u);
      read(v);
      a[u].push_back(v);
      a[v].push_back(u);
    }
    tarjan(rt);
    dfs1(rt);
    print(f[rt], '\n');
  }
  return 0;
}