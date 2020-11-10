// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.06 18:51:05
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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
int n, k, lim, ans, inv_lim;
int f[N], g[N], w[N], rev[N], fac[N], inv_fac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
template <class T> inline int _(T x) { x %= mod; return x < 0 ? x + mod : x; }
int inv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

void ntt(int *a) {
	rep(i, 0, lim) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = (ll)a[i + j + len] * w[j + len] % mod;
				a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
			}
}

void main() {
	read(n), ++n, lim = fac[0] = fac[1] = inv_fac[0] = inv_fac[1] = 1;
	rep(i, 2, n) fac[i] = (ll)fac[i - 1] * i % mod;
	rep(i, 2, n) inv_fac[i] = (ll)(mod - mod / i) * inv_fac[mod % i] % mod;
	rep(i, 2, n) inv_fac[i] = (ll)inv_fac[i - 1] * inv_fac[i] % mod;
	while (lim < (n << 1)) lim <<= 1, ++k;
	rep(i, 0, lim) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int len = 1, wn; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		rep(i, 1, len) w[i + len] = (ll)w[i + len - 1] * wn % mod;
	} inv_lim = inv(lim);
	rep(i, 0, n) f[i] = _((i & 1 ? -1 : 1) * inv_fac[i]);
	rep(i, 0, n) g[i] = _((ll)(fpow(i, n) - 1) * inv(i - 1) % mod * inv_fac[i]);
	g[0] = 1, g[1] = n;
	// rep(i, 0, lim) print(f[i], " \n"[i == lim - 1]);
	// rep(i, 0, lim) print(g[i], " \n"[i == lim - 1]);
	ntt(f), ntt(g);
	rep(i, 0, lim) f[i] = (ll)f[i] * g[i] % mod;
	std::reverse(f + 1, f + lim), ntt(f);
	rep(i, 0, lim) f[i] = (ll)f[i] * inv_lim % mod * fpow(2, i) % mod * fac[i] % mod;
	// rep(i, 0, lim) print(f[i], " \n"[i == lim - 1]);
	rep(i, 0, n) ans = (ans + f[i]) % mod;
	print((ans + mod) % mod, '\n');
}

} signed main() { return ringo::main(), 0; }
