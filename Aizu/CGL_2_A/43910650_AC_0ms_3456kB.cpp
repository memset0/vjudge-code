#include <bits/stdc++.h>

using std::vector;

#ifndef MEM_GEO_H
#define MEM_GEO_H

template <class T, class V> struct Point {
  T x, y;
  Point() {}
  explicit Point(T _x, T _y) { x = _x, y = _y; }
  template <class W> explicit Point(const Point<T, W> &o) { x = o.x, y = o.y; }
  std::string to_string() const { return '(' + std::to_string(x) + ',' + std::to_string(y) + ')'; }

  constexpr T real() const { return x; }
  constexpr T imag() const { return y; }
  constexpr V square() const { return (V)x * x + (V)y * y; }
  constexpr double norm() const { return sqrtl(this->square()); }
  constexpr bool side() const {
    // assert(x != 0 || y != 0);
    return y > 0 || (y == 0 && x < 0);
  }
  constexpr bool side(const Point &p) const {
    // assert(x != 0 || y != 0);
    return cross(*this, p) < 0 || (cross(*this, p) == 0 && dot(*this, p) < 0);
  }

  constexpr Point operator+=(const Point &rhs) { return x += rhs.x, y += rhs.y, *this; }
  constexpr Point operator-=(const Point &rhs) { return x -= rhs.x, y -= rhs.y, *this; }
  friend constexpr Point operator+(const Point &a, const Point &b) { return Point{a.x + b.x, a.y + b.y}; }
  friend constexpr Point operator-(const Point &a, const Point &b) { return Point{a.x - b.x, a.y - b.y}; }
  template <class X> friend inline Point<X, X> operator*(const Point &a, const X &c) { return Point<X, X>{a.x * c, a.y * c}; }
  friend inline Point<double, double> operator/(const Point &a, double c) { return Point<double, double>{a.x / c, a.y / c}; }

  inline Point constexpr perp() { return Point{-y, x}; }
  inline Point<double, double> scale(Point c, double factor) { return Point<double, double>(c) + this->operator-(c) * factor; }
  inline Point<double, double> rotate(double angle) { return {x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)}; }
};
template <class T, class V> constexpr V dot(const Point<T, V> &a, const Point<T, V> &b) { return (V)a.x * b.x + (V)a.y * b.y; }
template <class T, class V> constexpr V cross(const Point<T, V> &a, const Point<T, V> &b) { return (V)a.x * b.y - (V)a.y * b.x; }
template <class T, class V> constexpr V orient(const Point<T, V> &a, const Point<T, V> &b, const Point<T, V> &c) {
  // vet(ac) is on the left of vet(ab)   iff orient(a, b, c) > 0
  // a, b, c is collinear                iff orient(a, b, c) = 0
  // vet(ac) is on the right of vet(ab)  iff orient(a, b, c) < 0
  return cross(b - a, c - a);
}
template <class T, class V> constexpr bool isPerp(const Point<T, V> &a, const Point<T, V> &b) { return dot(a, b) == 0; }
template <class T, class V> constexpr bool polarCompare(const Point<T, V> &a, const Point<T, V> &b) {
  // to solve cases that vectors are more than 180deg apart in order
  return std::make_tuple(a.side(), (V)0, a.square()) < std::make_tuple(b.side(), cross(a, b), b.square());
}
template <class T, class V> void polarSort(vector<Point<T, V>> &vec) { std::sort(vec.begin(), vec.end(), polarCompare); }
template <class T, class V> void polarSortAround(vector<Point<T, V>> &vec, Point<T, V> o) {
  std::sort(vec.begin(), vec.end(), [&o](const Point<T, V> &a, const Point<T, V> &b) { return polarCompare(a - o, b - o); });
}

template <class T, class V> struct Segment {
  Point<T, V> u, v;
  Segment() {}
  explicit Segment(const Point<T, V> &_u, const Point<T, V> &_v) { u = _u, v = _v; }
  std::string to_string() const { return '[' + u.to_string() + ',' + v.to_string() + ']'; }

  constexpr Point<T, V> vector() const { return v - u; }
  constexpr bool collinear(const Point<T, V> &o) const { return cross(u - v, o - v) == 0; }
};
template <class T, class V> constexpr bool properInter(const Segment<T, V> &a, const Segment<T, V> &b) {
  V oa = orient(b.u, b.v, a.u), ob = orient(b.u, b.v, a.v);
  V oc = orient(a.u, a.v, b.u), od = orient(a.u, a.v, b.v);
  // proper intersection exists iff opposite signs
  // note that endpoints of the segments are not included
  return ((oa > 0 && ob < 0) || (oa < 0 && ob > 0)) && ((oc > 0 && od < 0) || (oc < 0 && od > 0));
}
template <class T, class V> Point<double, double> properInterPoint(const Segment<T, V> &a, const Segment<T, V> &b) {
  V oa = orient(b.u, b.v, a.u), ob = orient(b.u, b.v, a.v);
  return (a.u * (double)ob - a.v * (double)oa) / (ob - oa);
}

#endif

using namespace std;
using pt = Point<int, long long>;
using sg = Segment<int, long long>;
int T;
pt p0, p1, p2, p3;
sg s1, s2;

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
    s1 = sg{p0, p1}, s2 = sg{p2, p3};
    if (cross(s1.vector(), s2.vector()) == 0) {
      cout << 2 << endl;
    } else if (cross(s1.vector().perp(), s2.vector()) == 0) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
  }
}