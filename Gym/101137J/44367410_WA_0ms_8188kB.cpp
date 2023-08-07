#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int n, a[N];
long long sum, b[N], f[1 << N];
int main() {
#ifdef memset0
  freopen("J.in", "r", stdin);
#endif
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];
  for (int k = 1; k < n; k++) {
    // cerr << ">>> k = " << k << endl;
    for (int i = 0; i < n; i++) b[i] = a[i] * k - sum;
    // for (int i = 0; i < n; i++) cerr << b[i] << " \n"[i + 1 == n];
    for (int x = 1; x < (1 << n); x++) {
      f[x] = -1e18;
      for (int i = 0; i < n; i++)
        if ((x >> i) & 1) {
          f[x] = max(f[x], f[x ^ (1 << i)] + b[i]);
        }
      if (f[x] == -sum) f[x] = 0;
      // cerr << bitset<N>(x) << " " << f[x] << endl;
    }
    if (f[(1 << n) - 1] == 0) {
      cout << k << endl;
      return 0;
    }
  }
}