#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9, mod = 998244353;
int T, a, b, c, fac[N], ifac[N], inv[N];
inline int solve(int n, int m) {
  long long sum = 0;
  for (int k = 0; k <= n && k <= m; k++) {
    sum += (long long)fac[n] * ifac[n - k] % mod * ifac[k] % mod * fac[m] % mod * ifac[m - k] % mod;
  }
  return sum % mod;
}
int main() {
#ifdef memset0
  freopen("I.in", "r", stdin);
#endif
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
    fac[i] = (long long)fac[i - 1] * i % mod;
    ifac[i] = (long long)ifac[i - 1] * inv[i] % mod;
  }
  cin >> T;
  while (T--) {
    cin >> a >> b >> c;
    int s1 = solve(a, b);
    int s2 = solve(a, c);
    int s3 = solve(b, c);
    cout << (long long)s1 * s2 % mod * s3 % mod << endl;
  }
}