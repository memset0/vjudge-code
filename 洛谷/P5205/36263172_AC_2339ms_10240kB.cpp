// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.31 13:31:59
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define clear(a) memset(a, 0, sizeof(a))
#define rep(i, l, r) for (int i = (l); i < (r); i++)
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
int n, w[N], rev[N];

inline int dec(int x, int y) { x -= y; return x < 0 ? x + mod : x; }
inline int sub(int x, int y) { x += y; return x >= mod ? x - mod : x; }
int inv(int x) { return !x || x == 1 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline void print(int *a, int n) { for (int i = 0; i < n; i++) print(a[i], " \n"[i == n - 1]); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

inline void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = (ll)a[i + j + len] * w[j + len] % mod;
				a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
			}
}

inline int polyInit(int len) {
	int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
	rep(i, 0, lim) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int len = 1, wn; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
	} return lim;
}

inline void polyMul(int *f, int *g, int *ans, int n, int m, int len) {
	static int a[N], b[N];
	int lim = polyInit(n + m), inv_lim = inv(lim);
	rep(i, 0, n) a[i] = f[i]; rep(i, n, lim) a[i] = 0;
	rep(i, 0, m) b[i] = g[i]; rep(i, m, lim) b[i] = 0;
	ntt(a, lim), ntt(b, lim);
	rep(i, 0, lim) a[i] = (ll)a[i] * b[i] % mod;
	std::reverse(a + 1, a + lim), ntt(a, lim);
	rep(i, 0, len) ans[i] = (ll)a[i] * inv_lim % mod;
}

inline void polyInv(int *f, int *g, int n) {
	static int a[N], b[N]; memset(g, 0, n << 2), clear(a), clear(b);
	g[0] = inv(f[0]);
	for (int len = 2; (len >> 1) < n; len <<= 1) {
		int lim = polyInit(len << 1), inv_lim = inv(lim);
		rep(i, 0, len) a[i] = f[i], b[i] = g[i];
		ntt(a, lim), ntt(b, lim);
		rep(i, 0, lim) a[i] = (ll)a[i] * b[i] % mod * b[i] % mod;
		std::reverse(a + 1, a + lim), ntt(a, lim);
		rep(i, 0, len) g[i] = ((g[i] << 1) - (ll)a[i] * inv_lim % mod + mod) % mod;	
	}
}

inline void polySqrt(int *f, int *g, int n) {
	static int a[N], b[N], c[N];
	g[0] = 1;
	for (int len = 2; (len >> 1) < n; len <<= 1) {
		polyMul(g, g, a, len >> 1, len >> 1, len);
		rep(i, 0, len >> 1) c[i] = sub(g[i], g[i]);
		polyInv(c, b, len);
		rep(i, 0, len) a[i] = sub(a[i], f[i]);
		polyMul(a, b, g, len, len, len);
	}
}

void main() {
	static int a[N], b[N]; read(n);
	rep(i, 0, n) read(a[i]);
	polySqrt(a, b, n);
	rep(i, 0, n) print(b[i], " \n"[i == n - 1]);
}

} signed main() { return ringo::main(), 0; }

/*
	BB = A (n)
	B'B' = A (n/2)
	B - B' = 0 (n/2)
	BB - 2BB' + B'B' = 0 (n)
	A - 2BB' + B'B' = 0 (n)
	B = (A + B'B') / (2B') (n)
*/