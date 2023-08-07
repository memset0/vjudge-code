#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 100;
int T, n, x[N];
unsigned long long dp[N][2][10][2];
bool check(string s) {
  bool fl = false;
  for (int i = 1; i < s.length(); i++) {
    if (fl && s[i] > s[i - 1]) {
      return false;
    }
    if (s[i] < s[i - 1]) {
      fl = true;
    }
  }
  return true;
}
void bruteforce(int x) {
  int ans = 0;
  for (int i = 1; i <= x; i++)
    if (check(to_string(i))) {
      ++ans;
    }
  cout << ans << endl;
}
void solve(string s) {
  memset(x, 0, sizeof(x));
  memset(dp, 0, sizeof(dp));
  if (!check(s)) {
    cout << -1 << endl;
    return;
  }
  n = s.length() + 3;
  for (int i = 0; i < s.length(); i++) x[s.length() - i - 1] = s[i] - '0';
  dp[n][1][0][0] = 1;
  for (int i = n; i; i--)
    for (int a = 0; a < 2; a++)
      for (int b = 0; b < 10; b++)
        for (int c = 0; c < 2; c++)
          if (dp[i][a][b][c]) {
            int r = a ? x[i - 1] : 9;
            for (int u = 0; u <= r; u++) {
              int aa = a && u == x[i - 1];
              int cc = c || u < b;
              if (c && u > b) break;
              dp[i - 1][aa][u][cc] += dp[i][a][b][c];
              // printf("dp[%d][%d][%d][%d] -> dp[%d][%d][%d][%d] : %llu\n", i, a, b, c, i - 1, aa, u, cc, dp[i][a][b][c]);
            }
          }
  unsigned long long ans = 0;
  for (int a = 0; a < 2; a++)
    for (int b = 0; b < 10; b++)
      for (int c = 0; c < 2; c++) {
        ans += dp[0][a][b][c];
      }
  cout << (ans - 1) << endl;
}
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    string s;
    cin >> s;
    solve(s);

    // int x;
    // cin >> x;
    // solve(to_string(x));
    // bruteforce(x);
  }
}