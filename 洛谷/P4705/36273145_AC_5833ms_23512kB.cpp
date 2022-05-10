// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.03 23:41:02
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define vector std::vector <int>
#define rep(i, l, r) for (int i = (l), __lim = (r); i < __lim; ++i)
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

const int N = 4e5 + 10, mod = 998244353;
int n, m, t, a[N], b[N], f[N], g[N], h[N], w[N], rev[N], fac[N], inv_fac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int g_lim(int n) { int l = 1; while (l < n) l <<= 1; return l; }
int inv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline void print(int *a, int lim) { rep(i, 0, lim) print(a[i], " \n"[i == lim - 1]); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

inline int init(int len) {
    int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
    rep(i, 0, lim) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    return lim;
}

inline void ntt(int *a, int lim) {
    rep(i, 0, lim) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = (ll)a[i + j + len] * w[j + len] % mod;
                a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
            }
}

inline vector operator * (const vector &f, const vector &g) {
    static int a[N], b[N]; static vector h; h.clear();
    int lim = init(f.size() + g.size()), inv_lim = inv(lim);
    rep(i, 0, f.size()) a[i] = f[i]; memset(&a[f.size()], 0, (lim - f.size()) << 2);
    rep(i, 0, g.size()) b[i] = g[i]; memset(&b[g.size()], 0, (lim - g.size()) << 2);
    ntt(a, lim), ntt(b, lim);
    rep(i, 0, lim) a[i] = (ll)a[i] * b[i] % mod;
    std::reverse(a + 1, a + lim), ntt(a, lim);
    rep(i, 0, f.size() + g.size() - 1) h.push_back((ll)a[i] * inv_lim % mod);
    return h;
}

vector solve(int l, int r, int *a) {
    static vector F;
    if (l == r) { F.clear(), F.push_back(1), F.push_back(a[l] ? mod - a[l] : 0); return F; }
    int mid = (l + r) >> 1; 
    return solve(l, mid, a) * solve(mid + 1, r, a);
}

inline void mul(int *f, int *g, int *h, int n, int m, int l) {
    static int a[N], b[N];
    int lim = init(n + m), inv_lim = inv(lim);
    rep(i, 0, n) a[i] = f[i]; memset(&a[n], 0, (lim - n) << 2);
    rep(i, 0, m) b[i] = g[i]; memset(&b[n], 0, (lim - m) << 2);
    ntt(a, lim), ntt(b, lim);
    rep(i, 0, lim) a[i] = (ll)a[i] * b[i] % mod;
    std::reverse(a + 1, a + lim), ntt(a, lim);
    rep(i, 0, l) h[i] = (ll)a[i] * inv_lim % mod;
}

inline void inv(int *f, int *g, int n) {
    static int a[N], b[N]; int tmp = g_lim(n);
    memset(a, 0, tmp << 3);
    memset(b, 0, tmp << 3);
    memset(g, 0, tmp << 2);
    g[0] = inv(f[0]);
    for (int len = 2; (len >> 1) < n; len <<= 1) {
        int lim = init(len << 1), inv_lim = inv(lim);
        rep(i, 0, len) a[i] = f[i], b[i] = g[i];
        ntt(a, lim), ntt(b, lim);
        rep(i, 0, lim) a[i] = (ll)a[i] * b[i] % mod * b[i] % mod;
        std::reverse(a + 1, a + lim), ntt(a, lim);
        rep(i, 0, len) g[i] = ((g[i] << 1) - (ll)a[i] * inv_lim % mod + mod) % mod;
    }
}

inline void deri(int *f, int *g, int n) { for (int i = 1; i < n; i++) g[i - 1] = (ll)f[i] * i % mod; }
inline void inte(int *f, int *g, int n) { for (int i = 0; i < n - 1; i++) g[i + 1] = (ll)f[i] * inv(i + 1) % mod; }

inline void ln(int *f, int *g, int n) {
    static int a[N], b[N], c[N]; memset(a, 0, n << 2), memset(b, 0, n << 2), memset(c, 0, n << 2), memset(g, 0, n << 2);
    deri(f, a, n), inv(f, b, n), mul(a, b, c, n, n, n), inte(c, g, n);
}

inline void make(int *a, int n, int *f) {
    static int b[N];
    vector F = solve(1, n, a);
    // for (auto x : F) print(x, ' '); puts("");
    rep(i, 0, std::min(t, (int)F.size())) b[i] = F[i];
    rep(i, F.size(), t) b[i] = 0;
    ln(b, f, t);
    rep(i, 1, t) f[i] = dec(0, (ll)f[i] * i % mod * inv_fac[i] % mod);
    f[0] = n;
    // rep(i, 0, t) print(f[i], " \n"[i == t - 1]);
}

void main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1; i <= m; i++) read(b[i]);
    read(t), ++t;
	for (int len = 1, wn, lim = std::min((std::max(n, std::max(m, t)) << 2) + 1000, N); len < lim; len <<= 1) {
        wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
        rep(i, 1, len) w[i + len] = (ll)w[i + len - 1] * wn % mod;
    }
    fac[0] = fac[1] = inv_fac[0] = inv_fac[1] = 1;
    rep(i, 2, t) fac[i] = (ll)fac[i - 1] * i % mod;
    rep(i, 2, t) inv_fac[i] = (ll)(mod - mod / i) * inv_fac[mod % i] % mod;
    rep(i, 2, t) inv_fac[i] = (ll)inv_fac[i - 1] * inv_fac[i] % mod;
    make(a, n, f), make(b, m, g);
    mul(f, g, h, t, t, t);
    // rep(i, 0, t) print(h[i], " \n"[i == t - 1]);
    int tmp = inv((ll)n * m % mod);
    rep(i, 1, t) h[i] = (ll)h[i] * tmp % mod * fac[i] % mod;
    rep(i, 1, t) print(h[i], '\n');
}

} signed main() { return ringo::main(), 0;  }