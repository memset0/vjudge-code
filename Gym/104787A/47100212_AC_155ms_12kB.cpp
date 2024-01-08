#include <bits/stdc++.h>
using namespace std;
int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  int n, k;
  cin >> n >> k;
  auto print = [&](int x, int y) { cout << (x + 1) << ' ' << (y + 1) << '\n'; };
  for (int i = 0; i < n; i++) {
    print(i, i);
    print(i, (i + 1) % n);
  }
  int m = n << 1;
  for (int i = 0; m < k && i < n; i++)
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      if (j == (i + 1) % n) continue;
      if (m >= k) break;
      m++;
      print(i, j);
    }
}