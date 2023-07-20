#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
const double K = 1e6;
int n, a[N];
double f[N], s, sf[N << 2], sg[N << 2];
void build(int u, int l, int r) {
  if (l == r) {
    double t = n - f[l];
    sf[u] += 1 / t;
    sg[u] += (1 - f[l]) / t;
    return;
  }
  int mid = (l + r) >> 1;
  build(u << 1, l, mid);
  build(u << 1 | 1, mid + 1, r);
  sf[u] = sf[u << 1] + sf[u << 1 | 1];
  sg[u] = sg[u << 1] + sg[u << 1 | 1];
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], f[i] = a[i] / K;
  build(1, 1, n);
  s = (sf[1] / (1 - sg[1])) * ((double)(n - 1) / n);
  printf("%.10lf\n", s);
}