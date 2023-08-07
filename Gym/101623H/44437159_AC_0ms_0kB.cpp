#include <bits/stdc++.h>
using namespace std;
int n, a, b, c, d;
long long ans;
void calc(int a, int b, int c) { ans = max(ans, (long long)a * a + (long long)b * b + (long long)c * c + 7ll * min({a, b, c})); }
int main() {
#ifdef memset0
  freopen("H.in", "r", stdin);
#endif
  cin >> n;
  const int L = 20;
  for (int t = 1; t <= n; t++) {
    ans = 0;
    cin >> a >> b >> c >> d;
    for (int i = 0; i < L && i <= d; i++)
      for (int j = 0; j < L && i + j <= d; j++)
        for (int k = 0; k < L && i + j + k <= d; k++) {
          int r = d - i - j - k;
          calc(a + i + r, b + j, c + k);
          calc(a + i, b + j + r, c + k);
          calc(a + i, b + j, c + k + r);
        }
    cout << ans << endl;
  }
}