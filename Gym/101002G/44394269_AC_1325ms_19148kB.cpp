#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 1e3 + 9;
int n;

struct point {
  int x, y;
  inline point operator/(int k) const { return {x / k, y / k}; }
  inline point operator+(const point &rhs) const { return {x + rhs.x, y + rhs.y}; }
  inline point operator-(const point &rhs) const { return {x - rhs.x, y - rhs.y}; }
  inline bool operator<(const point &rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
  inline bool operator==(const point &rhs) const { return x == rhs.x && y == rhs.y; }
  inline bool operator!=(const point &rhs) const { return x != rhs.x || y != rhs.y; }
} a[N];

struct segment {
  point b, k;
  inline bool contain(const point &u) const {
    return (long long)k.x * (b.y - u.y) == // endl
           (long long)k.y * (b.x - u.x);
  }

  inline bool operator<(const segment &rhs) const {
    if (k == rhs.k) {
      if (k.x == 0) return b.x < rhs.b.x;
      if (k.y == 0) return b.y < rhs.b.y;
      // by - bx * ky / kx
      return ((long long)b.y * k.x - (long long)b.x * k.y) * rhs.k.x < // endl
             ((long long)rhs.b.y * rhs.k.x - (long long)rhs.b.x * rhs.k.y) * k.x;
    }
    return k < rhs.k;
  }
  friend inline bool operator==(const segment &a, const segment &b) { return !(a < b) && !(b < a); }
  friend inline bool operator!=(const segment &a, const segment &b) { return (a < b) || (b < a); }
};
inline segment to_segment(const point &a, const point &b) {
  point k = a - b;
  int g = __gcd(k.x, k.y);
  k.x /= g;
  k.y /= g;
  if (k.x < 0) {
    k.x *= -1, k.y *= -1;
  }
  return {b, k};
}

int main() {
#ifdef memset0
  freopen("G.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  rep(i, 1, n) {
    cin >> a[i].x >> a[i].y;
    a[i].x <<= 1;
    a[i].y <<= 1;
  }
  int ans = n;
  vector<pair<point, bool>> cp;
  vector<segment> cg;
  rep(i, 1, n) { cp.emplace_back(a[i], true); }
  rep(i, 1, n) rep(j, i + 1, n) {
    point c = (a[i] + a[j]) / 2;
    cp.emplace_back(c, false);
    point k = (a[i] - a[j]) / 2;
    swap(k.x, k.y), k.y *= -1;
    cg.push_back(to_segment(c + k, c));
    // fprintf(stderr, "i=%d j=%d :: %d %d :: %d %d %d %d\n", i, j, c.x, c.y, cg.back().k.x, cg.back().k.y, cg.back().b.x, cg.back().b.y);
  }
  sort(cp.begin(), cp.end());
  sort(cg.begin(), cg.end());
  // cerr << "! " << ans << endl;
  for (int l = 0, r; l < cp.size(); l = r + 1) {
    r = l;
    while (r + 1 < cp.size() && cp[r + 1].first == cp[r].first) ++r;
    int sum = 0;
    for (int i = l; i <= r; i++) {
      sum += cp[i].second ? 1 : 2;
    }
    ans = min(ans, n - sum);
  }
  // cerr << "! " << ans << endl;
  for (int l = 0, r; l < cg.size(); l = r + 1) {
    r = l;
    while (r + 1 < cg.size() && cg[r + 1] == cg[r]) ++r;
    int sum = (r - l + 1) << 1;
    for (int i = 1; i <= n; i++)
      if (cg[l].contain(a[i])) {
        ++sum;
      }
    // fprintf(stderr, "l=%d r=%d sum=%d %d\n", l, r, sum, ans);
    // for (int i = l; i <= r; i++) {
    //   auto it = cg[i];
    //   cerr << it.k.x << " " << it.k.y << " " << it.b.x << " " << it.b.y << endl;
    // }
    ans = min(ans, n - sum);
  }
  rep(i, 1, n) rep(j, i + 1, n) {
    segment x = to_segment(a[i], a[j]);
    int sum = 0;
    rep(k, 1, n) if (x.contain(a[k])) sum++;
    // cerr << i << " " << j << " " << sum << endl;
    ans = min(ans, n - sum);
  }
  assert(ans >= 0);
  cout << ans << endl;
}