// =================================
//   author: memset0
//   date: 2019.07.13 21:16:56
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int i = (l), i##ed = (r); i <= i##ed; ++i)
#define for_each(i, a) for (size_t i = 0, i##ed = a.size(); i < i##ed; ++i)
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

const int N = 1e6 + 10, mod = 1e9 + 7;
int n, p, ans = 1, fac[N], ifac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }

inline int fpow(int a, int b) {
  int s = 1;
  for (; b; b >>= 1, a = mul(a, a))
    if (b & 1) s = mul(s, a);
  return s;
}

inline int binom(int n, int m) {
  if (n < m) return 0;
  return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

void init_factorial(int lim) {
  fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i <= lim; i++) fac[i] = mul(fac[i - 1], i);
  for (int i = 2; i <= lim; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
  for (int i = 2; i <= lim; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
}

void main() {
  read(n), read(p);
  init_factorial(std::max(n, p));
  for (int i = 1; i <= n; i++) {
    // printf("> %d : %d %d %d\n", i, fpow(2, i), binom(n, i), binom(p, i));
    ans = inc(ans, mul(fpow(2, i), mul(binom(n, i), binom(p, i))));
  }
  print(ans, '\n');
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  return ringo::main(), 0;
}
