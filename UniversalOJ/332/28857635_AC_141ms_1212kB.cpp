#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int t;
bool mark, dis[N];
long long n, h, r, x[N], y[N], z[N], anc[N];
inline long long find(int x) { return anc[x] == x ? x : anc[x] = find(anc[x]); }
inline double dist(int i, int j) {
  return sqrt((x[i] - x[j]) * (long long)(x[i] - x[j]) +
              (y[i] - y[j]) * (long long)(y[i] - y[j]) +
              (z[i] - z[j]) * (long long)(z[i] - z[j]));
}
inline unsigned long long dist2(int i, int j) {
  return (unsigned long long)(x[i] - x[j]) * (x[i] - x[j]) +
         (unsigned long long)(y[i] - y[j]) * (y[i] - y[j]) +
         (unsigned long long)(z[i] - z[j]) * (z[i] - z[j]);
}
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%lld%lld%lld", &n, &h, &r);
    for (int i = 1; i <= n; i++)
      anc[i] = i; //初始化并查集
    memset(dis, 0, sizeof(dis));
    for (int i = 1; i <= n; i++) {
      scanf("%lld%lld%lld", &x[i], &y[i], &z[i]);
    }
    for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++)
        if (dist2(i, j) <= 4ull * r * r) {
          anc[find(i)] = find(j); //合并
        }
    for (int i = 1; i <= n; i++)
      if (z[i] <= r) {
        dis[find(i)] = 1;
      }
    mark = false;
    for (int i = 1; i <= n; i++)
      if (z[i] + r >= h)
        if (dis[find(i)]) {
          mark = true;
          break;
        }
    puts(mark ? "Yes" : "No");
  }
  return 0;
}