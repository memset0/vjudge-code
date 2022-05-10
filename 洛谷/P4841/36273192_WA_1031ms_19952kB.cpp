// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.30 21:12:55
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i = l; i < r; i++)
#define ll long long
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

const int N = 130010 << 2, mod = 998244353;
int n, a[N], b[N], w[N], rev[N], fac[N], inv_fac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
int inv(int x) { return !x || x == 1 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

inline void pOut(int *a, int n) { for (int i = 0; i < n; i++) print(a[i], " \n"[i == n - 1]); }
inline void pInt(int *f, int *g, int n) { for (int i = 1; i < n; i++) g[i - 1] = (ll)f[i] * i % mod; }
inline void pDer(int *f, int *g, int n) { for (int i = 0; i < n - 1; i++) g[i + 1] = (ll)f[i] * inv(i + 1) % mod; }

inline void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = (ll)a[i + j + len] * w[j + len] % mod;
				a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
			}
}

inline int pInit(int len) {
	int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int len = 1, wn; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
	} return lim;
}

inline void pMul(int *f, int *g, int *ans, int n, int m, int len) {
	int lim = pInit(n + m), inv_lim = inv(lim);
	rep(i, 0, n) a[i] = f[i]; rep(i, n, lim) a[i] = 0;
	rep(i, 0, m) b[i] = g[i]; rep(i, m, lim) b[i] = 0;
	ntt(a, lim), ntt(b, lim);
	for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod;
	std::reverse(a + 1, a + lim), ntt(a, lim);
	for (int i = 0; i < len; i++) ans[i] = (ll)a[i] * inv_lim % mod;
}

inline void pInv(int *f, int *g, int n) {
	g[0] = inv(f[0]), memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b));
	for (int len = 2; (len >> 1) < n; len <<= 1) {
		int lim = pInit(len << 1), inv_lim = inv(lim);
		for (int i = 0; i < len; i++) a[i] = f[i], b[i] = g[i];
		ntt(a, lim), ntt(b, lim);
		for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod * b[i] % mod;
		std::reverse(a + 1, a + lim), ntt(a, lim);
		for (int i = 0; i < len; i++) g[i] = ((g[i] << 1) - (ll)a[i] * inv_lim % mod + mod) % mod;
	}
}

inline void pLn(int *f, int *g, int n) {
	static int a[N], b[N], c[N];
	pInv(f, a, n), pInt(f, b, n), pMul(a, b, c, n, n, n), pDer(c, g, n);
}

void main() {
	static int f[N], g[N];
	read(n), ++n, f[0] = f[1] = fac[0] = fac[1] = inv_fac[0] = inv_fac[1] = 1;
	for (int i = 2; i < n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	for (int i = 2; i < n; i++) inv_fac[i] = (ll)(mod - mod / i) * inv_fac[mod % i] % mod;
	for (int i = 2; i < n; i++) inv_fac[i] = (ll)inv_fac[i - 1] * inv_fac[i] % mod;
	for (int i = 2; i < n; i++) f[i] = (ll)fpow(2, (ll)i * (i - 1) / 2 % (mod - 1)) * inv_fac[i] % mod;
	pLn(f, g, n), print((ll)g[n - 1] * fac[n - 1] % mod, '\n');
	// printf(">>> F | "); for (int i = 0; i < n; i++) print((ll)f[i] * fac[i] % mod, " \n"[i == n - 1]);
	// printf(">>> G | "); for (int i = 0; i < n; i++) print((ll)g[i] * fac[i] % mod, " \n"[i == n - 1]);
}

} signed main() { return ringo::main(), 0; }