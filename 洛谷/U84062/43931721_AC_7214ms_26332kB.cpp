// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.07.10 21:17:23
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

const int N = 55, M = 2200, mod = 1e9 + 9, w1 = 115381398, w2 = 884618610;
int n, m, max, num, lim = 1, a[N][N], tmp[M], f[M][N][N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void fwt2(int *a) {
  for (int len = 1; len < lim; len <<= 1)
    for (int i = 0; i < lim; i += (len << 1))
      for (int j = 0; j < len; j++) {
        int x = a[i + j], y = a[i + j + len];
        a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
      }
}

void fwt3(int *a) {
  for (int len = 1; len < lim; len *= 3)
    for (int i = 0; i < lim; i += len * 3)
      for (int j = 0; j < len; j++) {
        int x = a[i + j], y = a[i + j + len], z = a[i + j + (len << 1)];
        a[i + j] = (0ll + x + y + z) % mod;
        a[i + j + len] = (x + 1ll * w1 * y + 1ll * w2 * z) % mod;
        a[i + j + (len << 1)] = (x + 1ll * w2 * y + 1ll * w1 * z) % mod;
      }
}

void ifwt3(int *a) {
  for (int len = 1; len < lim; len *= 3)
    for (int i = 0; i < lim; i += len * 3)
      for (int j = 0; j < len; j++) {
        int x = a[i + j], y = a[i + j + len], z = a[i + j + (len << 1)];
        a[i + j] = (0ll + x + y + z) % mod;
        a[i + j + len] = (x + 1ll * w2 * y + 1ll * w1 * z) % mod;
        a[i + j + (len << 1)] = (x + 1ll * w1 * y + 1ll * w2 * z) % mod;
      }
}

int det(int a[N][N]) {
  int ans = 1, tmp;
  for (int i = 1; i <= n; i++) {
    // if (!a[i][i]) std::cerr << "error" << std::endl;
    ans = mul(ans, a[i][i]);
    tmp = inv(a[i][i]);
    for (int j = i; j <= n; j++)
      a[j][i] = mul(a[j][i], tmp);
    for (int j = i + 1; j <= n; j++) {
      tmp = a[j][i];
      for (int k = i; k <= n; k++)
        a[j][k] = dec(a[j][k], mul(a[i][k], tmp));
    }
  }
  return ans;
}

void main() {
  srand(20040725);
  read(num), read(n), read(m);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      read(a[i][j]);
      max = std::max(max, a[i][j]);
    }
  while (lim <= max) lim *= m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      memset(tmp, 0, lim << 2);
      tmp[a[i][j]] = rand() % mod;
      (m == 2 ? fwt2 : fwt3)(tmp);
      for (int k = 0; k < lim; k++)
        f[k][i][j] = tmp[k];
    }
  for (int k = 0; k < lim; k++)
    tmp[k] = det(f[k]);
  (m == 2) ? fwt2(tmp) : ifwt3(tmp);
  for (int k = 0; k < lim; k++)
    if (tmp[k]) print(k, ' ');
  putchar('\n');
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  return ringo::main(), 0;
}