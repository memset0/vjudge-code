#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define maxn 30

const double PI = acos(-1.0), EPS = 1e-6, PI2 = 2 * acos(-1.0);

int x[4], y[4];

double dbcmp(double a, double b) { return b - a > EPS ? -1 : a - b > EPS; }

double radian(int ax, int ay, int bx, int by) {
  double r = atan2(1.0 * ax * by - (ay * bx), 1.0 * ax * bx + (ay * by));
  return r;
}

bool in_tri(const int xx, const int yy) {
  double s = 0, t = 0;
  for (int i = 0; i < 3; i++) {
    t = radian(x[i + 1] - xx, y[i + 1] - yy, x[i] - xx, y[i] - yy);
    if (dbcmp(t, PI) == 0) return false;
    s += t;
  }
  if (dbcmp(s, PI2) == 0) return true;
  return false;
}

int min(int xx, int yy) {
  if (xx < yy) return xx;
  return yy;
}
int max(int xx, int yy) {
  if (xx > yy) return xx;
  return yy;
}

int main() {
  printf("Program 4 by team X\n");
  int minx, maxx, miny, maxy, ansminx;
  int end_x[maxn]; // last dot in line i end with (end_x[i], i)
  bool ans[maxn][maxn];
  while (scanf("%d%d%d%d%d%d", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2]) == 6) {
    memset(ans, 0, sizeof(ans));
    memset(end_x, 255, sizeof(end_x));
    minx = miny = maxn + 1;
    maxx = maxy = -1;
    for (int i = 0; i < 3; i++) {
      x[i] += 10;
      y[i] += 10;
      minx = min(minx, x[i]);
      maxx = max(maxx, x[i]);
      miny = min(miny, y[i]);
      maxy = max(maxy, y[i]);
    }
    x[3] = x[0];
    y[3] = y[0];
    ansminx = maxn + 1;
    for (int xx = minx; xx <= maxx; xx++)
      for (int yy = miny; yy <= maxy; yy++)
        if (in_tri(xx, yy)) {
          ans[xx][yy] = 1;
          if (end_x[yy] == -1 || xx > end_x[yy]) end_x[yy] = xx;
          ansminx = min(xx, ansminx);
        }
    for (int yy = maxy; yy >= 0; yy--)
      if (end_x[yy] != -1) {
        for (int xx = ansminx; xx < end_x[yy]; xx++)
          if (ans[xx][yy]) printf("(%2d, %2d) ", xx - 10, yy - 10);
          else
            printf("         ");
        if (ans[end_x[yy]][yy]) printf("(%2d, %2d)\n", end_x[yy] - 10, yy - 10);
      }
    printf("\n");
  }
  printf("End of program 4 by team X\n");
  return 0;
}