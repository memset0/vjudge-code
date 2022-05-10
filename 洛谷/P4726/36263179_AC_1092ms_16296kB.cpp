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
inline char read() {
	static const int IN_LEN = 1000000; static char buf[IN_LEN], *s, *t;
	return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}
template <class T> inline void read(T &x) {
	static bool f; static char c;
	for (f = 0, c = read(); !isdigit(c); c = read()) { f ^= c == '-'; if (c == -1) return; }
	for (x = 0; isdigit(c); c = read()) x = ((x + (x << 2)) << 1) + (c ^ '0');
	if (f) x = -x;
}
const int OUT_LEN = 10000000; char obuf[OUT_LEN], *ooh = obuf;
inline void print(char c) {
	if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
	*ooh++ = c;
}
template <class T> inline void print(T x) {
	static int buf[30], cnt;
	if (!x) { print('0'); return; }
	if (x < 0) print('-'), x = -x;
	for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + '0';
	while (cnt) print((char)buf[cnt--]);
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
template <class T> inline void print(T x, char c) { print(x), print(c); }

const int N = 1e5 + 10, mod = 998244353;

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
    static poly h; h.resize(len = ~len ? len : f.size() + g.size() - 1);
    int lim = init(len), inv_lim = inv(lim);
	int n = std::min((int)f.size(), lim >> 1); memcpy(a, &f[0], n << 2), memset(a + n, 0, (lim - n) << 2);
    int m = std::min((int)g.size(), lim >> 1); memcpy(b, &g[0], m << 2), memset(b + m, 0, (lim - m) << 2);
    ntt(a, lim), ntt(b, lim);
    for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
    std::reverse(a + 1, a + lim), ntt(a, lim);
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
    static poly g, h, t; g.resize(f.size()), g[0] = 1;
    for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
        t.resize(len), g.resize(len), h = ln(g);
        for (int i = 0; i < f.size() && i < len; i++) h[i] = dec(f[i], h[i]);
		for (int i = f.size(); i < len; i++) h[i] = opp(h[i]);
		memcpy(&t[0], &g[0], len << 1);
        memset(&t[len >> 1], 0, len << 1);
        h[0] = h[0] == mod - 1 ? 0 : h[0] + 1, h = mul(h, t);
        for (int i = len >> 1; i < len; i++) g[i] = h[i];
    } g.resize(f.size()); return g;
}

void main() {
    int n; read(n);
	poly f(n); f.in();
	// exp(exp(f));
	exp(f).out();
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
    return ringo::main(), ringo::flush(), 0;
}