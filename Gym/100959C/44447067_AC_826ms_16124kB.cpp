#include <bits/stdc++.h>
using namespace std;
const int N = 2e2 + 9, L = 1e6;
int n, m, a[N], dis[2][L << 1 | 1];
queue<pair<int, int>> q;
inline int merge(int x, int y) {
  if ((~x) && (~y)) return min(x, y);
  return max(x, y);
}
int main() {
#ifdef memset0
  freopen("C.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  memset(dis, -1, sizeof(dis));
  dis[1][L] = 0;
  q.push(make_pair(1, L));
  while (q.size()) {
    auto [k, u] = q.front();
    q.pop();
    assert(-L <= u - L && u - L <= L);
    // cerr << k << " " << u << endl;
    if (k) {
      for (int i = 1; i <= n; i++)
        if (u + a[i] <= (L << 1) && dis[0][u + a[i]] == -1) {
          dis[0][u + a[i]] = dis[1][u] + 1;
          q.push({0, u + a[i]});
        }
    } else {
      for (int i = 1; i <= n; i++)
        if (u - a[i] >= 0 && dis[1][u - a[i]] == -1) {
          dis[1][u - a[i]] = dis[0][u] + 1;
          q.push({1, u - a[i]});
        }
    }
  }
  cin >> m;
  for (int s, t, i = 1; i <= m; i++) {
    cin >> s >> t;
    if (s % 2 != t % 2) {
      cout << -1 << '\n';
    } else {
      int ans1 = dis[0][((t + s) >> 1) + L];
      int ans2 = dis[1][((t - s) >> 1) + L];
      cout << merge(ans1, ans2) << '\n';
    }
  }
}