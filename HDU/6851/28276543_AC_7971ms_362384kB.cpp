#include <cassert>
#include <cstdio>
#include <cstring>

const int P = 998244353;
inline int mul(const int &a, const int &b) { return 1ll * a * b % P; }
inline int add(int a, const int &b) {
  a += b;
  return (a >= P) ? a - P : a;
}
inline int sub(int a, const int &b) {
  a -= b;
  return (a < 0) ? a + P : a;
}
int qsm(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1)
      ans = mul(ans, a);
    a = mul(a, a);
    b >>= 1;
  }
  return ans;
}
int n, m, cnt[2097152], lim, x, y, invy, stk[22], top, val[2097152], stat[22],
    inv[22];
int f[2097152][22], g[2097152][22];
bool map[22][22], vis[22];
void FMT(int *a) {
  for (register int i = 1; i < lim; i <<= 1)
    for (register int j = 0; j < lim; j += (i << 1))
      for (register int k = 0; k < i; ++k)
        a[i + j + k] = add(a[i + j + k], a[j + k]);
}
void IFMT(int *a) {
  for (register int i = 1; i < lim; i <<= 1)
    for (register int j = 0; j < lim; j += (i << 1))
      for (register int k = 0; k < i; ++k)
        a[i + j + k] = sub(a[i + j + k], a[j + k]);
}
void bFMT(int a[2097152][22], const int &n) {
  auto y = a + 1, z = a + 1;
  for (register int i = 1, j, k; i < lim; i <<= 1)
    for (j = 0; j < lim; j += (i << 1))
      for (k = 0, y = a + j, z = a + i + j; k < i; ++k, ++y, ++z)
        for (register int x = n; ~x; --x)
          (*z)[x] = add((*z)[x], (*y)[x]);
}
void bIFMT(int a[2097152][22], const int &n) {
  auto y = a + 1, z = a + 1;
  for (register int i = 1, j, k; i < lim; i <<= 1)
    for (j = 0; j < lim; j += (i << 1))
      for (k = 0, y = a + j, z = a + i + j; k < i; ++k, ++y, ++z)
        for (register int x = n; ~x; --x)
          (*z)[x] = sub((*z)[x], (*y)[x]);
}
void dfs(int x, int j) {
  vis[x] = 1;
  stat[j] |= 1 << x;
  for (int i = 0; i < n; i++)
    if (map[x][i] && !vis[i])
      dfs(i, j);
}
unsigned long long tem;
int ans = 1;
int main() {
  scanf("%d", &n);
  lim = 1 << 21;
  for (int i = 1, p, b; i <= n; i++) {
    scanf("%d%d", &p, &b);
    if (b)
      f[b][__builtin_popcount(b)] = add(f[b][__builtin_popcount(b)], p);
    else
      ans = mul(ans, add(p, 1));
  }
  bFMT(f, 20);
  for (int i = 0; i <= 20; i++)
    inv[i] = qsm(i, P - 2);
  for (int i = 0; i < lim; i++) {
    g[i][0] = 1;
    for (int j = 1; j <= 20; j++) {
      for (int k = 0; k < j; k++)
        g[i][j] = add(g[i][j], mul(g[i][k], mul(j - k, f[i][j - k])));
      g[i][j] = mul(g[i][j], inv[j]);
    }
    //        for(int j=0;j<=2;j++)printf("%d ",f[i][j]);putchar('\n');
    //        for(int j=0;j<=2;j++)printf("%d ",g[i][j]);putchar('\n');
  }
  bIFMT(g, 20);
  int q;
  scanf("%d", &q);
  for (int i = 1, x; i <= q; i++) {
    scanf("%d", &x);
    printf("%d\n", mul(g[x][__builtin_popcount(x)], ans));
  }
}