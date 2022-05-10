// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.27 22:40:38
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
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

const int N = 4e5 + 10, mod = 998244353;
int T, n;
int a[N], f[N], g[N], h[N], w[N], rev[N];

int inv(int x) { return !x || x == 1 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

inline void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = (ll)w[j + len] * a[i + j + len] % mod;
				a[i + j] = (x + y) % mod, a[i + j + len] = (x - y + mod) % mod;
			}
}

inline int init(int len) {
	int lim = 1, k = 0;
	while (lim < len) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int len = 1, wn; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
	}
	return lim;
}

void polyMul(int *f, int *g, int len) {
	static int a[N], b[N];
	int lim = init(len << 1), inv_lim = inv(lim);
	for (int i = 0; i < lim; i++) a[i] = f[i], b[i] = g[i];
	ntt(a, lim), ntt(b, lim);
	for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod;
	std::reverse(a + 1, a + lim), ntt(a, lim);
	for (int i = 0; i < lim; i++) f[i] = (ll)a[i] * inv_lim % mod;
}

void polyInv(int *f, int *g, int n) {
	static int a[N], b[N];
	g[0] = inv(f[0]);
	for (int len = 2; (len >> 1) < n; len <<= 1) {
		int lim = init(len << 1), inv_lim = inv(lim);
		for (int i = 0; i < len; i++) a[i] = f[i], b[i] = g[i];
		ntt(a, lim), ntt(b, lim);
		for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod * b[i] % mod;
		std::reverse(a + 1, a + lim), ntt(a, lim);
		for (int i = 0; i < len; i++) g[i] = ((g[i] << 1) - (ll)a[i] * inv_lim % mod + mod) % mod;
	}
}

void main() {
	read(T);
	for (int i = 1; i <= T; i++) read(a[i]), n = std::max(n, a[i] + 1);
	h[0] = h[1] = 1;
	for (int i = 2; i < n; i++) h[i] = (ll)(mod - mod / i) * h[mod % i] % mod;
	for (int i = 2; i < n; i++) h[i] = (ll)h[i] * h[i - 1] % mod;
	for (int i = 1; i < n; i++) if (h[i]) h[i] = mod - h[i];
	polyInv(h, g, n);
	for (int i = 1; i < n; i++) f[i] = g[i];
	polyMul(f, g, n);
	for (int i = 1; i <= T; i++) print((ll)f[a[i]] * inv(g[a[i]]) % mod, '\n');
}

} signed main() { return ringo::main(), 0; }