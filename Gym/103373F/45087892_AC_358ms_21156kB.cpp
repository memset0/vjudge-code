#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
using pii = pair<int, int>;
const int N = 2e5 + 9;
int n, m, a[N];
long long s[N];
void add(int k, long long x) {
  for (; k < N; k += k & -k) s[k] += x;
}
long long ask(int k) {
  long long r = 0;
  for (; k; k -= k & -k) r += s[k];
  return r;
}
long long calc(int l, int r) {
  // cerr << "CALC " << l << " " << r << endl;
  return (long long)(r - l + 1) * (r - l + 2) / 2;
}
struct segment {
  int l, r, mid;
  pii w;
  bool x;
} p[N << 2];
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  if (l == r) {
    p[u].x = a[l];
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
}
void modify_rev(int u, int l, int r) {
  // fprintf(stderr, "modify rev %d %d %d\n", u, l, r);
  if (p[u].l == l && p[u].r == r) {
    p[u].x ^= 1;
    return;
  }
  if (r <= p[u].mid) {
    modify_rev(u << 1, l, r);
  } else if (l > p[u].mid) {
    modify_rev(u << 1 | 1, l, r);
  } else {
    modify_rev(u << 1, l, p[u].mid);
    modify_rev(u << 1 | 1, p[u].mid + 1, r);
  }
}
void modify(int u, int l, int r, const pii &w) {
  // fprintf(stderr, "modify %d %d %d [%d %d]\n", u, l, r, w.first, w.second);
  if (p[u].l == l && p[u].r == r) {
    p[u].w = w;
    return;
  }
  if (p[u].w.first) {
    p[u << 1].w = p[u].w;
    p[u << 1 | 1].w = p[u].w;
    p[u].w = {0, 0};
  }
  if (r <= p[u].mid) {
    modify(u << 1, l, r, w);
  } else if (l > p[u].mid) {
    modify(u << 1 | 1, l, r, w);
  } else {
    modify(u << 1, l, p[u].mid, w);
    modify(u << 1 | 1, p[u].mid + 1, r, w);
  }
}
bool query_bit(int u, int k) {
  if (p[u].l == p[u].r) {
    return p[u].x;
  }
  if (k <= p[u].mid) {
    return p[u].x ^ query_bit(u << 1, k);
  } else {
    return p[u].x ^ query_bit(u << 1 | 1, k);
  }
}
pii query_range(int u, int k) {
  // fprintf(stderr, "query range %d %d [%d %d] [%d %d]\n", u, k, p[u].l, p[u].r, p[u].w.first, p[u].w.second);
  if (p[u].w.first) {
    return p[u].w;
  }
  if (k <= p[u].mid) {
    return query_range(u << 1, k);
  } else {
    return query_range(u << 1 | 1, k);
  }
}
void push(int l, int r) {
  // cerr << "PUSH " << l << " " << r << endl;
  modify(1, l, r, {l, r});
  // for (int i = l; i <= r; i++) {
  //   assert(make_pair(l, r) == query_range(1, i));
  // }
  add(r, calc(l, r));
}
void pop(int l, int r) {
  // cerr << "POP " << l << " " << r << endl;
  add(r, -calc(l, r));
}
void link(int m) {
  // cerr << "LINK " << m << endl;
  pii ll = query_range(1, m);
  pii rr = query_range(1, m + 1);
  pop(ll.first, ll.second);
  pop(rr.first, rr.second);
  push(ll.first, rr.second);
}
void cut(int m) {
  // cerr << "CUT " << m << endl;
  pii it = query_range(1, m);
  pop(it.first, it.second);
  push(it.first, m);
  push(m + 1, it.second);
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  build(1, 1, n);
  for (int l = 1, r; l <= n; l = r + 1) {
    r = l;
    while (r + 1 <= n && a[r + 1] != a[r]) {
      ++r;
    }
    push(l, r);
  }
  // for (int i = 1; i <= n; i++) cerr << ask(i) << " \n"[i == n];
  for (int op, l, r, i = 1; i <= m; i++) {
    cin >> op >> l >> r;
    // cerr << ">>> " << op << " " << l << " " << r << endl;
    if (op == 1) {
      modify_rev(1, l, r);
      // for (int i = l; i <= r; i++) {
      //   a[i] ^= 1;
      //   assert(a[i] == query_bit(1, i));
      // }
      if (l > 1) {
        bool x = query_bit(1, l - 1);
        bool y = query_bit(1, l);
        x == y ? cut(l - 1) : link(l - 1);
      }
      if (r < n) {
        bool x = query_bit(1, r);
        bool y = query_bit(1, r + 1);
        x == y ? cut(r) : link(r);
      }
    } else {
      long long ans = ask(r) - ask(l - 1);
      // cerr << "! ans[0] = " << ans << endl;
      auto it = query_range(1, l);
      if (it.second <= r) {
        ans -= calc(it.first, it.second);
        ans += calc(l, it.second);
      }
      // cerr << "! ans[1] = " << ans<< endl;
      if (r < n) {
        it = query_range(1, r + 1);
        if (it.first <= r) ans += calc(max(l, it.first), r);
      }
      cout << ans << endl;
    }
  }
}////