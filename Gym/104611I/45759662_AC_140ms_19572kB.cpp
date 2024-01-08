#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9, mod = 1e9 + 7;
int t, dp[10][N], pw[11][N], C[11][11];
inline int popc(unsigned int x) { return __builtin_popcount(x); }
inline int get_digit() {
  static char c;
  do {
    cin >> c;
  } while (!isdigit(c));
  return c - '0';
}
int solve(vector<int> a) {
  if (a.empty()) {
    return 0;
  }
  long long res = 0;
  unsigned int x = 0;
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i]; j++) {
      int u = popc(x | (1 << j));
      if (u <= t) {
        res += (long long)C[10 - u][t - u] * dp[t - u][a.size() - i - 1];
        // fprintf(stderr, "i=%d j=%d u=%d x=%u x'=%u :: %d %d :: %lld\n", i, j, u, x, x | (1 << j), C[10 - u][t - u], dp[t - u][a.size() - i - 1], res);
      }
    }
    x |= 1 << a[i];
  }
  if (popc(x) == t) {
    ++res;
  }
  // fprintf(stderr, "solve => %lld\n", res);
  return (res % mod + mod) % mod;
}
int main() {
#ifdef memset0
  freopen("I.in", "r", stdin);
#endif
  for (int i = 0; i <= 10; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
  }
  int n;
  cin >> n;
  vector<int> l(n), r(n);
  for (int i = 0; i < n; i++) {
    l[i] = get_digit();
  }
  for (int i = 0; i < n; i++) {
    r[i] = get_digit();
  }
  reverse(l.begin(), l.end());
  --l[0];
  for (int i = 0; i < n; i++)
    if (l[i] < 0) {
      --l[i + 1];
      l[i] += 10;
    } else {
      break;
    }
  while (l.size() && l.back() == 0) {
    l.pop_back();
  }
  reverse(l.begin(), l.end());
  cin >> t;
  for (int i = 0; i <= t; i++) {
    pw[i][0] = 1;
    for (int j = 1; j < N; j++) {
      pw[i][j] = (long long)pw[i][j - 1] * i % mod;
    }
  }
  for (int i = 0; i < 10 && i <= t; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k <= i; k++) {
        dp[i][j] = (dp[i][j] + (long long)C[i][k] * ((i - k) & 1 ? mod - 1 : 1) % mod * pw[t - i + k][j]) % mod;
      }
    }
  }
  cout << (solve(r) - solve(l) + mod) % mod << endl;
}