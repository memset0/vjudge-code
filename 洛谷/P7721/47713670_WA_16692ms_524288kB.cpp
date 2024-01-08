#include <bits/stdc++.h>
#ifdef memset0
#define log(...) fprintf(stderr, __VA_ARGS__)
#else
#define log(...) void(0)
#endif
using namespace std;
const int N = 2e5 + 9, S = 300, M = S + 9, B = (N / S) * 2 + 9;
const long long mod = 333333333333333397;
int n, m, tot, s[N], id[N];
long long t, pw[N];
vector<int> bl[N], br[N];
inline void add(int k, int x) {
  for (; k <= n; k += k & -k) s[k] += x;
}
inline int ask(int k) {
  int r = 0;
  for (; k; k -= k & -k) r += s[k];
  return r;
}
inline void updsum(long long &x, long long y) {
  x += y;
  if (x >= mod) x -= mod;
}
struct atom {
  long long v;
  int i, bln;
  int k; // atom::i在块内的rank
  inline bool operator<(const atom &rhs) const { return v == rhs.v ? i < rhs.i : v < rhs.v; }
} a[N];
struct query {
  int l, r, xl, xr, cnt = 0;
  long long vl, vr, ans;
  void push(long long cur) {
    ans = (ans + (__int128)pw[cnt] * cur) % mod;
    cnt++;
  }
} q[N];
struct stored {
  int cnt, rnk;
  long long ans;
  long long delta;
} pre[M][M];
long long val[M];
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
    log("brute solve :: block[%d %d] :: i=%d qxl=%d qxr=%d\n", xl, xr, i, qxl, qxr);
    if (is_same) {
      push_query(i);
    } else {
      long long lst = -1;
      for (int j = qxl; j <= qxr; j++)
        if (q[i].l <= a[j].i && a[j].i <= q[i].r) {
          if (a[j].v != lst) {
            log("brute push i=%d j=%d a[j].v=%lld\n", i, j, a[j].v);
            q[i].push(a[j].v);
            lst = a[j].v;
          }
        }
    }
  }
  void solve_all_same() {
    if (qry.empty()) return;
    // 处理全部都相同，用树状数组维护
    fill_n(s + 1, n, 0);
    for (int i = xl; i <= xr; i++) { add(a[i].i, 1); }
    long long cur = a[xl].v;
    for (const auto &x : qry) {
      int cnt = ask(x.r) - ask(x.l - 1);
      if (cnt) {
        log("all-same push i=%d v=%lld\n", x.i, cur);
        q[x.i].push(cur);
      }
    }
    qry.clear();
  }
  void solve_all() {
    if (is_same) return solve_all_same();
    // 处理块大小小于sqrt，用O(sqrt)修改O(1)查询的数据结构+扫描线维护(???好像也不用)
    for (int i = 0; i < qry.size(); i++) log("qry[%d] = l=%d r=%d i=%d\n", i, qry[i].l, qry[i].r, qry[i].i);
    for (int i = 0; i < qry.size(); i++) {
      bl[qry[i].l].emplace_back(i);
      br[qry[i].r].emplace_back(i);
    }
    fill_n(id + 1, n, 0);
    int t = 0;
    for (int i = xl; i <= xr; i++) id[a[i].i] = -1;
    for (int i = 1; i <= n; i++) {
      if (id[i]) id[i] = ++t;
      cerr << id[i] << " \n"[i == n];
    }
    cerr << "! t=" << t << endl;
    for (int i = xl; i <= xr; i++) val[id[a[i].i]] = a[i].v;
    for (int x = t + 1, i = n; i >= 1; i--) {
      if (id[i]) x = id[i];
      if (bl[i].size()) {
        for (int j : bl[i]) { qry[j].l = x; }
        bl[i].clear();
      }
    }
    for (int x = 0, i = 1; i <= n; i++) {
      if (id[i]) x = id[i];
      if (br[i].size()) {
        for (int j : br[i]) { qry[j].r = x; }
        br[i].clear();
      }
    }
    for (int i = 0; i < qry.size(); i++) log("qry[%d] = l=%d r=%d i=%d\n", i, qry[i].l, qry[i].r, qry[i].i);
    for (int r = 1; r <= t; r++) {
      pre[r][r].ans = val[r];
      pre[r][r].cnt = 1;
      pre[r][r].rnk = 0;
      int rnk = 0;
      for (int i = 1; i < r; i++) pre[i][r] = pre[i][r - 1];
      for (int l = r - 1; l >= 1; l--)
        if (val[l] == val[r]) {
          break;
        } else {
          if (val[r] < val[l]) {
            pre[l][r].delta = (__int128)(pw[pre[l][r].rnk + 1] - pw[pre[l][r].rnk] + mod) * val[l] % mod;
            pre[l][r].rnk++;
          } else {
            rnk++;
          }
          pre[l][r].cnt++;
          pre[l][r].ans = (pre[l][r].ans + (__int128)pw[rnk] * val[r]) % mod;
        }
      for (int l = r - 1; l >= 1; l--) {
        if (l > 1) { updsum(pre[l - 1][r].delta, pre[l][r].delta); }
        updsum(pre[l][r].ans, pre[l][r].delta);
        pre[l][r].delta = 0;
      }
    }
    // for (int l = 1; l <= t; l++)
    //   for (int r = l; r <= t; r++) log("pre[%d][%d] cnt=%d ans=%lld\n", l, r, pre[l][r].cnt, pre[l][r].ans);
    for (const auto &x : qry)
      if (x.l <= x.r) {
        // log(">>>> %lld ; %d %lld %lld\n", q[x.i].ans, q[x.i].cnt, pw[q[x.i].cnt], pre[x.l][x.r].ans);
        q[x.i].ans = (q[x.i].ans + (__int128)pw[q[x.i].cnt] * pre[x.l][x.r].ans) % mod;
        q[x.i].cnt += pre[x.l][x.r].cnt;
      }
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
    if (q[i].xl <= q[i].xr) {
      int bl = a[q[i].xl].bln;
      int br = a[q[i].xr].bln;
      log("query %d : l=%d r=%d vl=%lld vr=%lld xl=%d xr=%d bl=%d br=%d\n", i, q[i].l, q[i].r, q[i].vl, q[i].vr, q[i].xl, q[i].xr, bl, br);
      if (bl == br) {
        b[bl].brute_solve(i, q[i].xl, q[i].xr);
      } else {
        b[bl].brute_solve(i, q[i].xl, b[bl + 1].xl - 1);
        for (int j = bl + 1; j < br; j++) { b[j].push_query(i); }
      }
    }
  }
  for (int i = 1; i <= tot; i++) {
    log("solve all block %d : xl = %d xr = %d is_same = %d\n", i, b[i].xl, b[i].xr, (int)b[i].is_same);
    for (int j = b[i].xl; j <= b[i].xr; j++) log("a in block i=%d v=%lld\n", a[j].i, a[j].v);
    b[i].solve_all();
  }
  for (int i = 1; i <= m; i++)
    if (q[i].xl <= q[i].xr) {
      int bl = a[q[i].xl].bln;
      int br = a[q[i].xr].bln;
      if (bl < br) { b[br].brute_solve(i, b[br - 1].xr + 1, q[i].xr); }
    }
  for (int i = 1; i <= tot; i++)
    if (b[i].is_same) { b[i].solve_all_same(); }
  for (int i = 1; i <= m; i++) cout << q[i].ans << endl;
  for (int i = 1; i <= m; i++) cout << q[i].cnt << " \n"[i == m];
}