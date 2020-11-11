#include <bits/stdc++.h>
using namespace std;

int n, x, y, z, i;

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> x >> y >> z;
    cout << 3 * z * x / (x + y) - z << endl;
  }
  return 0;
}