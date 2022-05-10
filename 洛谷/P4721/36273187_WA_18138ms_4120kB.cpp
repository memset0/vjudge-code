// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.19 09:43:04
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
int n, m;
int f[N], g[N], a[N], b[N], c[N], w[N], rev[N];

int inv(int x) { return !x || x == 1 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % mod)
		if (b & 1) s = (ll)s * a % mod;
	return s;
}

void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = (ll)w[len + j] * a[i + j + len] % mod;
				a[i + j] = (x + y) % mod, a[i + j + len] = (x - y + mod) % mod;
			}
}

void mul(int *a, int *b, int *c, int n, int m) {
	int lim = 1, k = 0, inv_lim;
	while (lim <= (n + m)) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int i = n; i < lim; i++) a[i] = 0;
	for (int i = m; i < lim; i++) b[i] = 0;
	// for (int i = 0; i < n; i++) print(a[i], " \n"[i == n - 1]);
	// for (int i = 0; i < m; i++) print(b[i], " \n"[i == m - 1]);
	ntt(a, lim), ntt(b, lim);
	for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod;
	std::reverse(a + 1, a + lim), ntt(a, lim), inv_lim = inv(lim);
	for (int i = 0; i < n + m - 1; i++) c[i] = (ll)a[i] * inv_lim % mod;
	// for (int i = 0; i < n + m - 1; i++) print(c[i], " \n"[i == n + m - 2]);
}

void solve(int l, int r) {
	if (l == r) return (void)(f[l] += l == 0);
	int mid = (l + r) >> 1;
	solve(l, mid);
	// printf(">> [%d %d] => [%d %d]\n", l, mid, mid + 1, r);
	for (int i = 0; i <= mid - l; i++) a[i] = f[i + l];
	int delta = l - 1;
	for (int i = 0; i < n - delta; i++) b[i] = g[i + delta];
	mul(a, b, c, mid - l + 1, n - delta);
	// for (int i = 0; i < n; i++) print(f[i], " \n"[i == n - 1]);
	for (int i = mid + 1; i <= r; i++) (f[i] += c[i - l - delta]) %= mod;
	// for (int i = mid - l + 1; i <= r - l; i++) print(c[i], ' '); puts("");
	// for (int i = 0; i < n; i++) print(f[i], " \n"[i == n - 1]);
	solve(mid + 1, r);
}

void main() {
	read(n);
	for (int len = 1, wn; (len << 1) < N; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[len + i] = (ll)wn * w[len + i - 1] % mod;
	}
	for (int i = 1; i < n; i++) read(g[i]);
	solve(0, n - 1);
	for (int i = 0; i < n; i++) print(f[i], " \n"[i == n - 1]);
}

} signed main() { return ringo::main(), 0; }