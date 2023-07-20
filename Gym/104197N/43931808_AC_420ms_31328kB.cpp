#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;

#ifndef MEM_MATH_H
#define MEM_MATH_H

using std::max;
using std::min;

template <typename T> inline T abs(T x) { return x < 0 ? -x : x; }
template <typename T> inline T lcm(T n, T m) { return n / gcd(n, m) * m; }
template <typename T> inline T gcd(T n, T m) { return m ? gcd(m, n % m) : n; }

template <typename X, typename T> constexpr T safe_mod(X x, const T &mod) {
  x %= mod;
  if (x < 0) x += mod;
  return x;
}

// ax+by = gcd(a,b) = g
// check: a>0 && b>0
// if a!=b: |x|<b && |y|<a
template <typename T> void exgcd(T a, T b, T &g, T &x, T &y) {
  if (!b) {
    g = a, x = 1, y = 0;
  } else {
    exgcd(b, a % b, g, y, x);
    y -= a / b * x;
  }
}

// m can be a composite number
template <typename T> T inverse(T a, T m) {
  T g, x, y;
  exgcd(a, m, g, x, y);
  if (g != 1) return -1; // no inverse element
  if (x < 0) x += m;
  return x;
}

struct barrett {
  unsigned int _m;
  unsigned long long im;

  explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

  unsigned int umod() const { return _m; }

  unsigned int mul(unsigned int a, unsigned int b) const {
    unsigned long long z = a;
    z *= b;
    unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
    unsigned long long y = x * _m;
    return (unsigned int)(z - y + (z < y ? _m : 0));
  }
};

#endif

#ifndef MEM_MODINT_H
#define MEM_MODINT_H

template <const int mod> struct Modulus {
  int x;
  Modulus() {}
  Modulus(int t) { x = t; }
  Modulus(long long t) { x = safe_mod(t, mod); }

  constexpr void operator*=(Modulus a) { x = (long long)x * a.x % mod; }
  constexpr void operator-=(Modulus a) { (x -= a.x) < 0 && (x += mod); }
  constexpr void operator+=(Modulus a) { (x += a.x) >= mod && (x -= mod); }

  friend constexpr Modulus operator*(const Modulus &a, const Modulus &b) { return Modulus<mod>((int)((long long)a.x * b.x % mod)); }
  friend constexpr Modulus operator-(Modulus a, const Modulus &b) { return ((a.x -= b.x) < 0 && (a.x += mod)), a; }
  friend constexpr Modulus operator+(Modulus a, const Modulus &b) { return ((a.x += b.x) >= mod && (a.x -= mod)), a; }
};

template <const int mod> inline Modulus<mod> finv(Modulus<mod> x) {
  if (x.x < 2) return x;
  return Modulus<mod>(mod - mod / x.x) * finv(Modulus<mod>(mod % x.x));
}

template <const int mod, typename T> inline Modulus<mod> fpow(Modulus<mod> a, T b) {
  Modulus<mod> s = 1;
  for (; b; b >>= 1, a = a * a)
    if (b & 1) s = s * a;
  return s;
}

template <const int mod> void init_inverse(int n, Modulus<mod> *inv) {
  inv[0] = inv[1] = 1;
  for (int i = 2; i < n; i++) inv[i] = (mod - mod / i) * inv[mod % i];
}
template <const int mod> void init_factorial(int n, Modulus<mod> *fac, Modulus<mod> *ifac) {
  fac[0] = 1, init_inverse(n, ifac);
  for (int i = 1; i < n; i++) fac[i] = fac[i - 1] * i, ifac[i] = ifac[i - 1] * ifac[i];
}

#define ModInt Modulus

#endif

const int N = 4e6 + 7, mod = 998244353;
using mint = Modulus<mod>;

int T, a, b, c, d; // a: -2     b: -1     c: +1     d: +2
mint ans, fac[N], ifac[N];

inline mint C(int n, int m) { return fac[n] * ifac[m] * ifac[n - m]; }
inline mint order(int x, int y) { return C(x + y, x); }
inline mint order(int x, int y, int z) { return C(x + y + z, x + y) * C(x + y, x); }

mint S(int a, int b, int c, int d, bool k) {
  if (a < 0 || b < 0 || c < 0 || d < 0) return 0;
  d -= b << 1;
  mint w = k ? a + 1 : 1;
  d -= a, a = 0;
  if (d < 0) return 0;
  return order(b, c, d) * w;
  // mint s = 0;
  // for (int x = 0; x <= d; x++) s += order(b, c, d - x) * w;
  // return s;
}

mint F(int a, int b, int c, int d) {
  if (a < 0 || b < 0 || c < 0 || d < 0) return 0;
  mint s1 = S(a, b, c, d, 0);             // +1* ... +1/+2
  mint s2 = S(a - 1, b, c - 1, d - 1, 1); // +1* ... +2*n +1 -2*n
  mint s3 = S(a, b - 1, c, d - 1, 1);     // +1* ... +2*n +2 -1 -2*n
  // fprintf(stderr, "F(%d,%d,%d,%d) -> %d %d %d\n", a, b, c, d, s1.x, s2.x, s3.x);
  return s1 + s2 + s3;
}

mint G(int a, int b, int c, int d) {
  if (a < 0 || b < 0 || c < 0 || d < 0) return 0;
  mint s1 = a == 0 && d >= (b << 1) ? order(b, c, d - (b << 1)) : 0;
  mint s2 = S(a - 1, b, c - 1, d - 1, 0);
  mint s3 = S(a, b - 1, c, d - 1, 0);
  // fprintf(stderr, "G(%d,%d,%d,%d) -> %d %d %d\n", a, b, c, d, s1.x, s2.x, s3.x);
  return s1 + s2 + s3;
}

mint H(int a, int b, int c, int d) {
  mint s = 0;
  if (a > 0 && d > 0 && a == d && b == 0 && c == 1) s += 1;
  if (a >= 0 && d > 0 && a + 1 == d && b == 1 && c == 0) s += 1;
  return s;
}

mint solve(int a, int b, int c, int d) {
  if (c < 0) return 0;
  mint f1 = F(a, b, c - 1, d);     // +1
  mint f2 = F(a, b - 1, c, d - 1); // -1 +2
  mint g1 = G(a, b, c, d - 1);     // +2 ...
  mint g2 = G(a, b - 1, c, d - 2); // +2 -1 +2 ...
  mint h = H(a, b, c, d);
  // fprintf(stderr, "solve(%d,%d,%d,%d) -> %d %d %d %d %d\n", a, b, c, d, f1.x, f2.x, g1.x, g2.x, h.x);
  return f1 + f2 + g1 + g2 + h;
}

int main() {
#ifdef memset0
  freopen("N.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  init_factorial(N, fac, ifac);
  cin >> T;
  while (T--) {
    cin >> a >> b >> c >> d;
    ans = solve(a, b, c, d) + solve(d, c, b, a);
    cout << ans.x << endl;
  }
}