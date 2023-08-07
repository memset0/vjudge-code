#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
const int N = 1e6 + 9;
int n, m, q;
char op[100];
long long l, r;
vector<int> ins[N], del[N];
vector<long long> f[N], g[N];
vector<vector<int>> a;
struct interval {
  int l, r;
  long long w;
  int x;
  inline long long get(int i) {
    assert(l <= i && i <= r);
    return w + (i - l) * x;
  }
};
vector<interval> vx[N], vy[N];
inline int get_cell() {
  int c = getchar();
  while (c != '.' && c != '#') c = getchar();
  return c == '#';
}
void solve(vector<interval> &vec, vector<long long> &res, int n) {
  res.resize(n + 2);
  // cerr << "solve " << vec.size() << " " << n << endl;
  for (int i = 1; i <= n; i++) ins[i].clear(), del[i].clear();
  for (int i = 0; i < (int)vec.size(); i++) {
    // cerr << "! " << vec[i].l << " " << vec[i].r << endl;
    assert(vec[i].l >= 1 && vec[i].r <= n);
    ins[vec[i].l].push_back(i);
    del[vec[i].r].push_back(i);
  }
  set<int> st;
  for (int i = 1; i <= n; i++) {
    for (int x : ins[i]) st.insert(x);
    // cerr << i << " " << a[i] << " " << (st.size() ? *--st.end() : -1) << endl;
    if (st.size()) {
      int k = *--st.end();
      // cerr << "     :: " << vec[k].get(i) << " " << l << " " << r << endl;
      res[i] = vec[k].get(i);
    } else {
      res[i] = -1;
    }
    for (int x : del[i]) st.erase(st.find(x));
  }
}
int main() {
#ifdef memset0
  freopen("J4.in", "r", stdin);
#endif
  scanf("%d%d%d", &n, &m, &q);
  a.resize(n + 2);
  rep(i, 1, n) {
    a[i].resize(m + 2);
    rep(j, 1, m) {
      a[i][j] = get_cell();
      // cerr << i << " " << j << " " << a[i][j] << endl;
    }
  }
  int x = n, y = 1, step;
  long long time = 1;
  rep(i, 1, q) {
    scanf("%s%d", op, &step);
    // cerr << i << " " << op[0] << " " << step << " " << time << " " << x << " " << y << endl;
    if (op[0] == 'l' || op[0] == 'r') {
      if (op[0] == 'l') {
        vx[x].push_back({y - step, y, time + step, -1});
        y -= step;
      } else {
        vx[x].push_back({y, y + step, time, 1});
        y += step;
      }
    } else {
      if (op[0] == 'u') {
        vy[y].push_back({x - step, x, time + step, -1});
        x -= step;
      } else {
        vy[y].push_back({x, x + step, time, 1});
        x += step;
      }
    }
    time += step;
  }
  l = 0, r = time + 1;
  rep(i, 1, n) { solve(vx[i], f[i], m); }
  rep(i, 1, m) { solve(vy[i], g[i], n); }
  rep(i, 1, n) rep(j, 1, m) {
    long long x = max(f[i][j], g[j][i]);
    if (~x) {
      if (a[i][j]) {
        l = max(l, x);
      } else {
        r = min(r, x);
      }
    } else {
      if (a[i][j]) r = -1;
    }
    // fprintf(stderr, "%4d%c", x, " \n"[j == m]);
  }
  --r;
  if (l <= r) {
    cout << l << " " << r << endl;
  } else {
    cout << -1 << " " << -1 << endl;
  }
}