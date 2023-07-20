#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 9;
int T, n, a[N], dp[N];
vector<pair<int, int>> qry[N];
struct node {
  int l, r, mid, max;
} p[N << 2];
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  p[u].max = -1;
  if (l == r) {
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
}
void update(int u, int k, int x) {
  if (p[u].l == p[u].r) {
    p[u].max = x;
    return;
  }
  if (k <= p[u].mid) {
    update(u << 1, k, x);
  } else if (k > p[u].mid) {
    update(u << 1 | 1, k, x);
  }
  p[u].max = max(p[u << 1].max, p[u << 1 | 1].max);
}
int query(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) {
    return p[u].max;
  }
  if (r <= p[u].mid) {
    return query(u << 1, l, r);
  } else if (l > p[u].mid) {
    return query(u << 1 | 1, l, r);
  } else {
    return max(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
  }
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      qry[i].clear();
    }
    build(1, 1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      int pre = -1;
      if (a[i] < n) {
        pre = query(1, a[i] + 1, n);
      }
      if (pre == -1) {
        qry[i - 1].emplace_back(i, 1);
      } else {
        qry[pre - 1].emplace_back(i, 2);
        qry[i - 1].emplace_back(i, 1);
      }
      update(1, a[i], i);
    }
    for (int i = 1; i <= n; i++) {
      dp[i] = i > 1 ? 2 : 1;
    }
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
      ans = max(ans, dp[i]);
      update(1, a[i], dp[i]);
      // fprintf(stderr, "dp[%d] = %d\n", i, dp[i]);
      for (const auto &it : qry[i]) {
        auto [j, w] = it;
        // fprintf(stderr, "seg[%d]:%d + %d -> dp[%d]:%d\n", i, query(1, 1, a[j]), w, j, dp[j]);
        dp[j] = max(dp[j], query(1, 1, a[j]) + w);
      }
    }
    cout << ans << endl;
  }
}