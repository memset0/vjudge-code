// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.08.02 00:45:24
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int i = (l), i##ed = (r); i <= i##ed; ++i)
#define for_each(i, a) for (size_t i = 0, i##ed = a.size(); i < i##ed; ++i)
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

const int N = 1e5 + 10, mod = 1004535809;
int n, k, flag;

inline void dec_up(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void inc_up(int &a, int b) { a += b; if (a >= mod) a -= mod; }
inline void mul_up(int &a, int b) { a = static_cast<ll>(a) * b % mod; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return static_cast<ll>(a) * b % mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, mul_up(a, a)) if (b & 1) mul_up(s, a); return s; }

struct poly : std::vector<int> {
	using std::vector<int>::vector;
	inline void in() { for (auto &x : *this) read(x); }
	inline void out() const { for (auto x : *this) print(x, ' '); putchar('\n'); }
} f;

int w[N << 2], rev[N << 2];
int init(int len) {
	int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	static int base_len = 1;
	for (int len = base_len, wn; len < lim; base_len = len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
	} return lim;
}

void dft(poly &a, int lim) {
	a.resize(lim);
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	if (lim > 1) {
		for (int i = 0; i < lim; i += 2) {
			int x = a[i], y = a[i + 1];
			a[i] = inc(x, y), a[i + 1] = dec(x, y);
		}
	}
	if (lim > 2) {
		for (int i = 0; i < lim; i += 4) {
			int x = a[i], y = mul(w[2], a[i + 2]);
			a[i] = inc(x, y), a[i + 2] = dec(x, y);
			x = a[i + 1], y = mul(w[3], a[i + 3]);
			a[i + 1] = inc(x, y), a[i + 3] = dec(x, y);
		}
	}
	for (int len = 4; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1)) {
			int t0, t1, t2, t3;
			int *f = &a[i], *g = &a[i + len], *p = &w[len], *end = &w[len << 1];
			while (p < end) {
				t0 = mul(*p, *g), *g = dec(*f, t0), inc_up(*f, t0);
				t1 = mul(*(p + 1), *(g + 1)), *(g + 1) = dec(*(f + 1), t1), inc_up(*(f + 1), t1);
				t2 = mul(*(p + 2), *(g + 2)), *(g + 2) = dec(*(f + 2), t2), inc_up(*(f + 2), t2);
				t3 = mul(*(p + 3), *(g + 3)), *(g + 3) = dec(*(f + 3), t3), inc_up(*(f + 3), t3);
				f += 4, g += 4, p += 4;
			}
		}
}

void idft(poly &a, int lim) {
	a.resize(lim), std::reverse(&a[1], &a[lim]);
	dft(a, lim); int inv_lim = inv(lim);
	for (int i = 0; i < lim; i++) mul_up(a[i], inv_lim);
}

poly mul(const poly &f, const poly &g, int len = -1) {
	static poly a, b; a = f, b = g;
	int lim = init(f.size() + g.size() - 1);
	dft(a, lim), dft(b, lim);
	for (int i = 0; i < lim; i++) mul_up(a[i], b[i]);
	idft(a, lim);
	return a.resize(~len ? len : f.size() + g.size() - 1), a;
}

poly inv(const poly &f, int len = -1) {
	if ((len = ~len ? len : f.size()) == 1) return poly{inv(f[0])};
	poly ans = inv(f, (len + 1) >> 1), tmp(&f[0], &f[len]);
	int lim = init((len << 1) - 1);
	dft(ans, lim), dft(tmp, lim);
	for (int i = 0; i < lim; i++) mul_up(ans[i], dec(2, mul(ans[i], tmp[i])));
	idft(ans, lim);
	return ans.resize(len), ans;
}

poly deri(poly f) {
	for (int i = 0; i < f.size() - 1; i++) f[i] = mul(f[i + 1], i + 1);
	return f[f.size() - 1] = 0, f;
}

poly inte(poly f) {
	for (int i = f.size() - 1; i; i--) f[i] = mul(f[i - 1], inv(i));
	return f[0] = 0, f;
}

poly ln(poly f, int len = -1) {
	if (~len) f.resize(len);
	return inte(mul(deri(f), inv(f), f.size()));
}

poly exp(poly f, int len = -1) {
	if ((len = ~len ? len : f.size()) == 1) return poly{1};
	poly ans = exp(f, (len + 1) >> 1), tmp(ln(ans, len));
	for (auto &it : tmp) if (it) it = mod - it; tmp[0] = inc(tmp[0], 1);
	for (int i = 0; i < tmp.size(); i++) tmp[i] = inc(tmp[i], f[i]);
	ans = mul(ans, tmp, len);
	return ans;
}

poly sqrt(poly f, int len = -1) {
	if ((len = ~len ? len : f.size()) == 1) return poly{1};
	poly ans = sqrt(f, (len + 1) >> 1), tmp(&f[0], &f[len]);
	ans.resize(len), tmp = mul(tmp, inv(ans), len);
	for (int i = 0; i < len; i++) inc_up(ans[i], tmp[i]);
	for (auto &it : ans) it = it & 1 ? (it + mod) >> 1 : it >> 1;
	return ans.resize(len), ans;
}

poly simple_fpow(poly f, int k) {
	f = ln(f);
	for (auto &it : f) mul_up(it, k);
	return exp(f);
}

void main() {
	read(n), read(k), read(flag);
	poly F(n), G(n);
	for (int i = 0; i < n; i++) read(F[i]);
	G[0] = 1, G[1] = mod - 1;
	G = simple_fpow(G, k);
	poly H = mul(F, flag ? G : inv(G));
	// F.out(), G.out(), H.out();
	for (int i = 0; i < n; i++) print(H[i], " \n"[i == n - 1]);
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}