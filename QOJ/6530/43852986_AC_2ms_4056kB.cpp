#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int t, n, p, q, sum, f[N];
int main() {
  cin >> t;
  while (t--) {
    cin >> p >> n;
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) scanf("%d", &f[i]);
    cin >> q;
    int x = 0, y = 0;
    sum = 0;
    for (int i = p; i <= q; i++) {
      if (f[y + 1] == i) {
        y++;
      } else
        sum++;
    }
    cout << sum << endl;
  }
}