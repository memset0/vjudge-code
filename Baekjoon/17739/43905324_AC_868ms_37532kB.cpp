#include <bits/stdc++.h>

using std::vector;

#ifndef MEM_GEO_H
#define MEM_GEO_H
template <class T, class V> struct Node {
  T x, y;
  Node() { x = y = 0; }
  explicit Node(T _x, T _y) { x = _x, y = _y; }
  constexpr T real() const { return x; }
  constexpr T imag() const { return y; }
  constexpr V square() const { return (V)x * x + (V)y * y; }
  constexpr double norm() const { return sqrtl(this->square()); }
  constexpr bool side() const {
    // assert(x != 0 || y != 0);
    return y > 0 || (y == 0 && x < 0);
  }
  constexpr bool side(const Node &p) const {
    // assert(x != 0 || y != 0);
    return cross(*this, p) < 0 || (cross(*this, p) == 0 && dot(*this, p) < 0);
  }

  constexpr Node operator+=(const Node &rhs) { x += rhs.x, y += rhs.y; }
  constexpr Node operator-=(const Node &rhs) { x -= rhs.x, y -= rhs.y; }
  friend constexpr Node operator+(const Node &a, const Node &b) { return Node<T, V>{a.x + b.x, a.y + b.y}; }
  friend constexpr Node operator-(const Node &a, const Node &b) { return Node<T, V>{a.x - b.x, a.y - b.y}; }
  template <class X> friend inline Node<X, X> operator*(const Node &a, const X &c) { return Node<X, X>{a.x * c, a.y * c}; }
  friend inline Node<double, double> operator/(const Node &a, double c) { return {a.x / c, a.y / c}; }

  inline Node constexpr perp() { return {-y, x}; }
  inline Node<double, double> scale(Node c, double factor) { return Node<double, double>(c) + this->operator-(c) * factor; }
  inline Node<double, double> rotate(double angle) { return {x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)}; }
};
template <class T, class V> constexpr V dot(const Node<T, V> &a, const Node<T, V> &b) { return (V)a.x * b.x + (V)a.y * b.y; }
template <class T, class V> constexpr V cross(const Node<T, V> &a, const Node<T, V> &b) { return (V)a.x * b.y - (V)a.y * b.x; }
template <class T, class V> constexpr V orient(const Node<T, V> &a, const Node<T, V> &b, const Node<T, V> &c) {
  // orient(a, b, c) > 0: vet(ac) is on the left of vet(ab)
  // orient(a, b, c) = 0: a, b, c is collinear
  // orient(a, b, c) < 0: vet(ac) is on the right of vet(ab)
  return cross(b - a, c - a);
}
template <class T, class V> constexpr bool isPerp(const Node<T, V> &a, const Node<T, V> &b) { return dot(a, b) == 0; }
template <class T, class V> constexpr bool polarCompare(const Node<T, V> &a, const Node<T, V> &b) {
  // to solve cases that vectors are more than 180deg apart in order
  return std::make_tuple(a.side(), (V)0, a.square()) < std::make_tuple(b.side(), cross(a, b), b.square());
}
template <class T, class V> void polarSort(vector<Node<T, V>> &vec) { std::sort(vec.begin(), vec.end(), polarCompare); }
template <class T, class V> void polarSortAround(vector<Node<T, V>> &vec, Node<T, V> o) {
  std::sort(vec.begin(), vec.end(), [&o](const Node<T, V> &a, const Node<T, V> &b) { return polarCompare(a - o, b - o); });
}

#endif

using namespace std;
using pt = Node<int, long long>;
const int N = 3e3 + 9;
int n, pre[N][N];
long long ans;
struct node {
  pt v;
  int id, c;
} a[N], b[N << 1];

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].v.x >> a[i].v.y >> a[i].c;
    a[i].id = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) b[j] = a[j];
    for (int j = i + 1; j <= n; j++) b[j - 1] = a[j];
    const pt &o = a[i].v;
    sort(b + 1, b + n, [&o](const node &a, const node &b) { return polarCompare(a.v - o, b.v - o); });
    for (int j = 1; j < n; j++) b[j + n - 1] = b[j];
    vector<int> cnt(3);
    cnt[b[1].c] = 1;
    for (int l = 1, r = 1; l < n; l++) {
      cnt[b[l].c]--;
      while (r < l || (r + 1 < l + n - 1 && (b[r + 1].v - o).side(b[l].v - o))) {
        ++r;
        cnt[b[r].c]++;
      }
      cnt[a[i].c] = 1;
      pre[i][b[l].id] = cnt[0] * cnt[1] * cnt[2];
      // fprintf(stderr, "i=%d l=%d r=%d :: pre[%d][%d] = %d * %d * %d\n", i, l, r, i, b[l].id, cnt[0], cnt[1], cnt[2]);
    }
  }
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
      if (pre[i][j] && pre[j][i]) {
        ans += (long long)pre[i][j] * pre[j][i];
        // fprintf(stderr, "i=%d j=%d :: ans += %d * %d :: %lld\n", i, j, pre[i][j], pre[j][i], ans);
      }

  // assert(ans % 4 == 0);
  cout << ans << endl;
}