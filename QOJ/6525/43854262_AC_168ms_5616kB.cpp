#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 9;
int T, n, m, a[N], b[N];
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    long long ans = -1;
    cin >> n >> m;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i] >> b[i];
      b[i] -= a[i];
      sum += a[i];
    }
    sort(b + 1, b + n + 1);
    reverse(b + 1, b + n + 1);
    int x = min(n - 2, m - n);
    if (x >= 1) {
      for (int i = 1; i <= x; i++)
        if (b[i] > 0 || i == 1) {
          sum += b[i];
        } else {
          break;
        }
      // cerr << ">" << sum << endl;
      ans = max(ans, sum);
    }

    // all have
    if (m >= n && n > 1) {
      sum = 0;
      for (int i = 1; i <= n; i++) {
        sum += a[i];
      }
      // cerr << ">" << sum << endl;
      ans = max(ans, sum);
    }

    // all not have
    if (m >= n * 2 - 1) {
      sum = 0;
      for (int i = 1; i <= n; i++) {
        sum += a[i] + b[i];
      }
      // cerr << ">" << sum << endl;
      ans = max(ans, sum);
    }

    cout << ans << endl;
  }
}