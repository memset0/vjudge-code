#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9, mod = 1e9 + 7;
int n, a[N], dp[N], last[N];
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    if (!last[a[i]]) {
      dp[i] = (dp[i - 1] * 2ll + 1) % mod;
    } else {
      dp[i] = (dp[i - 1] * 2ll - dp[last[a[i]] - 1]) % mod;
    }
    last[a[i]] = i;
  }
  cout << (dp[n] + mod) % mod << endl;
}