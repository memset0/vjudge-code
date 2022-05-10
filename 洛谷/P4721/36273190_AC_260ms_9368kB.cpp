// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.27 17:03:22
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
int n, lim;
int f[N], g[N], a[N], b[N], w[N], rev[N];

int inv(int x) { return !x || x == 1 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

void ntt(int *a) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = (ll)w[j + len] * a[i + j + len] % mod;
				a[i + j] = (x + y) % mod, a[i + j + len] = (x - y + mod) % mod;
			}
}

void polyInv(int *f, int *g) {
	g[0] = inv(f[0]);
	for (int len = 2, k = 2, inv_lim; (len >> 1) < n; len <<= 1, ++k) {
		lim = len << 1, inv_lim = inv(lim);
		for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
		for (int len = 1, wn; len < lim; len <<= 1) {
			wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
			for (int i = 1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
		}
		for (int i = 0; i < len; i++) a[i] = f[i], b[i] = g[i];
		ntt(a), ntt(b);
		for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod * b[i] % mod;
		std::reverse(a + 1, a + lim), ntt(a);
		for (int i = 0; i < len; i++) g[i] = ((g[i] << 1) - (ll)inv_lim * a[i] % mod + mod) % mod;
	}
}

void main() {
	read(n), g[0] = 1;
	for (int i = 1, x; i < n; i++) read(x), g[i] = x ? mod - x : 0;
	polyInv(g, f);
	for (int i = 0; i < n; i++) print(f[i], " \n"[i == n - 1]);
}

} signed main() { return ringo::main(), 0; }

/*

F * G = F - 1
F = 1 / (1 - G)



*/