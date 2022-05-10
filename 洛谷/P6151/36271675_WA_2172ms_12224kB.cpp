// =================================
//   author: memset0
//   date: 2019.03.17 13:14:36
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

const int N = 1e5 + 10, M = 2e5 + 10, mod = 998244353;
int n, m, ans, jiang;
int a[N], w[M << 1], rev[M << 1], fac[M << 1], ifac[M << 1];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int C(int n, int m) { return mul(fac[n], mul(ifac[m], ifac[n - m])); }
inline int inv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
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

inline std::vector <int> operator * (const std::vector <int> &f, const std::vector <int> &g) {
	static int a[N << 2], b[N << 2]; std::vector <int> h(f.size() + g.size() - 1);
	int lim = 1, k = 0, inv_lim; while (lim < h.size()) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int wn, len = 1; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
	}
	for (int i = 0; i < lim; i++) a[i] = i < f.size() ? f[i] : 0;
	for (int i = 0; i < lim; i++) b[i] = i < g.size() ? g[i] : 0;
	ntt(a, lim), ntt(b, lim), inv_lim = inv(lim);
	for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
	std::reverse(a + 1, a + lim), ntt(a, lim);
	for (int i = 0; i < h.size(); i++) h[i] = mul(a[i], inv_lim);
	return h;
}

inline std::vector <int> calc(int u) {
	int a = ringo::a[u];
	std::vector <int> ans(a + 1);
	if (u == jiang) {
		std::vector <int> f(a + 1), g(a + 1);
		for (int b = 1; b <= a; b++) f[b] = mul(fac[a + b - 1], mul(ifac[a - b], mul(ifac[2 * b - 1], mul(fac[b - 1], mul(b & 1 ? mod - 1 : 1, inv(b))))));
		for (int d = 0; d <= a; d++) g[d] = ifac[a - d];
		g = f * g;
		for (int c = 1; c <= a; c++) f[c] = mul(g[c + a], mul(ifac[c - 1], c & 1 ? mod - 1 : 1));
		for (int i = 0; i <= a - 1; i++) ans[i] = sub(ans[i], mul(f[i + 1], ifac[i]));
		for (int i = 0; i <= a - 2; i++) ans[i] = dec(ans[i], mul(f[i + 2], ifac[i]));
	} else {
		std::vector <int> f(a + 1), g(a + 1);
		for (int b = 1; b <= a; b++) f[b] = mul(fac[a + b - 1], mul(ifac[a - b], mul(ifac[2 * b - 1], mul(fac[b - 1], b & 1 ? mod - 1 : 1))));
		for (int d = 0; d <= a; d++) g[d] = ifac[a - d];
		f = f * g;
		for (int c = 1; c <= a; c++) ans[c] = mul(f[c + a], mul(ifac[c - 1], mul(ifac[c], c & 1 ? mod - 1 : 1)));
	}
	return ans;
}

std::vector <int> solve(int l, int r) {
	if (l == r) return calc(l);
	int mid = (l + r) >> 1;
	return solve(l, mid) * solve(mid + 1, r);
}

void main() {
	read(n);
	if (n == 1) { read(a[1]); print(a[1]); return; }
	for (int i = 1; i <= n; i++) read(a[i]), m += a[i];
	for (int i = 1; i <= n; i++) if (a[i] > 1 && (!jiang || a[i] < a[jiang])) jiang = i;
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= (m << 1); i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= (m << 1); i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= (m << 1); i++) ifac[i] = mul(ifac[i], ifac[i - 1]);
	auto f = solve(1, n);
	for (int i = 0; i < f.size(); i++) ans = sub(ans, mul(f[i], fac[i]));
	print(mul(ans, m), '\n');
}

} signed main() { return ringo::main(), 0; }