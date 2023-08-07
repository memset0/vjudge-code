#include "bits/stdc++.h"
typedef long long ll;
typedef std::pair<ll, ll> pii;
const int mod = 1e9 + 7, inv2 = (mod + 1) >> 1;
const ll INF = 1e16;
const int MAXN = 400011;

struct DSU {
  int fa[MAXN];
  void init(int n) {
    for (int i = 1; i <= n; ++i) fa[i] = i;
  }
  int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
  }
  bool uni(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return 0;
    fa[x] = y;
    return 1;
  }
} F;
pii a[MAXN], b[2][MAXN];
int lb[2], rb[2];
int n;
bool check(ll d) {
  // printf("d=%d\n",d);
  F.init(n);
  int rest = n;
  lb[0] = lb[1] = 0, rb[0] = rb[1] = n + 1;
  for (int u = 1; u <= n; ++u) {
    // printf("u=%d:\n",u);
    ll si = a[u].first + a[u].second;
    int p = std::upper_bound(b[0] + 1, b[0] + n + 1, pii(si - d + 1, 0)) - b[0] - 1;
    lb[0] = std::max(lb[0], p);
    if (p > 0) rest -= F.uni(b[0][1].second, u);
    // printf("%d ",p);
    ll di = a[u].first - a[u].second;
    p = std::upper_bound(b[1] + 1, b[1] + n + 1, pii(di - d + 1, 0)) - b[1] - 1;
    if (p > 0) rest -= F.uni(b[1][1].second, u);
    lb[1] = std::max(lb[1], p);
    // printf("%d ",p);

    p = std::lower_bound(b[1] + 1, b[1] + n + 1, pii(di + d, 0)) - b[1];
    rb[1] = std::min(rb[1], p);
    if (p <= n) rest -= F.uni(b[1][n].second, u);
    // printf("%d ",p);
    p = std::lower_bound(b[0] + 1, b[0] + n + 1, pii(si + d, 0)) - b[0];
    rb[0] = std::min(rb[0], p);
    if (p <= n) rest -= F.uni(b[0][n].second, u);
    // printf("%d ",p);
    // puts("");
  }
  // printf("rest=%d\n",rest);
  for (int i = 2; i <= lb[0]; ++i) rest -= F.uni(b[0][i - 1].second, b[0][i].second);
  for (int i = 2; i <= lb[1]; ++i) rest -= F.uni(b[1][i - 1].second, b[1][i].second);

  for (int i = rb[0]; i < n; ++i) rest -= F.uni(b[0][i].second, b[0][i + 1].second);
  for (int i = rb[1]; i < n; ++i) rest -= F.uni(b[1][i].second, b[1][i + 1].second);
  return rest == 1;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &a[i].first, &a[i].second);
    b[0][i] = pii(a[i].first + a[i].second, i);
    b[1][i] = pii(a[i].first - a[i].second, i);
  }
  std::sort(b[0] + 1, b[0] + n + 1);
  std::sort(b[1] + 1, b[1] + n + 1);
  b[0][n + 1] = pii(INF, 0);
  b[1][n + 1] = pii(INF, 0);
  ll l = 0, r = 2e9;
  while (l < r) {
    ll mid = (l + r + 1) >> 1;
    if (check(mid)) l = mid;
    else
      r = mid - 1;
  }
  printf("%lld\n", l);
  return 0;
}