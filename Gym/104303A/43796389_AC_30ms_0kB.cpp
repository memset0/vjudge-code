#include <bits/stdc++.h>
using namespace std;
const int N = 209;
int n, w, a[N];
int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> w;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int ans = 0;
    for (int i = n; i > 0; --i) {
      w -= a[i];
      ans++;
      if (w <= 0) break;
    }
    cout << ans << '\n';
  }
}