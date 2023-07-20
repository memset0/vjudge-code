#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
int T, n, a[N], b[N];
inline int gcd(int a, int b) {
  while (b != 0) {
    int tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}
int main() {
#ifdef memset0
  freopen("G.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    b[n + 1] = -114514;
    for (int i = n; i >= 1; i--) {
      if (a[i] == -1) {
        b[i] = max(2, b[i + 1] + 1);
      } else {
        b[i] = b[i + 1] - 1;
      }
    }
    // for (int i = 1; i <= n; i++) cerr << a[i] << " \n"[i == n];
    // for (int i = 1; i <= n; i++) cerr << b[i] << " \n"[i == n];
    int p = 1, q = 1;
    bool fl = true;
    for (int i = 1; i <= n; i++) {
      if (a[i] == 0) {
        if (q >= 2 && q - 2 >= b[i]) {
          a[i] = -1;
        } else {
          a[i] = 1;
        }
      }
      if (a[i] == 1) {
        p++;
        q++;
      } else {
        q--;
        if (q == 0) {
          cout << -1 << endl;
          fl = false;
          break;
        }
      }
      // cerr << i << " " << a[i] << " " << p << " " << q << endl;
    }
    if (fl) {
      int g = gcd(p, q);
      cout << (p / g) << " " << (q / g) << endl;
    }
  }
}