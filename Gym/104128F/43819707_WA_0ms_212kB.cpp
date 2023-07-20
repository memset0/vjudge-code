#include <bits/stdc++.h>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;
const int L = 1e9;
int n, m;
pii a, b, c, d, e, f, g, h, i, j;
vector<tuple<pii, pii, pii>> tri;
inline pii middle(const pii &a, const pii &b) { return make_pair((a.x + b.x) >> 1, (a.y + b.y) >> 1); }
inline int abs(int x) { return x < 0 ? -x : x; }
inline int mindis(const tuple<pii, pii, pii> &it) {
  auto [a, b, c] = it;
  return min({abs(a.x - b.x), abs(a.x - c.x), abs(b.x - c.x), abs(a.y - b.y), abs(b.y - c.y), abs(a.y - c.y)});
}
inline long long distance2(pii a, pii b) { return (long long)(a.x - b.x) * (a.x - b.x) + (long long)(a.y - b.y) * (a.y - b.y); }
inline int findmax() {
  int mv = -1;
  int mk = -1;
  for (int i = 0; i < tri.size(); i++) {
    int vv = mindis(tri[i]);
    if (vv > mv) {
      mv = vv;
      mk = i;
    }
  }
  return mk;
}
void solve8() {
  tri.emplace_back(c, middle(c, d), e);
  tri.emplace_back(d, middle(c, d), f);
  tri.emplace_back(middle(c, d), e, f);
}
void solve10() {
  tri.emplace_back(c, e, i);
  tri.emplace_back(e, i, g);
  tri.emplace_back(i, middle(i, d), g);
  tri.emplace_back(d, middle(i, d), f);
  tri.emplace_back(middle(i, d), g, f);
}
void solve12() {
  tri.emplace_back(c, e, i);
  tri.emplace_back(e, i, g);
  tri.emplace_back(d, f, j);
  tri.emplace_back(f, j, g);
  tri.emplace_back(i, middle(i, j), g);
  tri.emplace_back(j, middle(i, j), h);
  tri.emplace_back(middle(i, j), i, j);
}
const int F = 4e4;
const int G = 1e7;
int main() {
#ifdef memset0
  freopen("F.in", "r", stdin);
#endif
  cin >> n;
  if (n < 8 || n == 9) {
    cout << "No" << endl;
    return 0;
  }
  a = make_pair(0, 0);
  b = make_pair(0, L);
  c = make_pair(L, 0);
  d = make_pair(L, L);
  e = make_pair(L - F, G);
  f = make_pair(L - F, L - G);
  g = make_pair(e.x, e.y + (G << 2));
  h = make_pair(f.x, f.y - (G << 2));
  i = make_pair(c.x, c.y + (G << 2));
  j = make_pair(d.x, d.y - (G << 2));
  fprintf(stderr, "%lf\n", (double)distance2(middle(a, c), e) / 5e8 / 5e8);
  assert(distance2(middle(a, c), e) >= (long long)5e8 * 5e8);
  tri.emplace_back(a, c, e);
  tri.emplace_back(b, d, f);
  tri.emplace_back(a, middle(a, b), e);
  tri.emplace_back(b, middle(a, b), f);
  tri.emplace_back(middle(a, b), e, f);
  if (n % 3 == 0) solve12(), m = 12;
  if (n % 3 == 1) solve10(), m = 10;
  if (n % 3 == 2) solve8(), m = 8;
  for (auto [a, b, c] : tri) {
    cerr << a.x << " " << a.y << " " << b.x << " " << b.y << " " << c.x << " " << c.y << endl;
  }
  while (m < n) {
    int k = findmax();
    auto [a, b, c] = tri[k];
    pii d = middle(a, b);
    pii e = middle(a, c);
    pii f = middle(b, c);
    tri[k] = make_tuple(d, e, f);
    tri.push_back(make_tuple(a, d, e));
    tri.push_back(make_tuple(b, d, f));
    tri.push_back(make_tuple(c, e, f));
    m += 3;
  }
  cout << "Yes" << endl;
  for (auto [a, b, c] : tri) {
    cout << a.x << " " << a.y << " " << b.x << " " << b.y << " " << c.x << " " << c.y << endl;
    // cout << "Polygon" << endl;
    // cout << a.x << " " << a.y << endl;
    // cout << b.x << " " << b.y << endl;
    // cout << c.x << " " << c.y << endl;
  }
}