// =================================
//   author: memset0
//   date: 2019.04.21 10:00:55
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

const int N = 1e5 + 10, mod = 998244353;
int n, a, b, ans;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

int w[N << 2], rev[N << 2];
struct poly : std::vector<int> {
	using std::vector<int>::vector;
	inline void in() { for (int i = 0; i < size(); i++) read(at(i)); }
	inline void out() const { for (int i = 0; i < size(); i++) print(at(i), " \n"[i == size() - 1]); }
};

inline int init(int len) {
	int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int wn, len = 1; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
	} return lim;
}

inline void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
				a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
			}
}

inline poly operator*(const poly &f, const poly &g) {
	static int a[N << 1], b[N << 1];
	static poly h; h.resize(f.size() + g.size() - 1);
	int lim = init(h.size()), inv_lim = inv(lim);
	for (int i = 0; i < lim; i++) a[i] = i < f.size() ? f[i] : 0;
	for (int i = 0; i < lim; i++) b[i] = i < g.size() ? g[i] : 0;
	ntt(a, lim), ntt(b, lim);
	for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
	std::reverse(a + 1, a + lim), ntt(a, lim);
	for (int i = 0; i < h.size(); i++) h[i] = mul(a[i], inv_lim);
	return h;
}

poly solve(int l, int r) {
	if (l == r) return poly{l, 1};
	int mid = (l + r) >> 1;
	return solve(l, mid) * solve(mid + 1, r);
}

void main() {
	read(n), read(a), read(b);
	if (a + b - 2 > n - 1 || a < 1 || b < 1) { puts("0"); return; }
	if (n == 1 && a == 1 && b == 1) { puts("1"); return; }
	ans = 1;
	for (int i = 1; i <= a + b - 2; i++) ans = mul(ans, i);
	for (int i = 1; i <= a - 1; i++) ans = mul(ans, inv(i));
	for (int i = 1; i <= b - 1; i++) ans = mul(ans, inv(i));
	poly it = solve(0, n - 2);
	// it.out();
	ans = mul(ans, it[a + b - 2]);
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
};