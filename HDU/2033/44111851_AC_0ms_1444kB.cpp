#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
int T, a, b, c, d, e, f;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> a >> b >> c >> d >> e >> f;
    a += d, b += e, c += f;
    if (c >= 60) c -= 60, ++b;
    if (b >= 60) b -= 60, ++a;
    cout << a << " " << b << " " << c << endl;
  }
}