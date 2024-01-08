#include <bits/stdc++.h>
using namespace std;
using lf = long double;
const int N = 1e4 + 9;
int n;
bool flag = false;
struct node {
  int l, r, mid, cnt;
} p[N << 2];
void build(int u, int l, int r) {
  // fprintf(stderr, "build %d %d %d\n", u, l, r);
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  p[u].cnt = 0;
  if (l == r) {
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
}
void modify(int u, int l, int r) {
  // fprintf(stderr, "modify %d %d %d\n", u, l, r);
  if (p[u].l == l && p[u].r == r) {
    p[u].cnt++;
    return;
  }
  if (r <= p[u].mid) {
    modify(u << 1, l, r);
  } else if (l > p[u].mid) {
    modify(u << 1 | 1, l, r);
  } else {
    modify(u << 1, l, p[u].mid);
    modify(u << 1 | 1, p[u].mid + 1, r);
  }
}
void dfs(int u, int pre = 0) {
  pre += p[u].cnt;
  if (pre >= (n >> 1)) {
    flag = true;
  }
  if (p[u].l == p[u].r) {
    return;
  }
  dfs(u << 1, pre);
  dfs(u << 1 | 1, pre);
}
lf solve(const vector<int> &x, const vector<int> &y, const vector<int> &z) {
  auto check = [&](lf k) -> bool {
    vector<lf> val;
    vector<pair<lf, bool>> dif;
    for (int i = 0; i < n; i++) {
      lf b = -2 * x[i];
      lf c = x[i] * x[i] + y[i] * y[i] + z[i] * z[i] - k * k;
      lf delta = b * b - 4 * c;
      if (delta >= 0) {
        delta = sqrtl(delta);
        lf l = (-b - delta) / 2;
        lf r = (-b + delta) / 2;
        dif.push_back(make_pair(l, false));
        dif.push_back(make_pair(r, true));
      }
    }
    sort(dif.begin(), dif.end());
    int cnt = 0;
    for (const auto &[x, f] : dif) {
      cnt += f ? -1 : 1;
      if (cnt >= (n >> 1)) {
        return true;
      }
    }
    return false;
  };
  lf l = 0, r = 1.5e4, mid, res;
  for (int t = 50; t--;) {
    mid = (l + r) / 2;
    if (check(mid)) {
      res = mid;
      r = mid;
    } else {
      l = mid;
    }
  }
  return res;
}
int main() {
#ifdef memset0
  freopen("J.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  vector<int> x(n), y(n), z(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i] >> z[i];
  }
  lf ans = 1e10;
  ans = min(ans, solve(x, y, z));
  ans = min(ans, solve(y, x, z));
  ans = min(ans, solve(z, x, y));
  cout << fixed << setprecision(12) << ans << endl;
}