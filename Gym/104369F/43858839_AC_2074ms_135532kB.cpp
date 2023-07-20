#include <bits/stdc++.h>
using namespace std;
const int sn = 300, sq = 100007 / sn + 5, sx = sn + 7, N = 1e5 + 7;
int T, n, q, k, a[N], c[N], f[sq][N], g[N], st[sq][sn + 7];
long long sum, val[N], vval[N];
bool fl[N];
inline void upd1(int a, int b) {
  if (f[a][b] == 1) st[a][++st[a][0]] = b;
}
inline void upd2(int a, int b) {
  int pos = 0;
  for (int i = 1; i <= st[a][0]; i++) {
    if (st[a][i] == b) pos = i;
  }
  for (int i = pos; i < st[a][0]; i++) st[a][i] = st[a][i + 1];
  st[a][0]--;
}
inline bool chk(int u) {
  for (int i = 1; i <= st[u][0]; i++) {
    if (!fl[st[u][i]]) return false;
  }
  return true;
}
inline void Le(int u) {
  u--;
  // cerr<<u<<"sss"<<endl;
  while (u > 0) {
    bool fg = chk(g[u]);
    // cerr<<fg<<","<<u<<endl;
    if (fg) {
      sum += vval[g[u]], u -= sn;
      continue;
    }
    for (int x = u; x >= 1; x--) {
      if (!fl[c[x]]) break;
      sum += val[x];
    }
    break;
  }
}
inline void Re(int u) {
  u++;
  while (u <= n) {
    bool fg = chk(g[u]);
    if (fg) {
      sum += vval[g[u]], u += sn;
      continue;
    }
    for (int x = u; x <= n; x++) {
      if (!fl[c[x]]) break;
      sum += val[x];
    }
    break;
  }
}
int main() {
#ifdef memset0
  freopen("F.in", "r", stdin);
#endif
  scanf("%d", &T);
  for (int i = 1; i <= 100000; i++) g[i] = i / sn + 1;
  while (T--) {
    for (int i = 1; i <= n; i++) f[g[i]][c[i]] = 0, vval[g[i]] = 0, st[g[i]][0] = 0;
    scanf("%d%d", &n, &q);
    int sc = g[n];
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]), f[g[i]][c[i]]++, upd1(g[i], c[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &val[i]), vval[g[i]] += val[i];
    while (q--) {
      int u, p, x;
      scanf("%d", &u);
      if (u == 2) {
        scanf("%d%d", &p, &x);
        vval[g[p]] -= val[p];
        vval[g[p]] += x;
        val[p] = x;
      }
      if (u == 1) {
        scanf("%d%d", &p, &x);
        f[g[p]][c[p]]--;
        if (!f[g[p]][c[p]]) upd2(g[p], c[p]);
        c[p] = x;
        f[g[p]][c[p]]++;
        upd1(g[p], c[p]);
      }
      if (u == 3) {
        int x, k;
        scanf("%d%d", &x, &k), sum = 0;
        for (int i = 1; i <= k; i++) scanf("%d", &a[i]), fl[a[i]] = 1;
        int lx = x, rx = x;
        sum += val[x];
        // cerr<<sum<<","<<val[x]<<endl;
        while (lx - 1 >= 1 && (g[lx] == g[lx - 1])) {
          if (fl[c[lx - 1]]) sum += val[lx - 1], lx--;
          else
            break;
        }
        // cerr<<sum<<endl;
        while (rx + 1 <= n && (g[rx] == g[rx + 1])) {
          if (fl[c[rx + 1]]) sum += val[rx + 1], rx++;
          else
            break;
        }
        // cerr<<lx<<","<<rx<<","<<c[rx+1]<<","<<fl[2]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<","<<val[3]<<","<<val[4]<<endl;
        //	cerr<<"sss"<<endl;
        // cerr<<g[lx-1]<<","<<g[lx]<<endl;
        // cerr<<g[lx]<<","<<g[lx-1]<<endl;
        if (lx != 1 && g[lx] != g[lx - 1]) Le(lx);
        if (rx != n && g[rx] != g[rx + 1]) Re(rx);
        printf("%lld\n", sum);
        for (int i = 1; i <= k; i++) fl[a[i]] = 0;
      }
    }
  }
  return 0;
}//123123123