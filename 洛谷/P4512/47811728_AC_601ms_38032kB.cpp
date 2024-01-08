// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.30 10:18:28
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int i = l; i < r; i++)
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

const int N = 8e5 + 10, mod = 998244353;
int n, m;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
int inv(int x) { return !x || x == 1 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

namespace poly {
	int a[N], b[N], w[N], rev[N];
	using ringo::inv;
	inline void reverse(int *f, int *g, int n) { for (int i = 0; i < n; i++) g[n - i - 1] = f[i]; }
	inline void print(int *a, int n) { for (int i = 0; i < n; i++) ringo::print(a[i], " \n"[i == n - 1]); }
	inline int init(int len) {
		int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
		for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
		for (int len = 1, wn; len < lim; len <<= 1) {
			wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
			for (int i = 1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
		} return lim;
	}
	inline void ntt(int *a, int lim) {
		for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
		for (int len = 1; len < lim; len <<= 1)
			for (int i = 0; i < lim; i += (len << 1))
				for (int j = 0; j < len; j++) {
					int x = a[i + j], y = (ll)w[j + len] * a[i + j + len] % mod;
					a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
				}
	}
	inline void mul(int *f, int *g, int *ans, int n, int m) {
		int lim = init(n + m), inv_lim = inv(lim);
		rep(i, 0, n) a[i] = f[i]; rep(i, n, lim) a[i] = 0;
		rep(i, 0, m) b[i] = g[i]; rep(i, m, lim) b[i] = 0;
		ntt(a, lim), ntt(b, lim);
		for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod;
		std::reverse(a + 1, a + lim), ntt(a, lim);
		for (int i = 0; i < lim; i++) ans[i] = (ll)a[i] * inv_lim % mod;
	}
	inline void inv(int *f, int *g, int n) {
		g[0] = inv(f[0]);
		memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b));
		for (int len = 2; (len >> 1) < n; len <<= 1) {
			memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b));
			int lim = init(len << 1), inv_lim = inv(lim);
			for (int i = 0; i < len; i++) a[i] = f[i], b[i] = g[i];
			ntt(a, lim), ntt(b, lim);
			for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod * b[i] % mod;
			std::reverse(a + 1, a + lim), ntt(a, lim);
			for (int i = 0; i < len; i++) g[i] = ((g[i] << 1) - (ll)a[i] * inv_lim % mod + mod) % mod;
		}
	}
}

void main() {
	static int A[N], B[N], Ar[N], Br[N], Bri[N], Q[N], Qr[N], R[N], T[N];
	read(n), read(m), ++n, ++m;
	rep(i, 0, n) read(A[i]); rep(i, 0, m) read(B[i]);
	poly::reverse(A, Ar, n), poly::reverse(B, Br, m), poly::inv(Br, Bri, n - m + 1);
	poly::mul(Ar, Bri, Qr, n - m + 1, n - m + 1), poly::reverse(Qr, Q, n - m + 1);
	poly::mul(Q, B, T, n, n); for (int i = 0; i < m; i++) R[i] = dec(A[i], T[i]);
	for (int i = 0; i < n - m + 1; i++) print(Q[i], " \n"[i == n - m]);
	for (int i = 0; i < m - 1; i++) print(R[i], " \n"[i == m - 2]);
}

} signed main() { return ringo::main(), 0; }