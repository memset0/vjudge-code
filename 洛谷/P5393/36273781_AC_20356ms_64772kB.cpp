// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.16 09:33:57
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
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

const int N = 2e5 + 10, mod = 998244353;
int n;

int fac[N], ifac[N], w[N << 2], rev[N << 2];
struct poly : std::vector<int> {
    using std::vector<int>::vector;
    inline void in() {
        for (int i = 0; i < size(); i++)
            read(this->operator[](i));
    }
    inline void out() const {
        for (int i = 0; i < size(); i++)
            print(this->operator[](i),  " \n"[i == size() - 1]);
    }
} F[N << 2], f, g, h, ans;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

inline poly resize(poly f, int n) { f.resize(n); return f; }
inline poly reverse(poly f) { std::reverse(f.begin(), f.end()); return f; }

inline int init(int len) {
    int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int wn, len = 1; len < lim; len <<= 1) {
        wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
        for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
    } return lim;
}

inline void ntt(int *a, int lim) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
                a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
            }
}

inline poly operator + (const poly &f, const poly &g) {
    poly h(std::max(f.size(), g.size()));
    for (int i = 0; i < f.size(); i++) h[i] = f[i];
    for (int i = 0; i < g.size(); i++) h[i] = sub(h[i], g[i]);
    return h;
}

inline poly operator - (const poly &f, const poly &g) {
    poly h(std::max(f.size(), g.size()));
    for (int i = 0; i < f.size(); i++) h[i] = f[i];
    for (int i = 0; i < g.size(); i++) h[i] = dec(h[i], g[i]);
    return h;
}

inline poly operator * (const poly &f, const poly &g) {
    if ((ll)f.size() * g.size() <= 1000) {
        poly h(f.size() + g.size() - 1);
        for (int i = 0; i < f.size(); i++)
            for (int j = 0; j < g.size(); j++)
                h[i + j] = (h[i + j] + (ll)f[i] * g[j]) % mod;
        return h;
    }
    static int a[N << 2], b[N << 2];
    static poly h; h.resize(f.size() + g.size() - 1); int lim = init(h.size()), inv_lim = inv(lim);
    for (int i = 0; i < lim; i++) a[i] = i < f.size() ? f[i] : 0;
    for (int i = 0; i < lim; i++) b[i] = i < g.size() ? g[i] : 0;
    ntt(a, lim), ntt(b, lim);
    for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
    std::reverse(a + 1, a + lim), ntt(a, lim);
    for (int i = 0; i < h.size(); i++) h[i] = mul(a[i], inv_lim);
    return h;
}

inline poly inv(const poly &f) {
    static int a[N << 2], b[N << 2];
    poly g(1, inv(f[0]));
    for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
        int lim = init(len << 1), inv_lim = inv(lim);
        for (int i = 0; i < std::min((int)f.size(), len); i++) a[i] = f[i];
        for (int i = std::min((int)f.size(), len); i < lim; i++) a[i] = 0;
        for (int i = 0; i < (len >> 1); i++) b[i] = g[i];
        for (int i = (len >> 1); i < lim; i++) b[i] = 0;
        ntt(a, lim), ntt(b, lim);
        for (int i = 0; i < lim; i++) a[i] = mul(a[i], mul(b[i], b[i]));
        std::reverse(a + 1, a + lim), ntt(a, lim);
        for (int i = len >> 1; i < len && i < f.size(); i++)
            g.push_back(dec(0, mul(a[i], inv_lim)));
    } return g;
}

inline poly operator % (const poly &f, const poly &g) {
    int len = f.size() - g.size() + 1;
    if (len < 0) return f;
    poly F = f; std::reverse(F.begin(), F.end()); F.resize(len);
    poly G = g; std::reverse(G.begin(), G.end()); G.resize(len);
    poly q = F * inv(G); q.resize(len); std::reverse(q.begin(), q.end());
    return resize(f - q * g, g.size() - 1);
}

inline poly deri(const poly &f) {
    poly g(f.size());
    for (int i = 0; i < f.size() - 1; i++) g[i] = mul(i + 1, f[i + 1]);
    return g;
}

void build(int u, int l, int r) {
    if (l == r) { F[u] = poly{dec(0, l), 1}; return; }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    F[u] = F[u << 1] * F[u << 1 | 1];
}

void MPE(int u, int l, int r, const poly &f, const poly &y, poly &res) {
    if (l == r) { res[l] = mul(y[l], inv(f[0])); return; }
    int mid = (l + r) >> 1;
    MPE(u << 1, l, mid, f % F[u << 1], y, res);
    MPE(u << 1 | 1, mid + 1, r, f % F[u << 1 | 1], y, res);
}

poly FIP(int u, int l, int r, const poly &a) {
    if (l == r) { return poly(1, a[l]); }
	int mid = (l + r) >> 1;
    return FIP(u << 1, l, mid, a) * F[u << 1 | 1] + FIP(u << 1 | 1, mid + 1, r, a) * F[u << 1];
}

void main() {
    read(n), f.resize(n), g.resize(n), h.resize(n), f.in();
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= n; i++) fac[i] = mul(fac[i - 1], i);
    for (int i = 2; i <= n; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
    for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	for (int i = 0; i < n; i++) g[i] = ifac[i];
	g = f * g, g.resize(n);
	for (int i = 0; i < n; i++) g[i] = mul(g[i], fac[i]);
    build(1, 0, n - 1);
    MPE(1, 0, n - 1, deri(F[1]), g, h);
    FIP(1, 0, n - 1, h).out();
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}