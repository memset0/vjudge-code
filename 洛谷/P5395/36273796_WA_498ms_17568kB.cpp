// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.16 20:24:20
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

const int N = 8e5 + 10, mod = 998244353;
int n, k, lim = 1, inv_lim, f[N], g[N], fac[N], ifac[N], w[N], rev[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void ntt(int *a) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
				a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
			}
}

void main() {
	read(n);
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= n; i++) fac[i] = mul(fac[i], i);
	for (int i = 2; i <= n; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	for (int i = 0; i <= n; i++) f[i] = mul(fpow(i, n), ifac[i]), g[i] = i & 1 ? mod - ifac[i] : ifac[i];
	while (lim < ((n << 1) + 2)) lim <<= 1, ++k; inv_lim = inv(lim);
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int wn, len = 1; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
	}
	ntt(f), ntt(g);
	for (int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
	std::reverse(f + 1, f + lim), ntt(f);
	for (int i = 0; i < lim; i++) f[i] = mul(f[i], inv_lim);
	for (int i = 0; i <= n; i++) print(f[i], " \n"[i == n]);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}