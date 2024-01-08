// AC Onsite

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); ++i)
#define Rep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
// #define int long long
#define ull unsigned long long
using namespace std;
inline int read() {
  char c = getchar();
  int x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar())
    f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  if (f)
    x = -x;
  return x;
}
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int, int> pii;
typedef vector<int> vi;
#define maxn 1000005
#define inf 0x3f3f3f3f
int n, p[maxn], pos[maxn];
bool vis[maxn];
int vis2[maxn];
int sum[maxn];
int tmp[maxn][5];
int Q(int o, int l, int r) { return tmp[r][o] - tmp[l - 1][o]; }
int res;
pii ans;
map<int, int> mp;
vector<pii> buc;
void adde(int u, int v, int w) { mp[max(u, v)] += (-w); }
void del(int x) {
  if (vis[x - 1])
    adde(p[x], p[x - 1], -1);
  if (vis[x + 1])
    adde(p[x], p[x + 1], -1);
  vis[x] = 0;
}
void ins(int x) {
  vis[x] = 1;
  if (vis[x - 1])
    adde(p[x], p[x - 1], 1);
  if (vis[x + 1])
    adde(p[x], p[x + 1], 1);
}
void work(int x, int y) {
  if (x == y)
    return;
  mp.clear();
  del(x), del(y);
  swap(p[x], p[y]);
  ins(x), ins(y);
  swap(p[x], p[y]);
  int now = 0, lst = 1, res1 = 0;
  auto calc = [&](int p, int l, int r) {
    if (p > 0 || l > r)
      return;
    res1 += Q(-p, l, r);
  };
  for (auto [x, y] : mp) {
    calc(now, lst, x - 1);
    now += y;
    lst = x;
  }
  calc(now, lst, n);
  if (res1 > res)
    res = res1, ans = mkp(x, y);
}
void work() {
  n = read();
  For(i, 1, n) p[i] = read(), pos[p[i]] = i;
  For(i, 1, n) sum[i] = 1;
  sum[1] = 0;
  For(i, 1, n - 1) sum[max(p[i], p[i + 1])]--;
  For(i, 1, n) {
    sum[i] += sum[i - 1];
    For(j, 0, 4) tmp[i][j] = tmp[i - 1][j];
    if (sum[i] <= 4)
      tmp[i][sum[i]]++;
  }
  For(i, 0, n + 1) vis2[i] = 0;
  vis[0] = vis[n + 1] = 0;
  For(i, 1, n) vis[i] = 1;
  buc.clear();
  res = Q(0, 1, n), ans = mkp(1, 1);
  For(i, 1, n) if (i != pos[1]) buc.pb(mkp(i, pos[1]));
  int l = pos[1], r = pos[1], pl = pos[1], pr = pos[1];
  vis2[1] = 1;
  For(i, 2, n) {
    if (pos[i] < l)
      l = pos[i];
    if (pos[i] > r)
      r = pos[i];
    vis2[pos[i]] = 1;
    while (pl > 1 && vis2[pl - 1])
      --pl;
    while (pr < n && vis2[pr + 1])
      ++pr;
    for (int x : {pl - 1, pr + 1})
      for (int y : {l, r})
        if (x >= 1 && x <= n && x != y)
          buc.pb(mkp(x, y));
  }
  //	cerr<<"buc "<<buc.size()<<"\n";
  for (auto [x, y] : buc)
    work(x, y);
  //	cerr<<"res "<<res<<"\n";
  cout << ans.fi << " " << ans.se << "\n";
}
signed main() {
  //	freopen("data.in","r",stdin);
  int T = read();
  while (T--)
    work();
  return 0;
}