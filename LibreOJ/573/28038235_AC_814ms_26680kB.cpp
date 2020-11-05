// =================================
//   author: memset0
//   date: 2019.07.08 13:48:12
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int (i) = (l), __lim = (r); (i) <= __lim; (i)++)
#define for_each(i, a) for (size_t i = 0, __lim = a.size(); i < __lim; ++i)
namespace ringo {

template <class T> inline void read(T &x) {
  x = 0; char c = getchar(); bool f = 0;
  while (!isdigit(c)) f ^= c == '-', c = getchar();
  while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
  if (f) x = -x;
}
template <class T> inline void print(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) print(x / 10);
  putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline void print(T a, int l, int r, std::string s = "") {
  if (s != "") std::cout << s << ": ";
  for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 1e6 + 10, mod = 998244353;
int n, m, l, r, opt, type, lastans, a[N];

struct matrix {
  int a00, a01, a10, a11;
  inline void out() const {
    printf("[%d %d %d %d]", a00, a10, a01, a11);
  }
} ans, f[N], g[N], x[N], y[N];

inline matrix getF(int a) { return (matrix){a, 1, 1, 0}; }
inline matrix getG(int a) { return (matrix){0, 1, 1, mod - a}; }

inline matrix operator*(const matrix &x, const matrix &y) {
  return (matrix){
    (int)((1ll * x.a00 * y.a00 + 1ll * x.a01 * y.a10) % mod),
    (int)((1ll * x.a00 * y.a01 + 1ll * x.a01 * y.a11) % mod),
    (int)((1ll * x.a10 * y.a00 + 1ll * x.a11 * y.a10) % mod),
    (int)((1ll * x.a10 * y.a01 + 1ll * x.a11 * y.a11) % mod)
  };
}

void main() {
  read(n), read(m), read(type);
  for (int i = 1; i <= n; i++) read(a[i]);
  f[0] = g[0] = {1, 0, 0, 1};
  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1] * getF(a[i]);
    g[i] = getG(a[i]) * g[i - 1];
  }
  // for (int i = 1; i <= n; i++) f[i].out(), putchar(" \n"[i == n]);
  // for (int i = 1; i <= n; i++) g[i].out(), putchar(" \n"[i == n]);
  for (int i = 1; i <= m; i++) {
    read(opt);
    if (opt == 1) {
      read(a[++n]);
      if (type) a[n] ^= lastans;
      f[n] = f[n - 1] * getF(a[n]);
      g[n] = getG(a[n]) * g[n - 1];
    } else {
      read(l), read(r);
      if (type) l ^= lastans, r ^= lastans;
      ans = g[l - 1] * f[r] * (matrix){1, 0, 0, 0};
      // g[l - 1].out(), f[r].out(), ans.out(), putchar('\n');
      print(ans.a00, ' '), print(ans.a10, '\n');
      lastans = ans.a00 ^ ans.a10;
    }
  }
}

} signed main() {
#ifdef memset0 
  freopen("1.in", "r", stdin);
#endif
  return ringo::main(), 0;
}
