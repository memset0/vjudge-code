// luogu-judger-enable-o2
// test

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 60
#define gc getchar
#define rg register
using namespace std;

inline int rd() {
  rg int x = 0;
  rg bool f = 0;
  rg char c = gc();
  while (!isdigit(c)) {
    if(c == '-') f = 1;
    c = gc();
  }
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = gc();
  }
  return f ? -x : x;
}

bool vis[N];

int r, b, g, n, m, mod;

int ans, tr[N], sz[N], f[N][N][N];

inline int calc() {
  int tot = 0;
  for (rg int nr = r; ~nr; --nr)
      for (rg int nb = b; ~nb; --nb)
        for (rg int ng = g; ~ng; --ng) f[nr][nb][ng] = 0;
  for (rg int i = 1; i <= n; ++i) vis[i] = 0;
  for (rg int i = 1, p, len; i <= n; ++i)
    if (!vis[i]) {
      p = i; len = 0;
      while (!vis[p]){
        ++len; vis[p] = 1; p = tr[p];
      }
      sz[++tot] = len;
    }
  f[0][0][0] = 1;
  for (rg int i = 1; i <= tot; ++i)
    for (rg int nr = r; ~nr; --nr)
      for (rg int nb = b; ~nb; --nb)
        for (rg int ng = g; ~ng; --ng) {
          if (nr >= sz[i]) f[nr][nb][ng] = (f[nr][nb][ng] + f[nr-sz[i]][nb][ng]) % mod;
          if (nb >= sz[i]) f[nr][nb][ng] = (f[nr][nb][ng] + f[nr][nb-sz[i]][ng]) % mod;
          if (ng >= sz[i]) f[nr][nb][ng] = (f[nr][nb][ng] + f[nr][nb][ng-sz[i]]) % mod;
        }
  return f[r][b][g];
}

inline int qpow(int x, int t) {
  int res = 1;
  while (t) {
    if (t & 1) res = (res * x) % mod;
    x = (x * x) % mod; t >>= 1;
  }
  return res;
}

int main() {
  r = rd(); b = rd(); g = rd();
  n = r + b + g; m = rd(); mod = rd();
  for (rg int i = 1; i <= m; ++i) {
    for (rg int j = 1; j <= n; ++j) tr[j] = rd();
    ans = (ans + calc()) % mod;
  }
  for (rg int j = 1; j <= n; ++j) tr[j] = j;
  ans = (ans + calc()) % mod;
  printf("%d\n", ans * qpow(m + 1, mod - 2) % mod);
  return 0;
}