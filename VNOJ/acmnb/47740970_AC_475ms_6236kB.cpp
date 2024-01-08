#include <bits/stdc++.h>
using namespace std;
const int N = 8e5 + 9;
int n, a[N];
int main() {
  cin >> n, n <<= 1;
  long long ans = 0;
  for (int x, y, i = 1; i <= n; i++) {
    cin >> x >> y;
    ans += x;
    a[i] = y - x;
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= (n >> 1); i++) {
    ans += a[i];
  }
  cout << ans << endl;
}
