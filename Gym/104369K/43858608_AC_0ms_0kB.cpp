#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const int N = 10;
int T, n, m, x, y, k, ans, a[N][N];
#define at(i, j) (1ull << ((i)*m + (j)))

void dfs(ull x, int cnt) {
  if (cnt < ans) ans = cnt;
  // cerr << x << " " << cnt << endl;
  // for (int i = 0; i < n; i++)
  //   for (int j = 0; j < m; j++) cerr << ((x & at(i, j)) ? 1 : 0) << " \n"[j + 1 == m];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (x & at(i, j)) {
        if (i >= 2 && (x & at(i - 1, j)) && !(x & at(i - 2, j))) {
          dfs(x ^ at(i, j) ^ at(i - 1, j) ^ at(i - 2, j), cnt - 1);
        }
        if (j >= 2 && (x & at(i, j - 1)) && !(x & at(i, j - 2))) {
          dfs(x ^ at(i, j) ^ at(i, j - 1) ^ at(i, j - 2), cnt - 1);
        }
        if (i + 2 < n && (x & at(i + 1, j)) && !(x & at(i + 2, j))) {
          dfs(x ^ at(i, j) ^ at(i + 1, j) ^ at(i + 2, j), cnt - 1);
        }
        if (j + 2 < m && (x & at(i, j + 1)) && !(x & at(i, j + 2))) {
          dfs(x ^ at(i, j) ^ at(i, j + 1) ^ at(i, j + 2), cnt - 1);
        }
      }
}

int main() {
#ifdef memset0
  freopen("K.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    // cerr << "!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    memset(a, 0, sizeof(a));
    cin >> n >> m >> k, ans = k;
    ull s = 0;
    while (k--) {
      cin >> x >> y;
      --x, --y;
      a[x][y] = 1;
      s |= 1ull << (x * m + y);
    }
    dfs(s, ans);
    cout << ans << endl;
  }
}