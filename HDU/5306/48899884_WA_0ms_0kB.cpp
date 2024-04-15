#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
const int N = 1e6 + 9;
int T, n, m, a[N];
struct segment {
  int l, r, mid;
  int max, smax, cnt, lazy;
  long long sum;
} p[N << 2];
void maintain(int u) {
  p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
  p[u].max = max(p[u << 1].max, p[u << 1 | 1].max);
  p[u].smax = max(p[u << 1].smax, p[u << 1 | 1].smax);
  if (p[u << 1].max != p[u].max && p[u << 1].max > p[u].smax) p[u].smax = p[u << 1].max;
  if (p[u << 1 | 1].max != p[u].max && p[u << 1 | 1].max > p[u].smax) p[u].smax = p[u << 1 | 1].max;
  p[u].cnt = (p[u].max == p[u << 1].max ? p[u << 1].cnt : 0) + (p[u].max == p[u << 1 | 1].max ? p[u << 1 | 1].cnt : 0);
}
void pushup(int u, int x) {
  p[u].sum -= (long long)p[u].cnt * (p[u].max - x);
  p[u].max = x;
  p[u].lazy = x;
}
void pushdown(int u) {
  if (p[u].lazy != -1) {
    pushup(u << 1, p[u].lazy);
    pushup(u << 1 | 1, p[u].lazy);
    p[u].lazy = -1;
  }
}
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  p[u].lazy = -1;
  if (l == r) {
    p[u].max = a[l];
    p[u].smax = -1;
    p[u].cnt = 1;
    p[u].sum = a[l];
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
  maintain(u);
}
void modify(int u, int l, int r, int x) {
  if (x >= p[u].max) return;
  if (p[u].l == p[u].r) {
    p[u].sum = p[u].max = x;
    return;
  }
  pushdown(u);
  if (p[u].l == l && p[u].r == r && x > p[u].smax) {
    pushup(u, x);
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
int query_max(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) return p[u].max;
  if (r <= p[u].mid) return query_max(u << 1, l, r);
  if (l > p[u].mid) return query_max(u << 1 | 1, l, r);
  return max(query_max(u << 1, l, p[u].mid), query_max(u << 1 | 1, p[u].mid + 1, r));
}
long long query_sum(int u, int l, int r) {
  if (p[u].l == l && p[u].r == r) return p[u].sum;
  if (r <= p[u].mid) return query_sum(u << 1, l, r);
  if (l > p[u].mid) return query_sum(u << 1 | 1, l, r);
  return query_sum(u << 1, l, p[u].mid) + query_sum(u << 1 | 1, p[u].mid + 1, r);
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    build(1, 1, n);
    for (int op, l, r, x, i = 1; i <= m; i++) {
      cin >> op >> l >> r;
      if (op == 0) {
        cin >> x;
        modify(1, l, r, x);
      } else if (op == 1) {
        cout << query_max(1, l, r) << endl;
      } else {
        cout << query_sum(1, l, r) << endl;
      }
    }
  }
}