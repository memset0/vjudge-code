// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.07.11 10:51:33
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

const int N = 1e7 + 10;
ll m;
bool vis[N];
int n, mod, num, sum, ans, pcnt;
int f[N], inv[N], fac[N], ifac[N], pow[N], pri[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int binom(int n, int m) { return n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m])); }
inline int fpow(int a, ll b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void init(int lim) {
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i <= lim; i++) fac[i] = mul(fac[i - 1], i);
  for (int i = 2; i <= lim; i++) inv[i] = mul(mod - mod / i, inv[mod % i]);
  for (int i = 2; i <= lim; i++) ifac[i] = mul(ifac[i - 1], inv[i]);

  int M = (m + 1) % (mod - 1);
  pow[0] = 1;
  for (int i = 2; i <= lim; i++) {
    if (!vis[i]) {
      pri[++pcnt] = i;
      pow[i] = fpow(i, M);
    }
    for (int j = 1; j <= pcnt; j++) {
      int tmp = i * pri[j];
      if (tmp > lim) break;
      vis[tmp] = 1;
      pow[tmp] = mul(pow[i], pow[pri[j]]);
      if (i % pri[j] == 0) break;
    }
  }
}

void main() {
  read(num), read(n), read(m), read(mod), init(n);
  for (int i = 1; i <= n; i++) f[1] = inc(f[1], mul(i, i & 1 ? 1 : mod - 1));
  ans = dec((n + m) % mod, mul(f[1], m % mod));
  for (int i = 2; i <= n; i++) {
    if (i + n & 1 ^ 1) f[i] = inc(f[i - 1], inc(binom(n, i), binom(n, i - 1)));
    else f[i] = dec(f[i - 1], inc(binom(n, i), binom(n, i - 1)));
    f[i] = f[i] & 1 ? (f[i] + mod) >> 1 : f[i] >> 1;
    ans = inc(ans, mul(dec(1, f[i]), mul(dec(pow[i], i), inv[i - 1])));
  }
  print(ans, '\n');
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#else
  // freopen("abracadabra.in", "r", stdin);
  // freopen("abracadabra.out", "w", stdout);
#endif
  ringo::main();
  std::cerr << "clocks: " << clock() / (double)CLOCKS_PER_SEC << std::endl;
  return 0;
}