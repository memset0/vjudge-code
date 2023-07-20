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
    assert(x != 0 || y != 0);
    return y > 0 || (y == 0 && x < 0);
  }
  constexpr bool side(const Point &p) const {
    assert(x != 0 || y != 0);
    return cross(*this, p) < 0 || (cross(*this, p) == 0 && dot(*this, p) < 0);
  }

  friend constexpr bool operator==(const Point &a, const Point &b) { return a.x == b.x && a.y == b.y; }
  friend constexpr bool operator!=(const Point &a, const Point &b) { return a.x != b.x || a.y != b.y; }
  constexpr Point operator+=(const Point &rhs) { return x += rhs.x, y += rhs.y, *this; }
  constexpr Point operator-=(const Point &rhs) { return x -= rhs.x, y -= rhs.y, *this; }
  friend constexpr Point operator+(const Point &a, const Point &b) { return Point{a.x + b.x, a.y + b.y}; }
  friend constexpr Point operator-(const Point &a, const Point &b) { return Point{a.x - b.x, a.y - b.y}; }
  template <class X> friend inline Point<X, X> operator*(const Point &a, const X &c) { return Point<X, X>{a.x * c, a.y * c}; }
  friend inline Point<double, double> operator/(const Point &a, double c) { return Point<double, double>{a.x / c, a.y / c}; }

  inline Point constexpr perp() { return Point{-y, x}; }
  inline Point<double, double> scale(Point c, double factor) { return Point<double, double>(c) + this->operator-(c) * factor; }
  inline Point<double, double> rotate(double angle) { return Point<double, double>{x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)}; }
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
  template <class W> explicit Segment(const Segment<T, W> &o) { u.x = o.u.x, u.y = o.u.y, v.x = o.v.x, v.y = o.v.y; }
  std::string to_string() const { return '[' + u.to_string() + ',' + v.to_string() + ']'; }

  constexpr Point<T, V> vector() const { return v - u; }
  constexpr bool collinear(const Point<T, V> &o) const { return cross(u - v, o - v) == 0; }
  constexpr bool include(const Point<T, V> &o) const {
    // note: 1. endpoints of the segments are not included
    //       2. if you want to include the endpoint,
    //          you cannot directly change the following line to less than or equal to
    if (!collinear(o)) return false;
    if (u.x != v.x) return (u.x < o.x && o.x < v.x) || (v.x < o.x && o.x < u.x);
    return (u.y < o.y && o.y < v.y) || (v.y < o.y && o.y < u.y);
  }

  friend constexpr bool operator==(const Segment &a, const Segment &b) { return a.u == b.u && a.v == b.v; }
  friend constexpr bool operator!=(const Segment &a, const Segment &b) { return a.u != b.u || a.v != b.v; }

  constexpr double distance(const Point<T, V> &o) const {
    V oa = dot(o - u, v - u), ob = dot(o - v, u - v);
    // std::cerr << oa << " " << ob << " " << cross(o - u, v - u) << " " << cross(o - v, u - v) << std::endl;
    return oa >= 0 && ob >= 0 ? fabs(cross(o - u, v - u)) / (u - v).norm() : std::min((o - u).norm(), (o - v).norm());
  }
};
template <class T, class V> constexpr bool properInter(const Segment<T, V> &a, const Segment<T, V> &b) {
  // note: endpoints of the segments are not included
  V oa = orient(b.u, b.v, a.u), ob = orient(b.u, b.v, a.v);
  V oc = orient(a.u, a.v, b.u), od = orient(a.u, a.v, b.v);
  // proper intersection exists iff opposite signs
  return ((oa > 0 && ob < 0) || (oa < 0 && ob > 0)) && ((oc > 0 && od < 0) || (oc < 0 && od > 0));
}
template <class T, class V> Point<double, double> properInterPoint(const Segment<T, V> &a, const Segment<T, V> &b) {
  V oa = orient(b.u, b.v, a.u), ob = orient(b.u, b.v, a.v);
  return (a.u * (double)ob - a.v * (double)oa) / (ob - oa);
}

template <class T, class V> struct Polygon {
  vector<Point<T, V>> a;
};

#endif

using namespace std;
using pt = Point<double, double>;
using sg = Segment<double, double>;
const double PI = acos(-1);
int T, l1, l2, a, b;
double ans, fa, fb;

inline double cir(int l, double deg = 360) { return (long long)l * l * PI * deg / 360; }

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin >> T;
  cout.flags(ios::fixed);
  pt o{0, 0};
  while (T--) {
    cin >> l1 >> l2 >> a >> b;
    fa = a / 180. * PI;
    fb = b / 180. * PI;
    if (b <= 90) {
      ans = cir(l1 + l2, a << 1) + cir(l2, b << 1);
      cout << setprecision(15) << ans << endl;
    } else {
      ans = cir(l1 + l2, a << 1) + cir(l2, b << 1);
      pt n1{(double)l1, 0}, n2{(double)l2, 0};
      double d = sg{n1, n1 + n2.rotate(fb)}.distance(o);
      double g = acos(d / l1);
      ans += d * l1 * sin(g) / 2 - cir(d, g / PI * 180);
      // cout << "!!!" << setprecision(15) << d << " " << g << " " << g / PI * 180 << endl;
      // cout << "!!!" << setprecision(15) << d * l1 * sin(g) / 2 << " " << cir(d, g / PI * 180) << endl;
      cout << setprecision(15) << ans << endl;
    }
  }
}