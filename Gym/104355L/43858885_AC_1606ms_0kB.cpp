#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
long long n;
int m, c1, c2, b, c, oldans;
long long x, y;
void exgcd(long long a, long long b, long long &x, long long &y) {
  if (b == 0) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}
inline int fpow(long long k, int m) {
  long long s = 1, x = 2;
  while (k) {
    if (k & 1) s = s * x % m;
    k >>= 1;
    x = x * x % m;
  }
  return s;
}
struct atom {
  int a, b;
  friend inline atom operator*(const atom &x, const atom &y) { return {((long long)x.a * y.a % mod * m + (long long)x.a * y.b + (long long)x.b * y.a + (long long)x.b * y.b / m) % mod, (long long)x.b * y.b % m}; }
};
inline int R() { return rand() % 5 + 2; }
inline old_calc() {
  int ans = 0;
  int tot = (1 << n) - 1;
  for (int x = 0; x < (1 << n); x++) {
    if (((long long)c1 * (tot - x) + (long long)c2 * x) % m == b % m) {
      // cerr << "x=" << x << " " << ((long long)c1 * (tot - x) + (long long)c2 * x) << endl;
      ans++;
    }
  }
  return ans;
}
int solve() {
  cin >> n >> m >> c1 >> c2 >> b;
  // n = R(), m = R(), c1 = R(), c2 = R(), b = R();
  // c1 %= m, c2 %= m, b %= m;
  // cerr << n << " " << m << " " << c1 << " " << c2 << " " << b << endl;
  // oldans = old_calc();
  b = (b - (long long)c1 * (fpow(n, m) - 1 + m) % m + m) % m;
  c = (c2 - c1 + m) % m;
  // cerr << b << " " << c << endl;
  if (c == 0) {
    if (b != 0) {
      return 0;
    }
    return fpow(n, mod);
  }
  int g = __gcd(c, m);
  if (g > 1) {
    if (b % g) {
      return 0;
    }
    c /= g;
    m /= g;
    b /= g;
  }
  exgcd(c, m, x, y);
  int d = (x % m + m) % m;
  // cerr << c << " " << d << " " << m << endl;
  assert((long long)c * d % m == 1);
  int e = (long long)d * b % m;
  // printf("%d %d %d %d\n", c, b, m, e);
  atom s = {0, 1}, x = {2 / m, 2 % m};
  // printf("sr:%d %d\n", (1 << n) / m, (1 << n) % m);
  while (n) {
    if (n & 1) {
      s = s * x;
    }
    n >>= 1;
    x = x * x;
  }
  // printf(" s:%d %d\n", s.a, s.b);
  return (s.a + (s.b > e)) % mod;
}
int main() {
  int T;
  cin >> T;
  while (T--) {
    int ans = solve();
    // cerr << ans << " " << oldans << endl;
    // assert(ans == oldans);
    cout << ans << endl;
  }
}
/*
5
5 5 1 3 0
5 5 1 3 1
5 5 1 3 2
5 5 1 3 3
5 5 1 3 4


1 3 2 4 4 3
*/