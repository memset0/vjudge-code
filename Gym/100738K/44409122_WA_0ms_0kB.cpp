#include <bits/stdc++.h>
using namespace std;
int a, b, p;
bool check(long long n) {
  // a * n^{1/3} + b n^{1/2} >= p
  double A = (double)a * a * a * n;
  double B = (double)b * b * n;
  double x = a * pow(n, 1.0 / 3);
  while (x * x * x > A) x -= 1;
  double y = b * sqrt(n);
  while (y * y > B) y -= 1;
  // cerr << "n = " << n << endl;
  for (int s = 1; s > 1e-9; s /= 10) {
    while ((x + s) * (x + s) * (x + s) <= A) x += s;
    while ((y + s) * (y + s) <= B) y += s;
    if (x + y >= p) return true;
  }
  return false;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin >> a >> b >> p;
  long long l = 1, r = (long long)p * p + 9, mid, ans = -1;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << endl;
}