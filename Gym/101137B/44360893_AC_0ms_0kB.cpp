#include <bits/stdc++.h>
using namespace std;
long long l, r, w, g;
inline void check(long long x) {
  x *= g;
  if (l - w < x && x < r) {
    cout << "DEADLOCK" << endl;
    exit(0);
  }
}
int main() {
#ifdef memset0
  freopen("B.in", "r", stdin);
#endif
  cin >> l >> r >> w;
  g = __gcd(r, w);
  check(r / g - 2);
  check(r / g - 1);
  check(r / g);
  check(r / g + 1);
  check(r / g + 2);
  check((l - w) / g - 2);
  check((l - w) / g - 1);
  check((l - w) / g);
  check((l - w) / g + 1);
  check((l - w) / g + 2);
  cout << "OK" << endl;
}