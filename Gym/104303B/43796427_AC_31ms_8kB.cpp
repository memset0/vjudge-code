#include <bits/stdc++.h>
using namespace std;
int T, a, b, n;
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> a >> b >> n;
    if (a <= b) {
      cout << (long long)b * n << "\n";
    } else {
      long long ans = b;
      n -= 1;
      ans += (long long)n / 2 * (a + b);
      if (n & 1) {
        ans += b;
      }
      cout << ans << "\n";
    }
  }
}