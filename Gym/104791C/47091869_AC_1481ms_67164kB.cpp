#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 5e5 + 1009;
int T, n, m, k;
char s[N];
struct node {
  int l, lv, r, rv;
  node operator+(node const a) {
    node c = {0, 0, 0, 0};
    if (lv <= a.l) {
      c.l = l + (a.l - lv);
      c.lv = a.lv;
      if (c.l > r) c.l = n;
    } else {
      c.l = l;
      c.lv = min(a.lv + lv - a.l, a.rv);
    }
    if (rv >= a.r) {
      c.r = r - (rv - a.r);
      c.rv = a.rv;
      if (c.r < l) c.r = 1;
    } else {
      c.r = r;
      c.rv = max(a.rv - (a.r - rv), a.lv);
    }
    if (c.l >= c.r) c.l = 1, c.r = 2;
    return c;
  }
};
struct Seg {
  int v[N];
  node val[N << 2];
  void build(int p, int L, int R) {
    if (L == R) {
      if (v[L] == -1) val[p] = {2, 1, n, n - 1};
      else if (v[L] == 0)
        val[p] = {1, 1, n, n};
      else if (v[L] == 1)
        val[p] = {1, 2, n - 1, n};
      return;
    }
    int mid = L + R >> 1;
    build(p << 1, L, mid);
    build(p << 1 | 1, mid + 1, R);
    val[p] = val[p << 1] + val[p << 1 | 1];
  }
  void change(int p, int L, int R, int x) {
    if (L == R) {
      if (v[L] == -1) val[p] = {2, 1, n, n - 1};
      else if (v[L] == 0)
        val[p] = {1, 1, n, n};
      else if (v[L] == 1)
        val[p] = {1, 2, n - 1, n};
      return;
    }
    int mid = L + R >> 1;
    if (mid >= x) change(p << 1, L, mid, x);
    else
      change(p << 1 | 1, mid + 1, R, x);
    val[p] = val[p << 1] + val[p << 1 | 1];
  }
  node query(int p, int L, int R, int l, int r) {
    if (l <= L && R <= r) return val[p];
    int mid = L + R >> 1;
    if (mid >= l && mid < r) return query(p << 1, L, mid, l, r) + query(p << 1 | 1, mid + 1, R, l, r);
    else if (mid >= l)
      return query(p << 1, L, mid, l, r);
    else
      return query(p << 1 | 1, mid + 1, R, l, r);
  }
} X, Y;
int query(node X, int x) {
  if (n == 1) return 1;
  if (x <= X.l) return X.lv;
  if (x >= X.r) return X.rv;
  return X.lv + x - X.l;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
      cin >> s[i];
      X.v[i] = Y.v[i] = 0;
      if (s[i] == 'U') X.v[i] = -1;
      else if (s[i] == 'D')
        X.v[i] = 1;
      if (s[i] == 'L') Y.v[i] = -1;
      else if (s[i] == 'R')
        Y.v[i] = 1;
    }
    X.build(1, 1, m);
    Y.build(1, 1, m);
    for (int i = 1; i <= k; i++) {
      int opt;
      cin >> opt;
      if (opt == 1) {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        node xx = X.query(1, 1, m, l, r);
        node yy = Y.query(1, 1, m, l, r);
        cout << query(xx, x) << " " << query(yy, y) << endl;
      } else {
        int x;
        cin >> x;
        X.v[x] = 0;
        Y.v[x] = 0;
        cin >> s[x];
        if (s[x] == 'U') X.v[x] = -1;
        else if (s[x] == 'D')
          X.v[x] = 1;
        if (s[x] == 'L') Y.v[x] = -1;
        else if (s[x] == 'R')
          Y.v[x] = 1;
        X.change(1, 1, m, x);
        Y.change(1, 1, m, x);
      }
    }
  }
}