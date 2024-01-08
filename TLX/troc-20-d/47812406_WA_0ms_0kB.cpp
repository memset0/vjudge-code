#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int n, a[N];
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) { cin >> a[i]; }
  vector<pair<int, int>> seg;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = l;
    if (a[l]) continue;
    while (r + 1 <= n && a[r + 1] == a[r]) ++r;
    seg.emplace_back(l, r);
  }
  auto check = [&]() {
    if (seg.size() <= 1) return true;
    if (seg.size() == 2 && seg[0].first == 1 && seg[1].second == n) return true;
    if (seg.size() <= 2) return true;
    return false;
  };
  cout << (check() ? "YES" : "NO") << endl;
}