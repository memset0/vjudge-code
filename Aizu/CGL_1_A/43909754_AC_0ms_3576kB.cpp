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
  friend inline Node<double, double> operator/(const Node &a, double c) { return Node<double, double>{a.x / c, a.y / c}; }

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
int T;
pt u, v, w, a, b;

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> u.x >> u.y >> v.x >> v.y;
  cin >> T;
  a = v - u;
  long long p = a.square();
  while (T--) {
    cin >> w.x >> w.y;
    b = w - u;
    long long q = dot(a, b);
    Node<double, double> ans = (a * q / (double)p);
    printf("%.10lf %.10lf\n", ans.x + u.x, ans.y + u.y);
  }
}