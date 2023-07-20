// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.07.11 17:41:52
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

const int N = 2e4 + 10, NN = 34000000, mod = 1e9 + 7;
int T, n, m, ans, inv[N], _n[3], _m[3], fac[NN];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }

inline int get_inv(int x) {
  if (x < 2) return 1;
  return 1ll * (mod - mod / x) * get_inv(mod % x) % mod;
}

inline int fpow(int a, int b) {
  int s = 1;
  for (; b; b >>= 1, a = mul(a, a))
    if (b & 1) s = mul(s, a);
  return s;
}

inline int calc(int n, int m) {
  int ans = 1;
  for (int i = 2; i <= n + m; i++) {
    ans = mul(ans, fpow(inv[i - 1], std::min(n, i - 1) - std::max(1, i - m) + 1));
  }
  return ans;
}

void main() {
  fac[0] = inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) inv[i] = mul(mod - mod / i, inv[mod % i]);
  for (int i = 1; i < NN; i++) fac[i] = mul(fac[i - 1], i);
  for (read(T); T--; ) {
    read(n), read(m);
    for (int i = 0; i < 3; i++) {
      _n[i] = n <= i ? 0 : (n - i - 1) / 3 + 1;
      _m[i] = (n + m <= i ? 0 : (n + m - i - 1) / 3) - (n <= i ? 0 : (n - i - 1) / 3);
    }
    // printf("> %d %d %d %d %d %d\n", _n[0], _m[0], _n[1], _m[1], _n[2], _m[2]);
    ans = fac[_n[0] * _m[0] + _n[1] * _m[1] + _n[2] * _m[2]];
    ans = 1ll * ans * calc(_n[0], _m[0]) % mod;
    ans = 1ll * ans * calc(_n[1], _m[1]) % mod;
    ans = 1ll * ans * calc(_n[2], _m[2]) % mod;
    print(ans, '\n');
  }
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  return ringo::main(), 0;
}