#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 9;
int n, m, all, s[2][N];
template <const int d> inline void add(int k, int x) {
  for (; k < N; k += k & -k)
    s[d][k] += x;
}
template <const int d> inline int ask(int k) {
  int res = 0;
  for (; k; k -= k & -k)
    res += s[d][k];
  return res;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int k, l, r, i = 1; i <= m; i++) {
    cin >> k >> l >> r;
    if (k == 1) {
      ++all;
      add<0>(r, 1);
      add<1>(n - l + 1, 1);
    } else {
      cout << all - ask<0>(l - 1) - ask<1>(n - r) << endl;
    }
  }
}