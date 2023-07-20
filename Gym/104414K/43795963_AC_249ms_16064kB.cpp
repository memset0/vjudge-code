#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int n, q, op, l, r, k, h[N];
struct Segment {
  int l, r, mid;
  long long v, sum, ans;
} p[N << 2];
inline void maintain(int u) {
  p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
  p[u].ans = p[u << 1].ans + p[u << 1 | 1].ans;
}
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  if (l == r) {
    p[u].v = h[l + 1] - h[l];
    p[u].sum = p[u].v;
    p[u].ans = p[u].v > 0 ? p[u].v : 0;
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
  maintain(u);
}
void update(int u, int k, int x) {
  if (p[u].l == p[u].r) {
    p[u].v += x;
    p[u].sum = p[u].v;
    p[u].ans = p[u].v > 0 ? p[u].v : 0;
    return;
  }
  if (k <= p[u].mid) {
    update(u << 1, k, x);
  } else {
    update(u << 1 | 1, k, x);
  }
  maintain(u);
}
long long query_sum(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) return p[u].sum;
  if (r <= p[u].mid) {
    return query_sum(u << 1, l, r);
  } else if (l > p[u].mid) {
    return query_sum(u << 1 | 1, l, r);
  } else {
    return query_sum(u << 1, l, p[u].mid) + query_sum(u << 1 | 1, p[u].mid + 1, r);
  }
}
long long query_ans(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) return p[u].ans;
  if (r <= p[u].mid) {
    return query_ans(u << 1, l, r);
  } else if (l > p[u].mid) {
    return query_ans(u << 1 | 1, l, r);
  } else {
    return query_ans(u << 1, l, p[u].mid) + query_ans(u << 1 | 1, p[u].mid + 1, r);
  }
}
int main() {
#ifdef memset0
  freopen("K.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> h[i];
  build(1, 0, n);
  // cerr << "!" << endl;
  while (q--) {
    cin >> op >> l >> r;
    if (op == 1) {
      cin >> k;
      update(1, l - 1, k);
      update(1, r, -k);
    } else {
      long long ans = query_sum(1, 0, l - 1);
      if (l < r) {
        ans += query_ans(1, l, r - 1);
      }
      cout << ans << endl;
    }
  }
}