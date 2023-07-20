#include <bits/stdc++.h>

#ifndef MEM_GLOBAL_H
#define MEM_GLOBAL_H

// short stl
#define xx first
#define yy second
#define pb push_back
#define eb emplace_back
#define pii std::pair<int, int>
#define mp(a, b) std::make_pair(a, b)

// type
typedef long long ll;
typedef unsigned long long ull;
typedef double lf;
typedef long double llf;
#ifdef __SIZEOF_INT128__
typedef __int128_t lll;
typedef __uint128_t ulll;
#endif

// utils
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#endif

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
#ifdef _MSC_VER
    unsigned long long x;
    _umul128(z, im, &x);
#else
    unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
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
  explicit Modulus(int t) { x = t; }
  explicit Modulus(long long t) { x = safe_mod(t, mod); }

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
  inv[0] = inv[1] = Modulus<mod>(1);
  for (int i = 2; i < n; i++) inv[i] = Modulus<mod>(mod - mod / i) * inv[mod % i];
}
template <const int mod> void init_factorial(int n, Modulus<mod> *fac, Modulus<mod> *ifac) {
  fac[0] = Modulus<mod>(1), init_inverse(n, ifac);
  for (int i = 1; i < n; i++) fac[i] = fac[i - 1] * Modulus<mod>(i), ifac[i] = ifac[i - 1] * ifac[i];
}

#define ModInt Modulus

#endif

inline int gcd(int a, int b) {
  while (b != 0) {
    int tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}

const int N = 2048, mod = 998244353;
using std::vector;
using modint = Modulus<mod>;
int n, k;
modint ans, fac[N], inv[N], ifac[N], sum[N], dp[2][N >> 2][N];

inline modint order(int a, int b, int c, int d) { return fac[a + b + c + d] * ifac[a] * ifac[b] * ifac[c] * ifac[d]; }
inline modint slow_pow(modint x, int p) {
  modint s(1);
  while (p--) s *= x;
  return s;
}

void solve(vector<int> w) {
  // cerr << "solve ";
  // for (int x : w) cerr << x << " ";
  // cerr << endl;
  int _ = 0;
  memset(dp[_], 0, sizeof(dp[_]));
  for (int t = 0; t <= n; t++)
    if (t * w[0] <= k) {
      dp[_][t][t * w[0]] = slow_pow(ifac[t] * ifac[n - t], w[0]) * modint(n - t);
    }
  // for (int t = 0; t <= n; t++)
  //   for (int s = 0; s <= k; s++)
  //     if (dp[_][t][s].x) fprintf(stderr, "dp[%d][%d] = %d\n", t, s, dp[_][t][s].x);
  for (int i = 1; i < w.size(); i++) {
    memset(dp[_ ^ 1], 0, sizeof(dp[_ ^ 1]));
    // cerr << ">>>" << i << ">>>" << endl;
    for (int t = 0; t <= n; t++)
      for (int s = 0; s <= k; s++)
        if (dp[_][t][s].x) {
          // fprintf(stderr, "dp[%d][%d] = %d\n", t, s, dp[_][t][s].x);
          for (int v = t + 1; v <= n; v++)
            if (s + v * w[i] <= k) {
              dp[_ ^ 1][v][s + v * w[i]] += dp[_][t][s] * slow_pow(ifac[v] * ifac[n - v], w[i]);
            }
        }
    _ ^= 1;
  }
  modint tim = fac[4];
  for (int x : w) tim *= ifac[x];
  // cerr << "tim = " << tim.x << endl;
  for (int t = 0; t <= n; t++)
    for (int s = 0; s <= k; s++)
      if (dp[_][t][s].x) {
        sum[s] += tim * dp[_][t][s];
        // fprintf(stderr, "dp[%d][%d] -> %d\n", t, s, dp[_][t][s].x);
      }
}

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  init_inverse(N, inv);
  init_factorial(N, fac, ifac);
  // for (int i = 1; i <= 100; i++)
  //   for (int j = 1; j <= 100; j++)
  //     if (gcd(i, j) == 1 && (modint(i) * finv(modint(j))).x == 748683266) {
  //       cerr << "!! " << i << " " << j << endl;
  //     }

  cin >> n >> k;

  // for (int a = 0; a <= n && a <= k; a++)
  //   for (int b = 0; b <= n && a + b <= k; b++)
  //     for (int c = 0; c <= n && a + b + c <= k; c++)
  //       for (int d = 0; d <= n && a + b + c + d <= k; d++) {
  //         int t = min({a, b, c, d});
  //         modint s = modint(n - t) * inv[4 * n - a - b - c - d];
  //         modint g = ifac[a] * ifac[b] * ifac[c] * ifac[d] * ifac[n - a] * ifac[n - b] * ifac[n - c] * ifac[n - d];
  //         sum[a + b + c + d] += modint(n - t) * g;
  //         // fprintf(stderr, "%d %d %d %d : (%d / %d) * %d * %d\n", a, b, c, d, n - t, 4 * n - a - b - c - d, w.x, g.x);
  //         if (a + b + c + d == k) {
  //           ans += s * g * fac[a + b + c + d] * fac[4 * n - a - b - c - d] * modint(4 * n - k);
  //         } else {
  //           ans += s * g * fac[a + b + c + d] * fac[4 * n - a - b - c - d];
  //         }
  //       }
  // cerr << ans.x << endl;
  // ans *= finv(order(n, n, n, n));
  // cerr << ans.x << endl;
  // for (int i = 0; i <= k; i++) cerr << sum[i].x << " \n"[i == k];

  // ans = modint(0);
  // memset(sum, 0, sizeof(sum));

  solve({1, 1, 1, 1});
  solve({1, 1, 2});
  solve({1, 2, 1});
  solve({2, 1, 1});
  solve({1, 3});
  solve({2, 2});
  solve({3, 1});
  solve({4});
  for (int s = 0; s <= k; s++) {
    ans += sum[s] * fac[s] * fac[4 * n - s] * inv[4 * n - s] * modint(s == k ? 4 * n - k : 1);
  }
  // for (int i = 0; i <= k; i++) cerr << sum[i].x << " \n"[i == k];
  // cerr << ans.x << endl;
  ans *= finv(order(n, n, n, n));
  cout << ans.x << endl;
}//