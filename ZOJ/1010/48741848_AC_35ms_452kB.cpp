#include <bits/stdc++.h>
#define EPS 1e-9
using namespace std;

const int Max_N = 1010;
double add(double a, double b) {
  if (fabs(a + b) < EPS * (fabs(a) + fabs(b))) return 0;
  return a + b;
}
struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  Point operator+(Point p) { return Point(add(x, p.x), add(y, p.y)); }
  Point operator-(Point p) { return Point(add(x, -p.x), add(y, -p.y)); }
  Point operator*(double d) { return Point(x * d, y * d); }
  double operator*(Point p) { return add(x * p.x, y * p.y); }
  double operator^(Point p) { return add(x * p.y, -y * p.x); }
} po[Max_N];
// 判断点p是否在线段p1p2内
int on_segment(Point p1, Point p2, Point p) {
  if (((p1 - p).x * (p2 - p).x <= 0) && ((p1 - p).y * (p2 - p).y <= 0)) return 1;
  return 0;
}
struct Line {
  Point st, ed;
  Line() {}
  Line(Point a, Point b) {
    st = a;
    ed = b;
  }
} line[Max_N * 2];
// 判断线段p1p2与q1q2 是否相交
int intersection(Line l1, Line l2) {
  Point p1, p2, q1, q2;
  p1 = l1.st;
  p2 = l1.ed;
  q1 = l2.st;
  q2 = l2.ed;
  double d1, d2, d3, d4;
  d1 = (p2 - p1) ^ (q1 - p1);
  d2 = (p2 - p1) ^ (q2 - p1);
  d3 = (q2 - q1) ^ (p1 - q1);
  d4 = (q2 - q1) ^ (p2 - q1);
  if ((d1 == 0 && on_segment(p1, p2, q1)) || (d2 == 0 && on_segment(p1, p2, q2)) || (d3 == 0 && on_segment(q1, q2, p1)) || (d4 == 0 && on_segment(q1, q2, p2))) return 1;
  else if (d1 * d2 < 0 && d3 * d4 < 0)
    return 1;
  return 0;
}
int n;
bool judge() {
  int i, j;
  for (i = 0; i < n; i++)
    for (j = i + 2; j <= n + i - 2; j++)
      if (intersection(line[i], line[j])) return 0;
  return 1;
}
int main() {
  int i, j, k = 1;
  while (scanf("%d", &n) && n) {
    double area = 0.0;
    for (i = 0; i < n; i++) scanf("%lf%lf", &po[i].x, &po[i].y);
    for (i = 0; i < n; i++) {
      line[i].st = po[i];
      line[i].ed = po[(i + 1) % n];
    }
    for (i = 0; i < n; i++) // 把线段扩展一倍时，特别好处理， 与线段不相邻的其他线段
      line[n + i] = line[i];
    if (k != 1) puts("");
    printf("Figure %d: ", k++);
    if (n < 3) {
      printf("Impossible\n");
      continue;
    }
    if (judge()) {
      for (i = 0; i < n; i++) area += po[i] ^ po[(i + 1) % n];
      area = area < 0 ? -area : area;
      printf("%.2lf\n", area / 2.0);
    } else {
      printf("Impossible\n");
    }
  }
  return 0;
}