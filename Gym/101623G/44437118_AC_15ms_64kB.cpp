#include <bits/stdc++.h>
using lf = long double;
using namespace std;
const int N = 1e3 + 9;
const lf pi = acos(-1.0);
int n, m;
struct point {
  int x, y;
  lf deg, dis;
} a[N];
lf calc(int d) {
  lf alpha = pi * 2 / d;
  lf mn, mx;
  for (int i = 1; i <= n; i++) {
    lf theta = a[i].deg;
    while (theta >= alpha) theta -= alpha;
    lf beta = fabs(alpha / 2 - theta);
    lf w = 2 * a[i].dis * cos(beta) * tan(alpha / 2);
    // fprintf(stderr, "%d i=%d[%d %d] w=%.12lf\n", d, i, a[i].x, a[i].y, w);
    if (i == 1) mn = mx = w;
    else {
      mn = min(mn, w);
      mx = max(mx, w);
    }
  }
  return (mn / mx) * (mn / mx);
}
int main() {
#ifdef memset0
  freopen("G1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
    a[i].dis = sqrtl((long long)a[i].x * a[i].x + (long long)a[i].y * a[i].y);
    a[i].deg = atan2(a[i].y, a[i].x);
    if (a[i].deg < 0) a[i].deg += pi * 2;
  }
  int ansi = 3;
  lf ansv = calc(3);
  for (int i = 4; i <= 8; i++) {
    lf v = calc(i);
    if (v > ansv) {
      ansi = i;
      ansv = v;
    }
  }
  printf("%d %.12lf\n", ansi, (double)ansv);
}