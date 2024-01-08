#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int n, m, k, t;
long long a[N];
long long solve(long long x) {
  long long d = x / n * n - x;
  while (d < 0) d += n;
  while (d % k) d += n;
  // fprintf(stderr, "[x=%lld d=%lld m=%d]\n", x, d, m << 1);
  return m * t * (d / k);
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) { cin >> a[i]; }
  if (n <= 3) {
    for (int i = 1; i <= 3; i++) {
      if (i > n) {
        cout << "1 1\n0" << endl;
      } else {
        cout << i << " " << i << endl;
        cout << -a[i] << endl;
      }
    }
    return 0;
  }
  if (n & 1) {
    m = (n + 1) >> 1;
    t = 2;
  } else {
    vector<int> pri = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 43};
    for (int x : pri) {
      if (n % x) {
        t = x;
        break;
      }
    }
    if (n == 6 || n == 8) {
      m = 5;
    } else {
      m = (n + 1) * (t - 1) / t;
      // cerr << "! m = " << m << endl;
      while (m % 2 == 0) m += 1;
      while (__gcd(m * t, n) != 1) m += 2;
      // cerr << "! m = " << m << endl;
    }
  }
  k = m * t % n;
  cerr << "! m = " << m << endl;
  cout << 1 << " " << m << endl;
  for (int i = 1; i <= m; i++) {
    long long t = solve(a[i]);
    cout << t << " \n"[i == m];
    a[i] += t;
  }
  // for (int i = 1; i <= n; i++) { cerr << a[i] << ",\n"[i == n]; }
  cout << (n - m + 1) << " " << n << endl;
  for (int i = (n - m + 1); i <= n; i++) {
    long long t = solve(a[i]);
    cout << t << " \n"[i == n];
    a[i] += t;
  }
  // for (int i = 1; i <= n; i++) { cerr << a[i] << ",\n"[i == n]; }
  cout << 1 << " " << n << endl;
  for (int i = 1; i <= n; i++) { cout << -a[i] << " \n"[i == n]; }
}
