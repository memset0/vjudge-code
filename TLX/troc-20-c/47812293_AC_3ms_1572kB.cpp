#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 9;
int n, m, a[N][N];
int main() {
#ifdef memset0
  freopen("C.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      sum += a[i][j];
    }
  }
  if (sum == 0) {
    cout << "NO" << endl;
    return 0;
  }
  if (((n == 1 && m == 2) || (n == 2 && m == 1)) && sum == 2) {
    cout << "NO" << endl;
    return 0;
  }
  cout << "YES" << endl;
}