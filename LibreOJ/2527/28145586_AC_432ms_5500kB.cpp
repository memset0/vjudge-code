// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.20 12:54:07
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

const int N = 4e5 + 10, mod = 1004535809;
int n, m, s, k, ans, lim = 1, inv_lim;
int a[N], f[N], g[N], w[N], rev[N], fac[N], ifac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
				a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
			}
}

void main() {
	read(n), read(m), read(s);
	for (int i = 0; i <= m; i++) read(a[i]);
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= std::max(m, s); i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= std::max(m, s); i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= std::max(m, s); i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	for (int i = 0; i <= m; i++) f[i] = mul(a[i], ifac[i]);
	for (int i = 0; i <= m; i++) g[i] = i & 1 ? mod - ifac[i] : ifac[i];
	// print(f, 0, m, "f"), print(g, 0, m, "g");
	while (lim <= (m << 1)) lim <<= 1, ++k; inv_lim = inv(lim);
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int wn, len = 1; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = mul(wn, w[i + len - 1]);
	}
	ntt(f, lim), ntt(g, lim);
	for (int i = 0; i < lim; i++) g[i] = mul(f[i], g[i]);
	std::reverse(g + 1, g + lim), ntt(g, lim);
	for (int i = 0; i <= m; i++) g[i] = mul(g[i], inv_lim);
	for (int i = 0, tmp = 1; i <= m; i++) if (n >= i * s) {
		f[i] = mul(fac[m], mul(ifac[i], mul(fpow(ifac[s], i), mul(ifac[m - i], mul(fpow(m - i, n - i * s), tmp)))));
		for (int j = 0; j < s; j++) tmp = mul(tmp, n - i * s - j);
	} else f[i] = 0;
	// print(f, 0, m, "f"), print(g, 0, m, "g");
	// print(fac, 0, m, "fac"), print(ifac, 0, m, "ifac");
	for (int i = 0; i <= m; i++) ans = inc(ans, mul(fac[i], mul(f[i], g[i])));
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}