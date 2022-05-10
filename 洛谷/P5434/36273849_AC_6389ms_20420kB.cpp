// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.06.25 15:26:16
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int (i) = (l), __lim = (r); (i) <= __lim; (i)++)
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
namespace ringo {

template <class T> inline void read(T &x) {
	x = 0; char c = getchar(); bool f = 0;
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 262150, mod = 998244353;

inline int opp(int x) { return x == 0 ? 0 : mod - x; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

struct poly : std::vector <int> {
    using std::vector <int> ::vector;
    void in() { for (int i = 0; i < size(); i++) read(at(i)); }
    void out() const { for (int i = 0; i < size(); i++) print(at(i), " \n"[i == size() - 1]); }
};

int w[N << 2], rev[N << 2];
inline int init(int len) {
    int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    static int last = 1;
    for (int wn, len = last; len < lim; last = len <<= 1) {
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
                a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
            }
}

inline poly mul(const poly &f, const poly &g, int len = -1) {
    static int a[N << 2], b[N << 2];
    static poly h; h.resize(f.size() + g.size() - 1);
    int lim = init(h.size()), inv_lim = inv(lim);
    memcpy(a, &f[0], f.size() << 2), memset(a + f.size(), 0, (lim - f.size()) << 2);
    memcpy(b, &g[0], g.size() << 2), memset(b + g.size(), 0, (lim - g.size()) << 2);
    ntt(a, lim), ntt(b, lim);
    for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
    std::reverse(a + 1, a + lim), ntt(a, lim);
	if (~len) h.resize(len);
    for (int i = 0; i < h.size(); i++) h[i] = mul(a[i], inv_lim);
    return h;
}

inline poly inv(const poly &f) {
    static int a[N << 2], b[N << 2];
    static poly g; g.resize(f.size()), g[0] = inv(f[0]);
    for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
        int lim = init(len << 1), inv_lim = inv(lim);
        for (int i = 0; i < lim; i++) a[i] = i < f.size() && i < len ? f[i] : 0;
        for (int i = 0; i < lim; i++) b[i] = i < (len >> 1) ? g[i] : 0;
        ntt(a, lim), ntt(b, lim);
        for (int i = 0; i < lim; i++) a[i] = mul(a[i], mul(b[i], b[i]));
        std::reverse(a + 1, a + lim), ntt(a, lim);
        for (int i = len >> 1; i < len && i < g.size(); i++) g[i] = dec(0, mul(a[i], inv_lim));
    } return g;
}

inline poly ln(poly f) {
    static poly g; g.resize(f.size());
    for (int i = 1; i < f.size(); i++) g[i - 1] = mul(f[i], i);
    g = mul(inv(f), g), g.resize(f.size()), f[0] = 0;
    for (int i = 0; i < f.size() - 1; i++) f[i + 1] = mul(g[i], inv(i + 1));
    return f;
}

inline poly exp(const poly &f) {
    static poly g, h, t; g.clear(), g.push_back(1);
    for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
        g.resize(len), h = ln(g), t.resize(len), h.resize(len);
        for (int i = 0; i < len; i++) h[i] = dec(i < f.size() ? f[i] : 0, h[i]);
        for (int i = 0; i < len; i++) t[i] = i < g.size() ? g[i] : 0;
        h[0] = inc(h[0], 1), h = mul(h, t, len), g.resize(len);
        for (int i = len >> 1; i < len; i++) g[i] = h[i];
    } g.resize(f.size()); return g;
}

inline poly cactus(int n) {
	static poly f, g, f2, ff, t1, t2;
	f.resize(2), f[0] = 0, f[1] = 1;
	for (int len = 4; (len >> 1) < n; len <<= 1) {
		f2.clear(), ff.clear();
		g.clear(), t1.clear(), t2.clear();
		f.resize(len), f2.resize(len), ff.resize(len);
		g.resize(len), t1.resize(len), t2.resize(len);
		// 2 F(x) => f2
		for (int i = 0; i < len; i++) f2[i] = inc(f[i], f[i]);
		// F^2(x) => ff
		ff = mul(f, f, len);
		// 2 F(x) - F^2(x) => t1
		for (int i = 0; i < len; i++) t1[i] = dec(f2[i], ff[i]);
		// 2 - 2F(x) => t2
		for (int i = 0; i < len; i++) t2[i] = opp(f2[i]);
		t2[0] = inc(t2[0], 2);
		// x \exp t1 * t2^{-1} => g
		g = exp(mul(t1, inv(t2), len));
		for (int i = len - 1; i > 0; i--) g[i] = g[i - 1];
		g[0] = 0;
		// 2 G(x) - 2 F(x) => t1
		for (int i = 0; i < len; i++) t1[i] = dec(inc(g[i], g[i]), f2[i]);
		// (1 + (F(x) - 1)^{-2}) G(x) - 2 => t2
		for (int i = 0; i < len; i++) t2[i] = dec(ff[i], f2[i]);
		t2[0] = inc(t2[0], 1);
		t2 = inv(t2), t2[0] = inc(t2[0], 1);
		t2 = mul(t2, g, len), t2[0] = dec(t2[0], 2);
		// - t1 * t2^{-1} => g	
		g = mul(t1, inv(t2), len);
		for (int i = 0; i < len; i++) f[i] = dec(f[i], g[i]);
		// f.out();
	}
	f.resize(n);
	for (int i = 1; i < n; i++) f[i] = mul(f[i], inv(i));
	return f;
}

void main() {
	static int n, ans;
	read(n), ans = exp(cactus(n + 1))[n];
	for (int i = 1; i <= n; i++) ans = mul(ans, i);
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
#endif
    return ringo::main(), 0;
}