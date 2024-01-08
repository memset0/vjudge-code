#include <bits/stdc++.h>
#ifndef memset0
#define endl '\n'
#endif
using namespace std;
using ll = long long;
using lf = long double;
const int N = 5e3 + 9;
const lf pi = acosl(-1.0);
int n, q;
template <class T> inline void updmax(T &x, const T &y) {
  if (y > x) x = y;
}
template <class T> inline void updmin(T &x, const T &y) {
  if (y < x) x = y;
}
struct point {
  ll x, y;
  friend inline point operator+(const point &a, const point &b) { return {a.x + b.x, a.y + b.y}; }
  friend inline point operator-(const point &a, const point &b) { return {a.x - b.x, a.y - b.y}; }
} a[N];
ll dot(const point &a, const point &b) { return a.x * b.x + a.y * b.y; }
ll cross(const point &a, const point &b) { return a.x * b.y - a.y * b.x; }
ll orient(const point &a, const point &b, const point &c) { return cross(b - a, c - a); }
lf abs(const point &a) { return hypotl(a.x, a.y); }
lf dis(const point &a, const point &b) { return abs(a - b); }
struct segment {
  point v, x, y;
  ll c;
  segment() {}
  segment(const point &p, const point &q) : v(q - p), x(p), y(q), c(cross(v, p)) {}
  bool cmpProj(const point &p, const point &q) { return dot(v, p) < dot(v, q); }
  ll side(const point &p) { return cross(v, p) - c; }
  lf dist(const point &p) { return abs(side(p)) / abs(v); }
} s[N];
lf sqr(lf x) { return x * x; }
lf calc(lf r, lf t) { return r * r / 2 + t * t; }
// lf calc(lf r, lf t) { return 1 + sqr(t / r); }
lf solve(const point &u, const point &v) {
  point o;
  o.x = (u.x + v.x) >> 1;
  o.y = (u.y + v.y) >> 1;
  lf r = dis(u, v) / 2;
  bool hasPos = false, hasNeg = false;
  for (int i = 1; i <= n; i++) {
    ll w = orient(a[i], a[i % n + 1], o);
    if (w > 0) hasPos = true;
    if (w < 0) hasNeg = true;
  }
  // cerr << "haspos = " << hasPos << " :: hasneg = " << hasNeg << endl;
  if (!(hasPos && hasNeg)) return calc(r, 0);
  lf t = dis(o, a[1]);
  for (int i = 2; i <= n; i++) updmin(t, dis(o, a[i]));
  // fprintf(stderr, "t = %.12Lf\n", t);
  for (int i = 1; i <= n; i++) {
    // fprintf(stderr, "i=%d :: %d %d\n", i, s[i].cmpProj(a[i], o), s[i].cmpProj(o, a[i % n + 1]));
    if (s[i].cmpProj(s[i].x, o) && s[i].cmpProj(o, s[i].y)) {
      updmin(t, s[i].dist(o));
    }
  }
  // fprintf(stderr, "t = %.12Lf r = %.12Lf\n", t, r);
  return calc(r, t);
}
int main() {
#ifdef memset0
  freopen("K.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
    a[i].x <<= 1, a[i].y <<= 1;
  }
  for (int i = 1; i <= n; i++) {
    s[i] = segment(a[i], a[i % n + 1]);
  }
  point u, v;
  for (int i = 1; i <= q; i++) {
    cin >> u.x >> u.y >> v.x >> v.y;
    u.x <<= 1, u.y <<= 1, v.x <<= 1, v.y <<= 1;
    // cerr << "solve " << u.x << " " << u.y << " " << v.x << " " << v.y << endl;
    cout << fixed << setprecision(12) << (solve(u, v) / 4) << endl;
  }
}