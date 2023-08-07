#include <bits/stdc++.h>
using namespace std;
const int N = 25;
int n, m, x[N], c[N], cur[N << 1];
vector<int> tmp;
struct interval {
  int l, r, v;
} v[N];
vector<tuple<int, int, int>> q;
vector<interval> split(int x) {
  vector<interval> vec;
  for (int l = 1, r; l <= x; l = r + 1) {
    r = x / (x / l);
    vec.push_back({l, r, x / l});
  }
  vec.push_back({x + 1, -1, 0});
  return vec;
}
int main() {
#ifdef memset0
  freopen("F.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> c[i];
    --x[i];
    tmp.push_back(c[i]);
  }
  sort(tmp.begin(), tmp.end());
  tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
  m = (int)tmp.size();
  for (int i = 1; i <= n; i++) {
    int cc = lower_bound(tmp.begin(), tmp.end(), c[i]) - tmp.begin() + 1;
    v[cc].l = v[cc].r = x[i];
    v[cc].v = c[i];
    c[i] = cc;
  }
  for (int i = 1; i <= n; i++) {
    v[c[i]].l = min(v[c[i]].l, x[i]);
    v[c[i]].r = max(v[c[i]].r, x[i]);
  }
  if (m == 1) {
    cout << -1 << endl;
    return 0;
  }
  sort(v + 1, v + m + 1, [&](const interval &a, const interval &b) { return a.l == b.l ? a.r < b.r : a.l < b.l; });
  for (int i = 2; i <= m; i++)
    if (v[i - 1].r >= v[i].l) {
      cout << 0 << endl;
      return 0;
    }
  for (int i = 1; i <= m; i++) {
    for (const auto &it : split(v[i].l)) {
      q.emplace_back(it.l, i, it.v);
    }
    for (const auto &it : split(v[i].r)) {
      q.emplace_back(it.l, i + m, it.v);
    }
  }
  sort(q.begin(), q.end());
  int ans = 0;
  for (int l = 0, r; l < q.size(); l = r + 1) {
    r = l;
    while (r + 1 < q.size() && get<0>(q[r + 1]) == get<0>(q[r])) r++;
    if (r + 1 == q.size()) break;
    int len = get<0>(q[r + 1]) - get<0>(q[r]);
    for (int i = l; i <= r; i++) {
      cur[get<1>(q[i])] = get<2>(q[i]);
    }
    bool fl = true;
    for (int i = 1; fl && i <= m; i++) fl = fl && cur[i] == cur[i + m];
    for (int i = 1; fl && i < m; i++) fl = fl && cur[i] < cur[i + 1];
    // fprintf(stderr, "[%d] l=%d r=%d len=%d :: %d~%d\n", fl, l, r, len, get<0>(q[l]), get<0>(q[r + 1]) - 1);
    // for (int i = 1; i <= m; i++) cerr << cur[i] << " \n"[i == m];
    // for (int i = 1; i <= m; i++) cerr << cur[i + m] << " \n"[i == m];
    if (fl) {
      ans += len;
    }
  }
  cout << ans << endl;
}