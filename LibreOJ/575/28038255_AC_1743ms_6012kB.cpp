// =================================
//   author: memset0
//   date: 2019.07.08 15:23:33
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

const int N = 4e5 + 10, mod = 998244353;
char s[N];
int n, a[N], b[N], w[N], f[N], g[N], cnt[N], rev[N], inv_fac[N];

inline int opp(int x) { return x ? mod - x : 0; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

int init(int len) {
  int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
  for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
  static int base_len = 1;
  for (int len = base_len, wn; len < lim; base_len = len <<= 1) {
    wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
    for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
  } return lim;
}

void ntt(int *a, int lim) {
  for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
  for (int len = 1; len < lim; len <<= 1)
    for (int i = 0; i < lim; i += (len << 1))
      for (int j = 0; j < len; j++) {
        int x = a[i + j], y = mul(a[i + j + len], w[j + len]);
        a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
      }
}

void solve(int l, int r) {
  if (l == r) {
    if (!l) f[0] = 1;
    else f[l] = cnt[l - 1] & 1 ? opp(f[l]) : f[l];
    if (s[l] == '>' || !l) g[l] = cnt[l] & 1 ? opp(f[l]) : f[l];
    return;
  }
  int mid = (l + r) >> 1;
  solve(l, mid);
  int len1 = mid - l + 1, len2 = r - l;
  int lim = init(len1 + len2 - 1), inv_lim = inv(lim);
  for (int i = 0; i < lim; i++) a[i] = i < len1 ? g[i + l] : 0;
  for (int i = 0; i < lim; i++) b[i] = i < len2 ? inv_fac[i + 1] : 0;
  ntt(a, lim), ntt(b, lim);
  for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
  std::reverse(a + 1, a + lim), ntt(a, lim);
  for (int i = 0; i < lim; i++) a[i] = mul(a[i], inv_lim);
  for (int i = mid + 1; i <= r; i++) f[i] = inc(f[i], a[i - l - 1]);
  solve(mid + 1, r);
}

void main() {
  scanf("%s", s + 1);
  n = strlen(s + 1) + 1;
  for (int i = 1; i <= n; i++) cnt[i] = cnt[i - 1] + (s[i] == '>');
  inv_fac[0] = inv_fac[1] = 1;
  for (int i = 2; i <= n; i++) inv_fac[i] = mul(mod - mod / i, inv_fac[mod % i]);
  for (int i = 2; i <= n; i++) inv_fac[i] = mul(inv_fac[i - 1], inv_fac[i]);
  solve(0, n); int ans = f[n];
  for (int i = 1; i <= n; i++) ans = mul(ans, i);
  print(ans, '\n');
}

} signed main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  return ringo::main(), 0;
}
