#include <bits/stdc++.h>
using namespace std;
int T;
long long x, y, L, R;
vector<pair<long long, int>> factor(long long x) {
  vector<pair<long long, int>> a;
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0) {
      a.emplace_back(i, 0);
      while (x % i == 0) {
        a.back().second++;
        x /= i;
      }
    }
  if (x > 1) a.emplace_back(x, 1);
  return a;
}
int main() {
#ifdef memset0
  freopen("G.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> x >> L >> R;
    auto xf = factor(x), yf = xf;
    // for (const auto &it : xf) cout << it.first << " " << it.second << ";;" << endl;
    y = 1;
    for (auto &it : yf) {
      it.second &= 1;
      if (it.second) y *= it.first;
    }
    long long l = 1, r = sqrt(R / x / y) * 2 + 100, mid, ans = -1;
    while (l <= r) {
      mid = (l + r) >> 1;
      if ((__int128)mid * mid * x * y >= L) {
        ans = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    assert(ans != -1);
    if ((__int128)x * y * ans * ans <= R) {
      cout << (y * ans * ans) << endl;
    } else {
      cout << (-1) << endl;
    }
  }
}