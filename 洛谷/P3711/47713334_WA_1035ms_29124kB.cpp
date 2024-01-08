// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.03 22:56:28
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

const int N = 250010, mod = 998244353;
int n, a[N], fac[N], ifac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

struct poly : std::vector <int> {
	using std::vector <int> ::vector;
	inline void in() { for (size_t i = 0; i < size(); i++) read(at(i)); }
	inline void out() const { for (size_t i = 0; i < size(); i++) print(at(i), " \n"[i == size() - 1]); }
} F, A, B;

int w[N << 2], rev[N << 2];
inline int init(int len) {
	int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int wn, len = 1; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
	} return lim;
}

void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
				a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
			}
}

inline poly operator * (const poly &f, const poly &g) {
	static int a[N << 2], b[N << 2];
	poly h(f.size() + g.size() - 1);
	int lim = init(h.size()), inv_lim = inv(lim);
	for (int i = 0; i < lim; i++) a[i] = i < f.size() ? f[i] : 0;
	for (int i = 0; i < lim; i++) b[i] = i < g.size() ? g[i] : 0;
	ntt(a, lim), ntt(b, lim);
	for (int i = 0; i < lim; i++) a[i] = mul(a[i], b[i]);
	std::reverse(a + 1, a + lim), ntt(a, lim);
	for (int i = 0; i < h.size(); i++) h[i] = mul(a[i], inv_lim);
	return h;
}

inline poly inv(const poly &f) {
	static int a[N << 2], b[N << 2];
	poly g(1, inv(f[0]));
	for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
		int lim = init(len << 1), inv_lim = inv(lim);
		for (int i = 0; i < lim; i++) a[i] = i < len && i < f.size() ? f[i] : 0;
		for (int i = 0; i < lim; i++) b[i] = i < len && i < g.size() ? g[i] : 0;
		ntt(a, lim), ntt(b, lim);
		for (int i = 0; i < lim; i++) a[i] = mul(a[i], mul(b[i], b[i]));
		std::reverse(a + 1, a + lim), ntt(a, lim);
		for (int i = (len >> 1); i < len; i++) g.push_back(dec(0, mul(a[i], inv_lim)));
	}
	g.resize(f.size());
	return g;
}

void math_init(int len) {
	fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
	for (int i = 2; i <= len; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= len; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= len; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
}

poly bernoulli(int len) {
	poly a(len);
	for (int i = 0; i < len; i++) a[i] = ifac[i + 1];
	a.push_back(len);
	a = inv(a), a[1] = dec(0, a[1]);
	return a;
}
	
void main() {
	read(n);
	for (int i = 0; i <= n; i++) read(a[i]);
	math_init(n + 3);
	A.resize(n + 3), B = bernoulli(n + 3);
	for (int i = 0; i < A.size(); i++) A[i] = mul(a[i], fac[i]);
	for (int i = 0; i < B.size(); i++) B[i] = mul(B[i], ifac[i]);
	std::reverse(A.begin(), A.end());
	F = A * B;
	// A.out(), B.out();
	F.out();
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}