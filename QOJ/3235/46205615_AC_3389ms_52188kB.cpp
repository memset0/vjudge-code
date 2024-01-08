#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 9;
const unsigned int lim = (1u << 30) - 1u;
unsigned int x, y, z;
unsigned int rd() {
  x = x ^ (x << 11), x = x ^ (x >> 4);
  x = x ^ (x << 5), x = x ^ (x >> 14);
  unsigned int w = x ^ (y ^ z);
  x = y, y = z, z = w;
  return z;
}
int a[MAXN];
struct DSU {
  int fa[MAXN];
  void init(int n) {
    for (int i = 1; i <= n; ++i) fa[i] = i;
  }
  int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
  }
  void uni(int x, int y) {
    x = find(x), y = find(y);
    fa[x] = y;
  }
} s;
struct opt {
  int l, r, v;
  bool operator<(const opt &you) const { return v > you.v; }
} q[5000011];
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int task;
  cin >> task;
  while (task--) {
    int n, m;
    cin >> n >> m >> x >> y >> z;
    for (int i = 1; i <= n; ++i) a[i] = 0;
    s.init(n + 1);
    int cur = 0;
    bool flag = m > 10 * n;
    for (int i = 1; i <= m; ++i) {
      int l = rd() % n + 1, r = rd() % n + 1;
      int v = rd() & lim;
      if (flag && v < lim / 4) continue;
      if (l > r) swap(l, r);
      q[++cur] = {l, r, v};
    }
    sort(q + 1, q + cur + 1);
    for (int i = 1; i <= cur; ++i) {
      int p = s.find(q[i].l);
      while (p <= q[i].r) {
        a[p] = q[i].v;
        s.uni(p, p + 1), p = s.find(p);
      }
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) ans ^= (long long)i * a[i];
    cout << ans << '\n';
  }
  cerr << double(clock()) / CLOCKS_PER_SEC;
}
