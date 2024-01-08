#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int T, n, m, v[N];
long long suf[N];
pair<int, int> a[N];
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m;
    vector<pair<int, int>> vec;
    for (int x, y, i = 1; i <= m; i++) { cin >> a[i].first >> a[i].second; }
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++) { v[i] = a[i].first; }
    suf[m + 1] = 0;
    for (int i = m; i >= 1; i--) { suf[i] = suf[i + 1] + v[i]; }
    long long ans = 0;
    // for (int i = 1; i <= m; i++) cerr << v[i] << " \n"[i == m];
    // for (int i = 1; i <= m; i++) cerr << suf[i] << " \n"[i == m];
    for (int i = 1; i <= m; i++) {
      long long cur = 0;
      int k = upper_bound(v + 1, v + m + 1, a[i].second) - v;
      if (m - k + 1 > n - 1) { k = m - (n - 1) + 1; }
      if (k <= i) {
        // cerr << "! " << (n - (m - k + 1)) << endl;
        cur += suf[k] + (long long)(n - (m - k + 1)) * a[i].second;
      } else {
        // cerr << "! " << (n - 1 - (m - k + 1)) << endl;
        cur += suf[k] + a[i].first + (long long)(n - 1 - (m - k + 1)) * a[i].second;
      }
      // printf("i=%d[%d] k=%d cur=%lld\n", i, a[i].second, k, cur);
      ans = max(ans, cur);
    }
    cout << ans << endl;
  }
}