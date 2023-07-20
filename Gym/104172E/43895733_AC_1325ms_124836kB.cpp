#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
int n, k, a[N], pre[N], lim[N];
vector<int> loc[N];
multiset<int> ll, rr;
struct node {
  int l, r, mid;
  int cnt, sum;
} p[N << 2];
inline void maintain(int u) {
  if (p[u].cnt) {
    p[u].sum = 0;
  } else {
    p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
  }
}
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  p[u].cnt = 0, p[u].sum = r - l + 1;
  if (l == r) return;
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
}
void modify(int u, int l, int r, int x) {
  // if (u == 1) cerr << "modify " << u << " " << l << " " << r << " " << x << endl;
  if (p[u].l == l && p[u].r == r) {
    p[u].cnt += x;
    if (l == r) {
      p[u].sum = p[u].cnt ? 0 : 1;
    } else {
      maintain(u);
    }
    return;
  }
  if (r <= p[u].mid) {
    modify(u << 1, l, r, x);
  } else if (l > p[u].mid) {
    modify(u << 1 | 1, l, r, x);
  } else {
    modify(u << 1, l, p[u].mid, x);
    modify(u << 1 | 1, p[u].mid + 1, r, x);
  }
  maintain(u);
}
int query(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) return p[u].sum;
  if (r <= p[u].mid) return query(u << 1, l, r);
  if (l > p[u].mid) return query(u << 1 | 1, l, r);
  return query(u << 1, l, p[u].mid) + query(u << 1 | 1, p[u].mid + 1, r);
}
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    pre[i] = loc[a[i]].size() ? loc[a[i]].back() : -1;
    loc[a[i]].push_back(i);
    if (loc[a[i]].size() >= k) {
      lim[i] = loc[a[i]][(int)loc[a[i]].size() - k];
    } else {
      lim[i] = -1;
    }
  }
  long long ans = 0;
  build(1, 1, n);
  auto update = [&](int k, int x) {
    if (~lim[k]) {
      modify(1, ~pre[lim[k]] ? pre[lim[k]] + 1 : 1, lim[k], x);
    }
  };
  for (int i = 1; i <= n; i++) {
    update(i, 1);
    if (~pre[i]) update(pre[i], -1);
    // cerr << i << " :: " << i << "-" << query(1, 1, i) << endl;
    ans += query(1, 1, i);
  }
  cout << ans << endl;
}