#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
const double eps = 1e-10;
const double eps2 = 1e-13;
const double PI = acos(-1.0);

struct Point {
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
};
typedef Point Vector;

Vector operator-(Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator+(Point a, Point b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator*(Vector a, double p) { return Vector(a.x * p, a.y * p); }
Vector operator/(Vector a, double p) { return Vector(a.x / p, a.y / p); }
bool operator<(const Point &a, const Point &b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y); // 在有精度需求，比如使用lower_bound的时候，加上dcmp()
}
int dcmp(double x) {
  if (fabs(x) < eps) return 0;
  if (x < 0) return -1;
  return 1;
}
bool operator==(const Point &a, const Point &b) { return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0; }
double Dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }   // 点积
double Cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; } // 叉积
double Length(Vector a) { return sqrt(Dot(a, a)); }                // 长度
// 返回逆时针旋转90度的单位法向量；
Vector Normal(Vector a) {
  double l = Length(a);
  return Vector(-a.y / l, a.x / l);
}
// 返回向量夹角，无方向
double Angle(Vector a, Vector b) { return acos(Dot(a, b) / Length(a) / Length(b)); }
// 逆时针旋转向量
Vector Rotate(Vector a, double rad) { return Vector(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad)); }
// 求p+v*t与q+w*t的交点，使用时确保Cross(v,w)不等于0
Point GetlineIntersection(Point p, Vector v, Point q, Vector w) {
  Vector u = p - q;
  double t = Cross(w, u) / Cross(v, w);
  return p + v * t;
}
// 求p到直线ab的距离
double DistanceToline(Point p, Point a, Point b) {
  Vector v1 = p - a, v2 = b - a;
  return fabs(Cross(v1, v2) / Length(v2));
}
// 求p到线段ab的距离
double DistanceToSegment(Point p, Point a, Point b) {
  if (a == b) return Length(p - a);
  Vector v1 = b - a, v2 = p - a, v3 = p - b;
  if (dcmp(Dot(v1, v2) < 0)) return Length(p - a);
  else if (dcmp(Dot(v1, v3)) > 0)
    return Length(p - b);
  else
    return fabs(Cross(v1, v2) / Length(v1));
}
// 线段a1a2与线段b1b2规范相交返回真
bool SegmenProperIntersection(Point a1, Point a2, Point b1, Point b2) {
  double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
  double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
  return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
// 点p在线段a1a2上返回真
bool OnSegment(Point p, Point a1, Point a2) { return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0; }
// 点p在ab上的投影
Point GetLineProjection(Point P, Point A, Point B) {
  Vector v = B - A;
  return A + v * (Dot(v, P - A) / Dot(v, v));
}
// 与 x 轴的夹角，取值范围为 (-π，π]
double angle(Vector v) { return atan2(v.y, v.x); }
// 求线段a1,a2到线段b1,b2的最短距离
double disSegmenttoSegment(Point a1, Point a2, Point b1, Point b2) {
  double ans = DistanceToSegment(a1, b1, b2);
  ans = min(ans, DistanceToSegment(a2, b1, b2));
  ans = min(ans, DistanceToSegment(b1, a1, a2));
  ans = min(ans, DistanceToSegment(b2, a1, a2));
  return ans;
}
// 返回单位向量；
Vector normal(Vector a) {
  double l = Length(a);
  return Vector(a.x / l, a.y / l);
}
int ConvecHull(Point *p, int n, Point *ch) {
  sort(p, p + n);
  int m = 0;
  for (int i = 0; i < n; i++) {
    while (m > 1 && dcmp(Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)) m--; // 注意<=与<的区别
    ch[m++] = p[i];
  }
  int k = m;
  for (int i = n - 2; i >= 0; i--) {
    while (m > k && dcmp(Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)) m--; // 注意<=与<的区别
    ch[m++] = p[i];
  }
  if (n > 1) m--;
  return m;
}

int n, m;
Point p[20], ch[20], g, s;
Point seg[1000], k;
Point r[1000];
Point q, nq;
int pos, np, rnum, cnt;
double getangle() {
  double l = 0, rf = PI, mf;
  Point ro[20], rg;
  if (cos(angle(g - q)) >= 0) return 0;
  while ((rf - l) > eps2) {
    mf = (l + rf) / 2;
    for (int i = 0; i < m; i++) {
      ro[i] = Rotate(ch[i] - q, mf) + q;
    }
    if (cos(angle(g - q) + mf) >= 0) {
      rf = mf;
      continue;
    }
    bool flag = false;
    for (int i = 0; i < m; i++) {
      if (ch[i] == q) continue;
      for (int j = 0; j < cnt; j++) {
        if (Cross(r[j + 1] - r[j], ro[i] - r[j]) < 0) {
          rf = mf;
          flag = true;
          break;
        }
      }
      if (flag) break;
    }
    if (!flag) {
      l = mf;
    }
  }
  return mf;
}
double getangle2() {
  double l = 0, rf = -PI, mf;
  Point ro[20], rg;
  if (cos(angle(g - q)) <= 0) return 0;
  while ((l - rf) > eps2) {
    mf = (l + rf) / 2;
    for (int i = 0; i < m; i++) {
      ro[i] = Rotate(ch[i] - q, mf) + q;
    }
    if (cos(angle(g - q) + mf) <= 0) {
      rf = mf;
      continue;
    }
    bool flag = false;
    for (int i = 0; i < m; i++) {
      if (ch[i] == q) continue;
      for (int j = 0; j < cnt; j++) {
        if (Cross(r[j + 1] - r[j], ro[i] - r[j]) < 0) {
          rf = mf;
          flag = true;
          break;
        }
      }
      if (flag) break;
    }
    if (!flag) {
      l = mf;
    }
  }
  return mf;
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    cin >> g.x >> g.y;
    s = g;
    cnt = 0;
    while (cin >> seg[cnt].x >> seg[cnt].y) {
      cnt++;
      if (dcmp(seg[cnt - 1].y) == 0) break;
    }
    cin >> k.x >> k.y;
    m = ConvecHull(p, n, ch);
    r[cnt] = k;
    for (int i = 0; i < cnt; i++) {
      Vector v = normal(Vector(1, seg[i].y));
      v = v * seg[i].x;
      r[cnt - i - 1] = r[cnt - i] - v;
    }
    q.x = 999999999;
    for (int i = 0; i < m; i++) {
      bool flag = false;
      for (int j = 0; j < cnt; j++) {
        if (dcmp(DistanceToSegment(ch[i], r[j], r[j + 1])) == 0) {
          if (ch[i].x < q.x) q = ch[i];
        }
      }
    }
    double ag1 = getangle();  // 左边
    double ag2 = getangle2(); // 右边
    bool f;
    if (fabs(ag1) > fabs(ag2)) {
      f = true;
    } else
      f = false;
    while (true) {
      if (f) q.x = 999999999;
      else
        q.x = -999999999;
      for (int i = 0; i < m; i++) {
        bool flag = false;
        for (int j = 0; j < cnt; j++) {
          if (dcmp(DistanceToSegment(ch[i], r[j], r[j + 1])) == 0) {
            if (f && ch[i].x < q.x) q = ch[i];
            if (!f && ch[i].x > q.x) q = ch[i];
          }
        }
      }
      double ag;
      if (f) ag = getangle();
      else
        ag = getangle2();
      Point o = q;
      for (int i = 0; i < m; i++) {
        ch[i] = Rotate(ch[i] - o, ag) + o;
      }
      g = Rotate(g - o, ag) + o;
      if (dcmp(ag) == 0) break;
    }
    printf("%.3f %.3f\n", g.x, g.y);
  }
  return 0;
}