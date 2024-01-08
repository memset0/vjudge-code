#include <bits/stdc++.h>
#include <chrono>
#define all(x) (x).begin(), (x).end()
#define debug(x) cerr << #x << ": " << x << endl
using namespace std;
using ll = long long;
using lf = long double;
const int mod = 998244353;
int T;
long long n;
long long gcd(long long x, long long y) { return __gcd(x, y); }
// int fpow(int a, int b, int mod) {
//   int s = 1;
//   for (; b; b >>= 1, a = (ll)a * a % mod)
//     if (b & 1) s = (ll)s * a % mod;
//   return s;
// }
// int bruteforce(int n) {
//   int m = n * n - n;
//   int ans = 0;
//   for (int x = 1; x <= m; x++)
//     for (int y = x + 1; y <= m; y++) {
//       ans += fpow(x, y, n) == fpow(y, x, n);
//     }
//   return ans * 2 + m;
// }
// miller_rabin
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long power64(long long a, long long b, long long mod) {
  long long s = 1;
  for (; b; b >>= 1, a = (__int128)a * a % mod)
    if (b & 1) s = (__int128)s * a % mod;
  return s;
}
bool check(long long n, long long b) {
  long long a = n - 1;
  int k = 0;
  while (a % 2 == 0) {
    a /= 2;
    k++;
  }
  long long t = power64(b, a, n);
  if (t == 1 || t == n - 1) return true;
  while (k--) {
    t = (__int128)t * t % n;
    if (t == n - 1) return true;
  }
  return false;
}
bool miller_rabin(long long n) {
  if (n == 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  for (int i : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
    if (i >= n) break;
    if (!check(n, i)) return false;
  }
  return true;
}
long long pollards_rho(long long n) {
  if (miller_rabin(n)) return n;
  long long c = rng() % (n - 2) + 1, i = 1, k = 2, x = rand() % (n - 3) + 2, u = 2;
  while (true) {
    i++;
    x = ((__int128)x * x + c) % n;
    long long g = gcd((u - x + n) % n, n);
    if (g > 1 && g < n) {
      return g;
    }
    if (u == x) return 0;
    if (i == k) {
      u = x;
      k *= 2;
    }
  }
}
void solve_factor(long long n, vector<long long> &v) {
  if (n == 1) return;
  long long p;
  do {
    p = pollards_rho(n);
  } while (!p);
  if (p == n) {
    v.push_back(p);
    return;
  }
  solve_factor(p, v);
  solve_factor(n / p, v);
}
vector<pair<long long, int>> factor(long long n) {
  vector<long long> v;
  for (int i : {2, 3, 5, 7, 11, 13, 17, 19})
    while (n % i == 0) {
      v.push_back(i);
      n /= i;
    }
  // cerr << "n = " << n << endl;
  solve_factor(n, v);
  sort(v.begin(), v.end());
  // for (long long x : v) cerr << "! " << x << endl;
  vector<pair<long long, int>> r;
  for (int j, i = 0; i < v.size(); i = j) {
    j = i;
    while (j < v.size() && v[i] == v[j]) ++j;
    r.push_back(make_pair(v[i], j - i));
  }
  return r;
}
int solve(long long n) {
  --n;
  auto fac = factor(n);
  vector<vector<int>> f(fac.size()), g(fac.size());
  int ans = 1;
  for (int i = 0; i < fac.size(); i++) {
    long long p = fac[i].first;
    int e = fac[i].second;
    f[i].push_back(1);
    for (int x = 1, j = 0; j < e; j++) {
      f[i].push_back((p - 1) % mod * x % mod);
      x = p % mod * x % mod;
    }
    for (int x = 1, j = 0; j <= e; j++) {
      g[i].push_back((long long)x * x % mod);
      x = p % mod * x % mod;
    }
    reverse(g[i].begin(), g[i].end());
    int s = 0;
    for (int j = 0; j <= e; j++) {
      s = (s + (long long)f[i][j] * g[i][j]) % mod;
    }
    ans = (long long)ans * s % mod;
  }
  // for (int x = 1; x <= n; x++)
  //   if (n % x == 0)
  //     for (int y = 1; y <= n; y++)
  //       if (n % y == 0) {
  //         int a = 0, b = 0;
  //         for (int i = 1; i <= n; i++) a += gcd(i, n) == x;
  //         for (int i = 1; i <= n; i++) b += gcd(i, n) == y;
  //         ans += gcd(x, y) * a * b;
  //       }
  // cerr << "! " << ans << endl;
  ans = (ans + n) % mod;
  return n % mod * ans % mod;
}
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  // for (int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
  //   cerr << i << ": " << solve(i) << " " << bruteforce(i) << endl;
  // }
  cin >> T;
  while (T--) {
    cin >> n;
    cout << solve(n) << endl;
  }
}

/*
284789646
90061579
971585925
887008006
527110672
334479293

284789646
90061579
289022849
887008006
165192759
875816057
*/