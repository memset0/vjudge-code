// =================================
//   author: memset0
//   date: 2019.03.19 20:24:14
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

const int N = 2e4 + 10, mod = 998244353;
int n, m, x, ans, fac[N], ifac[N], w[N << 2], rev[N << 2];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
				a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
			}
}

int init(int len) {
	int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int wn, len = 1; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
	} return lim;
}

struct poly : std::vector <int> {
	using std::vector <int> :: vector;
	friend inline poly operator * (const poly &f, const poly &g) {
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
};

void main() {
	read(n), read(m), read(x);
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= m; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= m; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= m; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	poly f(m + 1), g(m + 1);
	for (int i = 0, x; i <= m; i++) read(x), f[i] = mul(x, ifac[i]);
	for (int i = 0; i <= m; i++) g[i] = i & 1 ? dec(0, ifac[i]) : ifac[i];
	poly h = f * g; h.resize(m + 1);
	// for (int i = 0; i <= m; i++) print(f[i], " \n"[i == m]);
	// for (int i = 0; i <= m; i++) print(g[i], " \n"[i == m]);
	// for (int i = 0; i <= m; i++) print(h[i], " \n"[i == m]);
	for (int i = 0, tmp = 1, now = n; i <= m; i++) {
		ans = (ans + (ll)h[i] * fpow(x, i) % mod * tmp) % mod;
		tmp = mul(tmp, now--);
		// for (int i = 0; i <= m; i++) printf(">> %d %d %d\n", h[i], fpow(x, i), tmp);
	}
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }