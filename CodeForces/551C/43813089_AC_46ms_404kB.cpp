#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int n, m, a[N];
inline bool check(long long x) {
  // cerr << "check " << x << endl;
  int res = m - 1, at = 0;
  long long tim = x;
  for (int i = 1; i <= n; i++) {
    int todo = a[i];
    while (todo) {
      // cerr << "at = " << at << " " << tim << endl;
      tim -= i - at;
      at = i;
      // cerr << "at = " << at << " " << tim << endl;
      if (tim <= 0) {
        if (!res) {
          return false;
        }
        --res;
        tim = x - i;
        at = i;
        if (tim <= 0) {
          return false;
        }
      }
      int cost = (int)min(tim, (long long)todo);
      // cerr << (m - res) << " " << i << " " << tim << " " << todo << endl;
      tim -= cost;
      todo -= cost;
    }
  }
  return true;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0), ios::sync_with_stdio(0);
  cin >> n >> m;
  long long l = 1, r = (long long)n * n / 2 + 1, mid, ans;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    r += a[i];
  }
  while (l <= r) {
    mid = (l + r) >> 1;
    if (check(mid)) {
      r = mid - 1;
      ans = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << endl;
}