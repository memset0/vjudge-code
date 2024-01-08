#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 9;
int T, n, a[N][N];
bool vis[N];
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
        cin >> a[i][j];
    }
    fill_n(vis + 1, n, false);
    for (int i = 1; i <= n; i++) {
      vis[a[1][i]] = true;
      if (i > 1) {
        int x = a[1][i];
        for (int j = 2; j <= n; j++)
          if (vis[a[x][j]]) {
            cout << a[x][j] << ' ' << x << '\n';
            break;
          }
      }
    }
  }
}