#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int n, m, a[N];
long long s[N];
struct segment {
  int l, r, mid;
  long long min, max, tag;
} p[N << 2];
void pushup(int u, long long x) {
  p[u].min += x;
  p[u].max += x;
  p[u].tag += x;
}
void pushdown(int u) {
  if (p[u].tag) {
    pushup(u << 1, p[u].tag);
    pushup(u << 1 | 1, p[u].tag);
    p[u].tag = 0;
  }
}
void maintain(int u) {
  p[u].min = min(p[u << 1].min, p[u << 1 | 1].min);
  p[u].max = max(p[u << 1].max, p[u << 1 | 1].max);
}
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  if (l == r) {
    p[u].min = p[u].max = s[l];
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
  maintain(u);
}
void modify(int u, int l, int r, long long x) {
  if (p[u].l == l && p[u].r == r) {
    pushup(u, x);
    return;
  }
  pushdown(u);
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
long long query_min(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) {
    return p[u].min;
  }
  pushdown(u);
  if (r <= p[u].mid) return query_min(u << 1, l, r);
  if (l > p[u].mid) return query_min(u << 1 | 1, l, r);
  return min(query_min(u << 1, l, p[u].mid), query_min(u << 1 | 1, p[u].mid + 1, r));
}
long long query_max(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) {
    return p[u].max;
  }
  pushdown(u);
  if (r <= p[u].mid) return query_max(u << 1, l, r);
  if (l > p[u].mid) return query_max(u << 1 | 1, l, r);
  return max(query_max(u << 1, l, p[u].mid), query_max(u << 1 | 1, p[u].mid + 1, r));
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    s[i] = s[i - 1] + a[i];
  }
  // for (int i = 1; i <= n; i++) cerr << s[i] << " \n"[i == n];
  build(1, 0, n);
  string op;
  for (int k, x, l1, l2, r1, r2, i = 1; i <= m; i++) {
    cin >> op;
    if (op[0] == 's') {
      cin >> k >> x;
      modify(1, k, n, x - a[k]);
      a[k] = x;
    } else {
      cin >> l1 >> l2 >> r1 >> r2;
      // cerr << "! " << query_max(1, r1, r2) << " - " << query_min(1, l1 - 1, l2 - 1) << endl;
      cout << query_max(1, r1, r2) - query_min(1, l1 - 1, l2 - 1) << endl;
    }
  }
}