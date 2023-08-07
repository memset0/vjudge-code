#include <bits/stdc++.h>
using namespace std;
const int N = 109;
int n, cnt[N][N];
inline void move(int a, int b, int c) {
#ifdef memset0
  assert(cnt[a][c]);
  --cnt[a][c];
  ++cnt[b][c];
#endif
  // fprintf(stderr, "move %d from %d to %d\n", c, a, b);
  cout << a << ' ' << c << ' ' << b << '\n';
}
void solve(int n) {
  if (n == 2) {
    move(2, 1, 2);
    return;
  }
  solve(n - 1);
  move(n, n - 1, n);
  for (int i = 2; i < n - 1; i++) {
    move(i, n, i);
    move(n, i, n);
  }
  move(n - 1, n, n - 1);
  move(1, n - 1, 1);
	move(n, 1, n);
  // cerr << endl;
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n; j++) cerr << cnt[i][j] << " \n"[j == n];
  // }
  // cerr << endl;
}
int main() {
#ifdef memset0
  freopen("G.in", "r", stdin);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cnt[i][i] = n;
  }
  move(1, 0, 1);
  solve(n);
  move(0, n, 1);
#ifdef memset0
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) cerr << cnt[i][j] << " \n"[j == n];
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      assert(cnt[i][j] == 1);
    }
#endif
}