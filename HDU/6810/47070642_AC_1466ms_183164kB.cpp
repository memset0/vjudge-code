#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9, mod = 1e9 + 7;
int T, n, m, fa[N], siz[N];
vector<int> G[N];
struct z {
  int x;
  z(int x = 0) : x(x) {}
  friend inline z operator*(z a, z b) { return (long long)a.x * b.x % mod; }
  friend inline z operator-(z a, z b) { return (a.x -= b.x) < 0 ? a.x + mod : a.x; }
  friend inline z operator+(z a, z b) { return (a.x += b.x) >= mod ? a.x - mod : a.x; }
} F0[N], F1[N], fac[N], inv[N], ifac[N], sumall[N], sumsub[N];
inline z fpow(z a, int b) {
  z s = 1;
  for (; b; b >>= 1, a = a * a)
    if (b & 1) s = s * a;
  return s;
}
inline z finv(z a) { return fpow(a, mod - 2); }
inline z C(int n, int m) { return n < m ? 0 : fac[n] * ifac[m] * ifac[n - m]; }
struct atom {
  int siz;
  z sum;
};
vector<atom> A[N];
void dfs(int u) {
  siz[u] = 1;
  sumsub[u] = 0;
  for (int v : G[u]) {
    fa[v] = u, dfs(v), siz[u] += siz[v];
    sumsub[u] = sumsub[u] + sumsub[v] + siz[v];
  }
}
void dfs2(int u, z fr) {
  sumall[u] = fr + sumsub[u], fr = fr + n;
  for (int v : G[u]) {
    fr = fr + sumsub[v] + siz[v];
  }
  for (int v : G[u]) {
    dfs2(v, fr - sumsub[v] - siz[v] - siz[v]);
  }
}
void sol0(int n, int m, int l, int r, z *F) {
  if (l > m || l > r) {
    memset(F, 0, (n + 1) << 2);
  } else {
    F[n] = C(n, m);
    for (int i = n - 1; i >= 0; i--) F[i] = F[i + 1] - C(i, l - 1) * C(n - i - 1, m - l);
    for (int j = m + 1; j <= r; j++)
      for (int i = 0; i <= n; i++) F[i] = F[i] + C(i, j) * C(n - i, m - j);
  }
}
z sol1() {
  z res = 0;
  for (int u = 1; u <= n; u++) {
    res = res + C(n - 1, m - 1) * sumall[u];
    for (auto &x : A[u]) {
      res = res - F0[x.siz - 1] * (x.sum + x.siz) - F1[x.siz] * (sumall[u] - x.sum - x.siz);
    }
  }
  return res;
}
z sol2() {
  if (m & 1) return 0;
  z res = 0;
  for (int u = 1; u <= n; u++)
    for (auto &x : A[u]) {
      res = res + C(x.siz, m >> 1) * C(n - x.siz, m >> 1) * (inv[x.siz] * (x.sum + x.siz) + inv[n - x.siz] * (sumall[u] - x.sum - x.siz));
    }
  return res * (m >> 1) * finv(2);
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  fac[0] = ifac[0] = inv[0] = inv[1] = 1;
  for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i;
  for (int i = 2; i < N; i++) inv[i] = (mod - mod / i) * inv[mod % i];
  for (int i = 1; i < N; i++) ifac[i] = ifac[i - 1] * inv[i];
  for (cin >> T; T--;) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) G[i].clear(), A[i].clear();
    for (int fa, i = 2; i <= n; i++) {
      cin >> fa;
      G[fa].push_back(i);
    }
    dfs(1);
    dfs2(1, 0);
    for (int u = 1; u <= n; u++) {
      for (int v : G[u]) A[u].push_back({siz[v], sumsub[v]});
      A[u].push_back({n - siz[u], sumall[fa[u]] - sumsub[u] - siz[u]});
    }
    int l = (m >> 1) + 1;
    sol0(n - 1, m - 1, l - 1, m - 1, F0);
    sol0(n - 1, m - 1, l, m, F1);
    cout << (sol1() - sol2()).x << '\n';
  }
}