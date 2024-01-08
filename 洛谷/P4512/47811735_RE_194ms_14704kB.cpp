// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.17 22:21:00
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
#define poly std::vector <int>
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

const int N = 6e4 + 10, mod = 998244353;
int n, b[N], w[N << 2], rev[N << 2];
poly F[N << 2];

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
	static int a[N << 2], b[N << 2];
	poly h(f.size() + g.size() - 1); int lim = init(h.size()), inv_lim = inv(lim);
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
    for (size_t i = 0; i < q.size(); i++) print(q[i], " \n"[i == q.size() - 1]);
    return resize(f - q * g, g.size() - 1);
}

inline poly deri(const poly &f) {
    poly g(f.size());
    for (int i = 1; i < n; i++) g[i - 1] = mul(f[i], i);
    return g;
}

poly solve1(int l, int r) {
	if (l == r) return poly{1, dec(0, b[l])};
	int mid = (l + r) >> 1;
    return solve1(l, mid) * solve1(mid + 1, r);
}

void solve2(int l, int r, int u) {
	if (l == r) { F[u] = poly{dec(0, inv(b[l])), 1}; return; }
	int mid = (l + r) >> 1;
    solve2(l, mid, u << 1);
    solve2(mid + 1, r, u << 1 | 1);
    F[u] = F[u << 1] * F[u << 1 | 1];
}

void solve3(int l, int r, int u) {
    if (l == r) { F[u] = poly{dec(0, b[l]), 0}; return; }
    int mid = (l + r) >> 1;
    solve3(l, mid, u << 1);
    solve3(mid + 1, r, u << 1 | 1);
    F[u] = F[u << 1] * F[u << 1 | 1];
}

void MPE(int l, int r, poly f, poly &a, int u) {
    if (l == r) { a[l] = f[0]; return; }
    int mid = (l + r) >> 1;
    MPE(l, mid, f % F[u << 1], a, u << 1);
    MPE(mid + 1, r, f % F[u << 1 | 1], a, u << 1 | 1);
}

// void main() {
// 	read(n);
//     poly a(n), c(n), d(n), h(n);
// 	for (int i = 0; i < n; i++) read(b[i]);
// 	for (int i = 0; i < n; i++) read(h[i]);
//     solve2(0, n - 1, 1), MPE(0, n - 1, resize(h * solve1(0, n - 1), n), c, 1);
//     solve3(0, n - 1, 1), MPE(0, n - 1, resize(deri(F[1]), n), d, 1);
//     for (int i = 0; i < n; i++) a[i] = mul(c[i], mul(inv(d[i]), fpow(b[i], n - 1)));
//     for (int i = 0; i < n; i++) print(a[i], " \n"[i == n - 1]);
//     for (int i = 0; i < n; i++) print(b[i], " \n"[i == n - 1]);
//     for (int i = 0; i < n; i++) print(c[i], " \n"[i == n - 1]);
//     for (int i = 0; i < n; i++) print(d[i], " \n"[i == n - 1]);
//     for (int i = 0; i < n; i++) print(h[i], " \n"[i == n - 1]);
// }

// void main() {
//     int n, m, l;
//     read(n), read(m), ++n, l = std::max(n, m);
//     std::vector <int> a(l), c(l);
//     for (int i = 0; i < n; i++) read(a[i]);
//     for (int i = 0; i < m; i++) read(b[i]);
//     solve3(0, n - 1, 1), MPE(0, n - 1, a, c, 1);
//     for (size_t i = 0; i < c.size(); i++) print(c[i], ' ');
// }

void main() {
    int n, m;
    read(n), read(m), ++n, ++m;
    poly a(n), b(m);
    for (int i = 0; i < n; i++) read(a[i]);
    for (int i = 0; i < m; i++) read(b[i]);
    auto c = a % b;
    for (size_t i = 0; i < c.size(); i++) print(c[i], ' ');
}

} signed main() { return ringo::main(), 0; }