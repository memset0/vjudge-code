#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int n, fa[N], siz[N];
struct point {
  int x, y;
} a[N];
inline int iabs(int x) { return x < 0 ? -x : x; }
inline int dis(const point &a, const point &b) { return iabs(a.x - b.x) + iabs(a.y - b.y); }
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
bool check(int d) {
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    siz[i] = 1;
  }
  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 2; y++) {
      int j = 1;
      for (int i = 2; i <= n; i++)
        if (a[j].x + a[j].y > a[i].x + a[i].y) {
          j = i;
        }
      for (int i = 1; i <= n; i++)
        if (dis(a[i], a[j]) >= d) {
          int fi = find(i), fj = find(j);
          if (fi != fj) {
            if (siz[fi] < siz[fj]) {
              fa[fi] = fj;
              siz[fj] += siz[fi];
            } else {
              fa[fj] = fi;
              siz[fi] += siz[fj];
            }
          }
        }
      for (int i = 1; i <= n; i++) a[i].y *= -1;
    }
    for (int i = 1; i <= n; i++) a[i].x *= -1;
  }
  // for (int i = 1; i <= n; i++) cerr << find(i) << " \n"[i == n];
  // for (int i = 1; i <= n; i++) cerr << siz[find(i)] << " \n"[i == n];
  return siz[find(1)] == n;
}
int main() {
#ifdef memset0
  freopen("B.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  int l = 0, r = 2e9 + 1, mid, ans = -1;
  while (l <= r) {
    mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << ans << endl;
}