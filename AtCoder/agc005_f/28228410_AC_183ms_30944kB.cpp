// =================================
//   author: memset0
//   date: 2019.01.25 22:26:04
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
namespace ringo {
template <class T> inline void read(T &x) {
	x = 0; register char c = getchar(); register bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}
template <class T> inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }

const int N = 2e5 + 10, mod = 924844033;
int n, k, lim = 1, inv_lim;
int f[N << 2], g[N << 2], w[N << 2], rev[N << 2];;
int cnt[N], fac[N], fac_inv[N], fa[N], siz[N], ans[N];
int tot = 2, hed[N], to[N << 1], nxt[N << 1];

inline int C(int n, int m) { return (ll)fac[n] * fac_inv[m] % mod * fac_inv[n - m] % mod; }
inline int inv(int x) { return !x || x == 1 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) {
    int s = 1;
    for (; b; b >>= 1, a = (ll)a * a % mod)
        if (b & 1) s = (ll)s * a % mod;
    return s;
}

void ntt(int *a, int lim) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = (ll)w[j + len] * a[i + j + len] % mod;
                a[i + j] = (x + y) % mod, a[i + j + len] = (x - y + mod) % mod;
            }
}

void dfs(int u) {
    siz[u] = 1;
    for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
        if (v != fa[u]) {
            fa[v] = u, dfs(v), siz[u] += siz[v];
        }
    ++cnt[n - siz[u]];
    if (u != 1) ++cnt[siz[u]];
}

void main() {
    read(n), fac[0] = fac[1] = fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
    for (int i = 2; i <= n; i++) fac_inv[i] = inv(fac[i]);
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
        nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
    } dfs(1);

    while (lim <= (n + 1 + n + 1)) lim <<= 1, ++k;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int len = 1, wn; len < lim; len <<= 1) {
        wn = fpow(5, (mod - 1) / (len << 1)), w[len] = 1;
        for (int i = 1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
    }
    for (int i = 0; i <= n; i++) f[i] = (ll)cnt[i] * fac[i] % mod;
    for (int i = 0; i <= n; i++) g[i] = fac_inv[n - i];
    // for (int i = 0; i < lim; i++) print(f[i], " \n"[i == lim - 1]);
    // for (int i = 0; i < lim; i++) print(g[i], " \n"[i == lim - 1]);
    ntt(f, lim), ntt(g, lim), inv_lim = inv(lim);
    for (int i = 0; i < lim; i++) f[i] = (ll)f[i] * g[i] % mod;
    std::reverse(f + 1, f + lim), ntt(f, lim);
    for (int i = 0; i < lim; i++) f[i] = (ll)f[i] * inv_lim % mod;
    // for (int i = 0; i < lim; i++) print(f[i], " \n"[i == lim - 1]);
    for (int i = 1; i <= n; i++) ans[i] = (ll)f[i + n] * fac_inv[i] % mod;
    for (int i = 1; i <= n; i++) ans[i] = ((ll)n * C(n, i) - ans[i] + mod) % mod;
    for (int i = 1; i <= n; i++) print(ans[i], " \n"[i == n]);
}

} signed main() { return ringo::main(), 0; }