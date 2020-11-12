#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 7, M = 1e5 + 7;
double f[N][N], ans[M][N];
int n, a[M], b[M], w[N], g[M], mu[M];
bool fl[M];
inline int gcd(int a, int b) {
  if (!b)
    return a;
  return gcd(b, a % b);
}
int main() {
  //    freopen("in.txt","r",stdin);
  //    freopen("w.txt","w",stdout);
  int t;
  cin >> t;
  for (int i = 1; i <= 100000; i++)
    mu[i] = 1;
  for (int i = 2; i <= 100000; i++) {
    if (!fl[i]) {
      mu[i] = -mu[i];
      for (int j = i + i; j <= 100000; j += i)
        mu[j] = -mu[j], fl[j] = 1;
      if (1ll * i * i <= 100000) {
        for (int j = i * i; j <= 100000; j += i * i)
          mu[j] = 0;
      }
    }
  }

  while (t--) {
    cin >> n;
    memset(fl, 0, sizeof(fl));
    memset(f, 0, sizeof(f));
    for (int i = 1; i < n; i++) {
      f[i][1] = 1.0 * i / n;
      for (int k = 2; k <= i; k++)
        f[i][k] = f[i][k - 1] * (i - k + 1) / (n - k + 1);
    }

    for (int i = 1; i <= n; i++)
      scanf("%d", &w[i]);
    int v = w[1];
    for (int i = 2; i <= n; i++)
      v = gcd(v, w[i]);
    if (v > 1) {
      if (n % 2 == 0)
        printf("0.00000000\n");
      else
        printf("1.00000000\n");
      continue;
    }
    for (int i = 1; i <= n; i++)
      for (int j = 1; j * j <= w[i]; j++) {
        if (w[i] % j == 0) {
          g[j]++, fl[j] = 1;
          if (j * j != w[i])
            g[w[i] / j]++, fl[w[i] / j] = 1;
        }
      }
    mu[1] = 0;
    double sum = 0;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= 100000; i++)
      if (fl[i]) {
        for (int j = 1; j <= n; j++) {
          if (w[j] % i == 0)
            a[i]++;
          else if (gcd(w[j], i) > 1)
            b[i]++;
        }
        for (int j = 1; j <= n; j++)
          ans[i][j] = f[a[i]][j];
      }
    sum = 0;
    fl[1] = 0;
    for (int i = 100000; i > 0; i--)
      if (fl[i]) {
        for (int j = 1; j * j <= i; j++) {
          if (i % j == 0) {
            for (int z = 1; z <= n; z += 2)
              ans[j][z] = ans[j][z] - ans[i][z];
            if (j * j == i || j == 1)
              continue;
            for (int z = 1; z <= n; z += 2)
              ans[i / j][z] = ans[i / j][z] - ans[i][z];
          }
        }
        for (int j = 1; j <= a[i]; j += 2)
          sum = sum + ans[i][j] * (n - a[i] - b[i]) / (n - j);
      }
    printf("%.9lf\n", sum);
  }
}
// 1
// 4
// 1 2 4 8