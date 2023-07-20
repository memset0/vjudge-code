#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int mod = 998244353;
int T, n, m, inv[10];

inline int C(int n, int k) {
  int ans = 1;
  for (int i = 1; i <= k; i++) ans = (long long)ans * (n + 1 - i) % mod;
  for (int i = 1; i <= k; i++) ans = (long long)ans * inv[i] % mod;
  return ans;
}

int solve1(int n) { return C(n, 4); }
int solve2(int n) { return C(n, 4); }
int solve3(int n) {
  int t = C(n, 2);
  int ans = (long long)t * t % mod;
  // ans = (long long)ans * (mod + 1 >> 1) % mod;
  // cerr << "solve3 " << n << " = " << ans << endl;
  return ans;
}

int main() {
#ifdef memset0
  freopen("C.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  inv[0] = inv[1] = 1;
  for (int i = 2; i < 10; i++) inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
  cin >> n >> m;
  // ++n, ++m;
  long long x1 = solve1(n);
  long long x2 = solve2(n);
  long long x3 = solve3(n);
  long long y1 = solve1(m);
  long long y2 = solve2(m);
  long long y3 = solve3(m);
  long long ans = (x1 * y1 % mod + (x2 * y3 % mod + x3 * y2 % mod) - x2 * y2 % mod * 2) % mod;
  ans = (ans + mod) % mod;
  cout << ans << endl;
}