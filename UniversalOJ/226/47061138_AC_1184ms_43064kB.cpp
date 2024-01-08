#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 9, mod = 998244353, L = 1e4 + 9;
int n, m, ans, tot, top, cir[N], w0[N], w1[N], deg[N], u[N], v[N], w[N], pre[N], suf[N], stk[N], hed[N], to[N << 1], val[N << 1], nxt[N << 1], fac[N * L], ifac[L];
bool vis[N], onc[N], inc[N];
void initgraph() {
  tot = 0;
  memset(hed, -1, sizeof(hed));
}
void initfac() {
  fac[0] = ifac[0] = ifac[1] = 1;
  for (int i = 1; i < N * L; i++) fac[i] = (long long)fac[i - 1] * i % mod;
  for (int i = 2; i < L; i++) ifac[i] = (long long)(mod - mod / i) * ifac[mod % i] % mod;
  for (int i = 1; i < L; i++) ifac[i] = (long long)ifac[i - 1] * ifac[i] % mod;
}
inline int C(int n, int m) { return n < m ? 0 : (long long)fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
inline void link(int u, int v, int w) { nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++; }
inline int calc_fac(int x) {
  int res = 1;
  for (int i = 1; i <= x; i++) res = (long long)res * i % mod;
  return res;
}
void solve_tree() {
  int ans = 1;
  for (int u, v, w, i = 1; i <= m; i++) {
    cin >> u >> v >> w;
    if (w & 1) {
      cout << 0 << endl;
      return;
    }
    deg[u] += w >> 1, deg[v] += w >> 1;
    ans = (long long)ans * C(w, w >> 1) % mod * (w >> 1) % mod;
  }
  for (int i = 1; i <= n; i++) ans = (long long)ans * fac[deg[i] - 1] % mod;
  cout << ans << endl;
}
void dfs(int u, int fa) {
  stk[++top] = u, vis[u] = 1;
  for (int i = hed[u]; ~i; i = nxt[i])
    if (to[i] != fa) {
      if (vis[to[i]]) {
        if (*cir) continue;
        cir[++*cir] = val[i];
        for (int x = u; x != to[i]; x = to[pre[x] ^ 1]) {
          cir[++*cir] = val[pre[x]];
        }
      } else {
        pre[to[i]] = i;
        dfs(to[i], u);
      }
    }
  --top;
}
void ordered_circle() {
  int same = -1;
  if (u[cir[1]] == u[cir[2]]) same = u[cir[1]];
  if (u[cir[1]] == v[cir[2]]) same = u[cir[1]];
  if (v[cir[1]] == u[cir[2]]) same = v[cir[1]];
  if (v[cir[1]] == v[cir[2]]) same = v[cir[1]];
  assert(~same);
  int s = u[cir[1]] + v[cir[1]] - same;
  for (int i = 1; i <= *cir; i++) {
    if (u[cir[i]] != s) swap(u[cir[i]], v[cir[i]]);
    s = v[cir[i]];
  }
}
int calc(int cur) {
  memset(deg, 0, sizeof(deg));
  int ans = 1, sum = 0, ano = 1;
  for (int i = 1; i <= m; i++) {
    if (inc[i]) {
      if ((w[i] + cur) & 1) return 0;
      w0[i] = (w[i] + cur) >> 1;
      w1[i] = (w[i] - cur) >> 1;
    } else {
      w0[i] = w1[i] = w[i] >> 1;
    }
    deg[u[i]] += w1[i];
    deg[v[i]] += w0[i];
    ans = (long long)ans * C(w[i], w0[i]) % mod;
  }
  for (int i = 1; i <= n; i++) ans = (long long)ans * fac[deg[i] - 1] % mod;
  for (int i = 1; i <= m; i++)
    if (!inc[i]) ano = (long long)ano * w0[i] % mod;
  for (int k = 1; k <= *cir; k++) pre[k] = (long long)pre[k - 1] * w0[cir[k]] % mod;
  for (int k = *cir; k >= 1; k--) suf[k] = (long long)suf[k + 1] * w1[cir[k]] % mod;
  for (int k = 1; k <= *cir; k++) {
    sum = (sum + (long long)pre[k - 1] * suf[k + 1] % mod * ano) % mod;
  }
  return (long long)sum * ans % mod;
}
int main() {
#ifdef mmeset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  initfac();
  initgraph();
  cin >> n >> m;
  if (n == m + 1) return solve_tree(), 0;
  for (int i = 1; i <= m; i++) {
    cin >> u[i] >> v[i] >> w[i];
    link(u[i], v[i], i);
    link(v[i], u[i], i);
    deg[u[i]] += w[i];
    deg[v[i]] += w[i];
  }
  for (int i = 1; i <= n; i++)
    if (deg[i] & 1) {
      cout << 0 << endl;
      return 0;
    }
  dfs(1, 0);
  ordered_circle();
  int mn = INT_MAX;
  for (int i = 1; i <= *cir; i++) {
    inc[cir[i]] = onc[u[cir[i]]] = onc[v[cir[i]]] = true;
    mn = min(mn, w[cir[i]]);
  }
  pre[0] = suf[0] = pre[*cir + 1] = suf[*cir + 1] = 1;
  for (int d = -mn; d <= mn; d++) ans = (ans + calc(d)) % mod;
  cout << ans << endl;
}