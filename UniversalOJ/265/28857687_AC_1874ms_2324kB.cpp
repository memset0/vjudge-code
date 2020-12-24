#include <bits/stdc++.h>
using namespace std;
const int N = 20;
const double eps = 1e-11;
int t, n, m, f[N * N], dp[1 << 18];
double fa, fb;
struct node {
  double x, y;
} a[N];
inline bool equ(double a, double b) { return fabs(a - b) < eps; }
inline bool gra(double a, double b) { return !equ(a, b) && a > b; }
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> t;
  while (t--) {
    memset(f, 0, sizeof(f));
    memset(dp, 0x3f, sizeof(dp));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].x >> a[i].y;
    }
    for (int i = 1; i <= n; i++)
      f[++f[0]] = 1 << (i - 1);
    for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++)
        if (a[i].x != a[j].x) {
          fa = (a[i].y * a[j].x - a[j].y * a[i].x) /
               (a[i].x * a[j].x * (a[i].x - a[j].x));
          fb = (a[i].y - fa * a[i].x * a[i].x) / a[i].x;
          // cerr << i << " " << j << " : " << fa << " " << fb << endl;
          f[0]++;
          if (gra(0., fa)) {
            for (int k = 1; k <= n; k++)
              if (equ(fa * a[k].x * a[k].x + fb * a[k].x, a[k].y)) {
                f[f[0]] += 1 << (k - 1);
              }
          }
        }
    dp[0] = 0;
    for (int i = 0; i < (1 << n); i++)
      for (int j = 1; j <= f[0]; j++)
        dp[i | f[j]] = min(dp[i | f[j]], dp[i] + 1);
    printf("%d\n", dp[(1 << n) - 1]);
  }
}