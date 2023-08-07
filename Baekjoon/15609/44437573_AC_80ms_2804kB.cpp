#include <bits/stdc++.h>
using namespace std;
const int N = 4096 + 9;
int n, m, a[N];
double p[N];
vector<vector<pair<int, double>>> vec;
vector<pair<int, double>> solve(int l, int r) {
  assert(l < r);
  if (l + 1 == r) {
    return vec[l];
  }
  int mid = (l + r) >> 1;
  auto vl = solve(l, mid);
  auto vr = solve(mid, r);
  set<int> st;
  for (const auto &[i, x] : vl) st.insert(i), p[i] = 0;
  for (const auto &[i, x] : vr) st.insert(i), p[i] = 0;
  for (const auto &[i, x] : vl)
    for (const auto &[j, y] : vr) {
      p[i] += x * y * a[i] / (double)(a[i] + a[j]);
      p[j] += x * y * a[j] / (double)(a[i] + a[j]);
    }
  vector<pair<int, double>> vu;
  for (int x : st) {
    vu.emplace_back(x, p[x]);
  }
  return vu;
}
int main() {
#ifdef memset0
  freopen("K1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 2, a + n + 1);
  m = 1;
  while ((m << 1) <= n) m <<= 1;
  for (int i = 1, j = 1, t = 1; i <= m; i++, j += t) {
    if (i >= m - (n - m) + 1) t = 2;
    if (t == 1) {
      vec.push_back({{j, 1.}});
    } else {
      vec.push_back({
          {j, a[j] / (double)(a[j] + a[j + 1])},
          {j + 1, a[j + 1] / (double)(a[j] + a[j + 1])},
      });
    }
  }
  auto ans = solve(0, vec.size());
  assert(ans[0].first == 1);
  printf("%.12lf\n", (double)ans[0].second);
}