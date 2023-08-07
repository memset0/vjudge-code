#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 9;
int n, m;
char s[N], t[N];
bool dp[N][N];
int main() {
#ifdef memset0
  freopen("L.in", "r", stdin);
#endif
  scanf("%s%s", s + 1, t + 1);
  n = strlen(s + 1);
  m = strlen(t + 1);
  dp[0][0] = true;
  for (int i = 1; i <= n; i++) {
    bool fl = false;
    for (int j = 1; j <= m; j++) {
      if (dp[i - 1][j - 1] && s[i] == t[j]) {
        dp[i][j] = true;
        if (t[j] != t[j + 1]) {
          fl = true;
        }
      }
      dp[i][j] |= fl;
    }
    // for (int j = 1; j <= m; j++) cerr << dp[i][j] << " \n"[j == m];
  }
  cout << (dp[n][m] ? "Yes" : "No") << endl;
}