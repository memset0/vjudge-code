#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;
int n, x, y, xx, yy;
vector<tuple<int, int, int, int>> ans;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> x >> y;
  xx = min(x, y);
  yy = max(x, y);
  if (x < y) {
    for (int i = 1; i <= y - x; i++) {
      ans.emplace_back(x + i, y - i, -i, i);
    }
  } else if (x > y) {
    for (int i = 1; i <= x - y; i++) {
      ans.emplace_back(x - i, y + i, i, -i);
    }
  }
  for (int i = 1; i < xx; i++) {
    ans.emplace_back(i, i, yy - i, yy - i);
  }
  for (int i = yy + 1; i <= n; i++) {
    ans.emplace_back(i, i, -i + 1, -i + 1);
  }
  cout << "Yes" << endl;
  cout << ans.size() << endl;
  for (const auto &[a, b, c, d] : ans) {
    cout << a << " " << b << " " << c << " " << d << endl;
  }
}