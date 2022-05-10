// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.24 22:02:35
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

const int N = 1e5 + 10, mod = 998244353;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

template <class T> void read_mod(T &x, int mod) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (isdigit(c)) x = ((ll)x * 10 + c - '0') % mod, c = getchar();
}

struct poly : std::vector <int> {
    using std::vector <int> ::vector;
    void in() { for (int i = 0; i < size(); i++) read(at(i)); }
    void out() const { for (int i = 0; i < size(); i++) print(at(i), " \n"[i == size() - 1]); }
};

int w[N << 2], rev[N << 2];
inline int init(int len) {
    int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int wn, len = 1; len < lim; len <<= 1) {
        wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
        for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
    } return lim;
}

void ntt(int *a, int lim) {
    for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
                a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
            }
}

inline poly operator * (const poly &f, const poly &g) {
    static int a[N << 2], b[N << 2]; poly h(f.size() + g.size() - 1);
    int lim = init(h.size()), inv_lim = inv(lim);
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
        for (int i = 0; i < lim; i++) a[i] = i < f.size() && i < len ? f[i] : 0;
        for (int i = 0; i < lim; i++) b[i] = i < g.size() ? g[i] : 0;
        ntt(a, lim), ntt(b, lim);
        for (int i = 0; i < lim; i++) a[i] = mul(a[i], mul(b[i], b[i]));
        std::reverse(a + 1, a + lim), ntt(a, lim);
        for (int i = len >> 1; i < len; i++) g.push_back(dec(0, mul(a[i], inv_lim)));
    } g.resize(f.size()); return g;
}

inline poly ln(poly f) {
    poly g(f.size());
    for (int i = 1; i < f.size(); i++) g[i - 1] = mul(f[i], i);
    g = inv(f) * g, g.resize(f.size()), f[0] = 0;
    for (int i = 0; i < f.size() - 1; i++) f[i + 1] = mul(g[i], inv(i + 1));
    return f;
}

inline poly exp(const poly &f) {
    poly g(1, 1), h, t;
    for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
        g.resize(len), h = ln(g), t.resize(len), h.resize(len);
        for (int i = 0; i < len; i++) h[i] = dec(i < f.size() ? f[i] : 0, h[i]);
        for (int i = 0; i < len; i++) t[i] = i < g.size() ? g[i] : 0;
        h[0] = sub(h[0], 1), h = h * t;
        for (int i = len >> 1; i < len; i++) g[i] = h[i];
    } g.resize(f.size()); return g;
}

inline poly fpow(poly a, int b) {
    int n = a.size(); poly s(1, 1);
    for (; b; b >>= 1, a = a * a, a.resize(n))
        if (b & 1) s = s * a, s.resize(n);
    s.resize(n); return s;
}

void main() {
    int n, k;
    read(n), read(k);
    // read_mod(k, mod);
    poly f(n); f.in();
    f = fpow(f, k);
    // f = ln(f);
    // for (int i = 0; i < n; i++) f[i] = mul(f[i], k);
    // f = exp(f);
    f.out();
}

} signed main() { return ringo::main(), 0; }
