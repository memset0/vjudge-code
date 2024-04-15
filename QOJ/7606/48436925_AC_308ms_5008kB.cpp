#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
const int S = 200, L = 19, X = 40;
long long dp[L][S][X], pw[L];
vector<int> sg;
int digitsum(long long x) {
  int s = 0;
  while (x) {
    s += x % 10;
    x /= 10;
  }
  return s;
}
long long find_next(long long x) {
  for (long long y = x + 10;; y += 10)
    if (x < y - digitsum(y)) return y;
}
long long find_next_with(long long x, int s) {
  for (long long y = x + 10;; y += 10)
    if (x < y - digitsum(y) - s) return y;
}
long long DP(int i, int s, int x) {
  // fprintf(stderr, "dp[%d][%d][%d] = %lld\n", i, s, x, dp[i][s][x]);
  if (dp[i][s][x] != -1) return dp[i][s][x];
  if (i == 2) {
    long long u = x * 10, pre = -1;
    while (u < pw[3]) {
      pre = u;
      u = find_next_with(u, s);
    }
    return dp[i][s][x] = pre;
  } else {
    long long u = DP(i - 1, s, x);
    for (int j = 0; j <= 9; j++) {
      if (j) {
        u = j * pw[i] + DP(i - 1, s + j, u % 1000 / 10);
      }
      if (j != 9) {
        u = find_next_with(u, s);
      }
    }
    return dp[i][s][x] = u;
  }
}
bool solve(long long n) {
  if (n == 0) return 0;
  if (n % 10) return 1;
  vector<int> a;
  for (long long t = n; t; t /= 10) a.push_back(t % 10);
  // for (int i = 0; i < a.size(); i++)
  //     cerr << a[i] << " \n"[i + 1 == a.size()];
  long long u = a.back() * pw[a.size() - 1];
  for (int i = (int)a.size() - 2; i >= 4; i--) {
    // fprintf(stderr, "i=%d a[i]=%d u=%lld\n", i, a[i], u);
    int s = 0;
    for (int j = i + 1; j < a.size(); j++) s += a[j];
    for (int j = 0; j < a[i]; j++) {
      // fprintf(stderr, "<<<< dp[%d][%d][%lld]=%lld\n", i - 1, s + j, u % 1000 / 10, dp[i - 1][s + j][u % 1000 / 10]);
      u = u / pw[i + 1] * pw[i + 1] + j * pw[i] + DP(i - 1, s + j, u % 1000 / 10);
      // fprintf(stderr, ">>>> j=%d u=%lld[%d] next(u)=%lld[%d]\n", j, u, sg[u], find_next(u), sg[find_next(u)]);
      u = find_next(u);
    }
  }
  // fprintf(stderr, "!u=%lld n=%lld\n", u, n);
  while (u < n) {
    u = find_next(u);
  }
  return u != n;
}
void test(int N) {
  sg.push_back(0);
  for (int i = 1; i < N; i++) {
    int x = digitsum(i);
    for (int j = 1; j <= x; j++)
      if (sg[i - j] == 0) {
        sg.push_back(1);
        break;
      }
    if (sg.size() == i) {
      sg.push_back(0);
    }
  }
  for (int i = 1; i < N; i++) {
    if (i % 100000 == 0) printf("i=%d\n", i);
    if (sg[i] != solve(i)) {
      fprintf(stderr, "error i=%d sg=%d solve=%d\n", i, sg[i], solve(i));
    }
  }
}
void out(int n) { fprintf(stderr, "sg[%d] = %d\n", n, sg[n]); }
signed main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  pw[0] = 1;
  for (int i = 1; i <= L; i++) pw[i] = pw[i - 1] * 10;
  memset(dp, -1, sizeof(dp));
  cin.tie(0)->sync_with_stdio(0);
  // test(10000000);
  int T;
  cin >> T;
  while (T--) {
    long long n;
    cin >> n;
    cout << (solve(n) ? "Algosia" : "Bajtek") << endl;
  }
}//