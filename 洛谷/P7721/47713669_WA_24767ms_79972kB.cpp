#include <bits/stdc++.h>
#ifdef memset0
#define log(...) fprintf(stderr, __VA_ARGS__)
#else
#define log(...) void(0)
#endif
using namespace std;
const int N = 2e5 + 9, S = 5009, B = (N / S) * 2 + 9;
const long long mod = 333333333333333397;
int n, m, tot, s[N];
long long t, pw[N];
inline void add(int k, int x) {
  for (; k <= n; k += k & -k) s[k] += x;
}
inline int ask(int k) {
  int r = 0;
  for (; k; k -= k & -k) r += s[k];
  return r;
}
struct atom {
  long long v;
  int i, k, bln;
  inline bool operator<(const atom &rhs) const { return v == rhs.v ? i < rhs.i : v < rhs.v; }
} a[N];
struct query {
  int l, r, xl, xr, cnt = 0;
  long long vl, vr, ans;
} q[N];
struct block {
  struct query {
    int l, r, i;
    query(int l, int r, int i) : l(l), r(r), i(i) {}
  };
  vector<query> qry;
  int xl, xr;
  bool is_same;
  void push_query(int i) { qry.emplace_back(q[i].l, q[i].r, i); }
  void brute_solve(int i, int qxl, int qxr) {
    log("brute block[%d %d] :: i=%d qxl=%d qxr=%d\n", xl, xr, i, qxl, qxr);
    if (is_same) {
      push_query(i);
    } else {
      long long lst = -1;
      for (int j = qxl; j <= qxr; j++)
        if (q[i].l <= a[j].i && a[j].i <= q[i].r) {
          log("push i=%d j=%d : %lld*%lld\n", i, j, pw[q[i].cnt], a[j].v);
          if (a[j].v != lst) {
            q[i].ans = (q[i].ans + (__int128)pw[q[i].cnt] * a[j].v) % mod;
            lst = a[j].v;
            q[i].cnt++;
          }
        }
    }
  }
  void solve_all_same() {
    // 处理全部都相同，用树状数组维护
    memset(s + 1, 0, n << 2);
    for (int i = xl; i <= xr; i++) { add(a[i].i, 1); }
    long long cur = a[xl].v;
    for (const auto &x : qry) {
      int cnt = ask(x.r) - ask(x.l - 1);
      if (cnt) {
        q[x.i].ans = (q[x.i].ans + (__int128)pw[q[x.i].cnt] * cur) % mod;
        q[x.i].cnt++;
      }
    }
  }
  void solve_all() {
    if (is_same) return solve_all_same();
    // 处理块大小小于sqrt，用O(sqrt)修改O(1)查询的数据结构+扫描线维护
  }
} b[B];
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> t >> m;
  pw[0] = 1;
  for (int i = 1; i < N; i++) pw[i] = (__int128)pw[i - 1] * t % mod;
  map<long long, int> mp;
  vector<long long> tmp;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].v;
    tmp.push_back(a[i].v);
    a[i].i = i;
    mp[a[i].v]++;
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) log("a[%d] : v=%lld i=%d k=%d\n", i, a[i].v, a[i].i, a[i].k);
  sort(tmp.begin(), tmp.end());
  vector<int> bln;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = l + mp[a[l].v] - 1;
    while (r < n && r + mp[a[r + 1].v] < l + S) r += mp[a[r + 1].v];
    ++tot;
    for (int i = l; i <= r; i++) { a[i].bln = tot; }
    b[tot].xl = l, b[tot].xr = r;
    if (a[l].v == a[r].v) b[tot].is_same = true;
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r >> q[i].vl >> q[i].vr;
    q[i].xl = lower_bound(tmp.begin(), tmp.end(), q[i].vl) - tmp.begin() + 1;
    q[i].xr = upper_bound(tmp.begin(), tmp.end(), q[i].vr) - tmp.begin();
    int bl = a[q[i].xl].bln;
    int br = a[q[i].xr].bln;
    log("query %d : l=%d r=%d vl=%lld vr=%lld xl=%d xr=%d\n", i, q[i].l, q[i].r, q[i].vl, q[i].vr, q[i].xl, q[i].xr);
    if (bl == br) {
      b[bl].brute_solve(i, q[i].xl, q[i].xr);
    } else {
      b[bl].brute_solve(i, q[i].xl, b[bl + 1].xl - 1);
      for (int j = bl + 1; j < br; j++) { b[j].push_query(i); }
    }
  }
  for (int i = 1; i <= tot; i++) {
    log("solve all block %d : xl = %d xr = %d is_same = %d\n", i, b[i].xl, b[i].xr, (int)b[i].is_same);
    b[i].solve_all();
  }
  for (int i = 1; i <= m; i++) {
    int bl = a[q[i].xl].bln;
    int br = a[q[i].xr].bln;
    if (bl < br) { b[br].brute_solve(i, b[br - 1].xr + 1, q[i].xr); }
  }
  for (int i = 1; i <= m; i++) cout << q[i].ans << endl;
}