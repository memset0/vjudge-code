#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int N = 1e5 + 9;
int n, k, s, a[N], dp[N];
struct segment {
  int l, r, mid;
  int max, min, ans;
} p[N << 2];
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  p[u].ans = n + 1;
  if (l == r) {
    p[u].min = p[u].max = a[l];
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
  p[u].min = min(p[u << 1].min, p[u << 1 | 1].min);
  p[u].max = max(p[u << 1].max, p[u << 1 | 1].max);
}
inline pii merge(const pii &a, const pii &b) { return make_pair(min(a.first, b.first), max(a.second, b.second)); }
pii query(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) { return make_pair(p[u].min, p[u].max); }
  if (r <= p[u].mid) return query(u << 1, l, r);
  if (l > p[u].mid) return query(u << 1 | 1, l, r);
  return merge(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
}
void update(int u, int k, int x) {
  if (p[u].l == p[u].r) {
    p[u].ans = x;
    return;
  }
  if (k <= p[u].mid) {
    update(u << 1, k, x);
  } else {
    update(u << 1 | 1, k, x);
  }
  p[u].ans = min(p[u << 1].ans, p[u << 1 | 1].ans);
}
int queryans(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) { return p[u].ans; }
  if (r <= p[u].mid) return queryans(u << 1, l, r);
  if (l > p[u].mid) return queryans(u << 1 | 1, l, r);
  return min(queryans(u << 1, l, p[u].mid), queryans(u << 1 | 1, p[u].mid + 1, r));
}
bool check(int l, int r) {
  auto it = query(1, l, r);
  return it.second - it.first <= s;
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> s >> k;
  for (int i = 1; i <= n; i++) { cin >> a[i]; }
  build(1, 0, n);
  dp[0] = 0;
  update(1, 0, 0);
  for (int i = 1; i <= n; i++) {
    int l = 1, r = i - k + 1, mid, res = i + 1;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (check(mid, i)) {
        res = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    dp[i] = n + 1;
    l = res, r = i - k + 1;
    if (l <= r) { dp[i] = min(dp[i], queryans(1, l - 1, r - 1) + 1); }
    update(1, i, dp[i]);
    // fprintf(stderr, "dp[%d] = %d :: %d %d\n", i, dp[i], l, r);
  }
  cout << (dp[n] > n ? -1 : dp[n]) << endl;
}