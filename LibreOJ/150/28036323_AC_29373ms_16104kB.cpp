// =================================
//   author: memset0
//   date: 2019.06.25 15:26:16
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int (i) = (l), __lim = (r); (i) <= __lim; (i)++)
#define for_each(i, a) for (size_t i = 0, __lim = a.size(); i < __lim; ++i)
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

const int N = 1e5 + 10, M = N << 3, mod = 998244353;
int n, k, w[M], rev[M];

inline int opp(int x) { return x == 0 ? 0 : mod - x; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

namespace poly {
	struct poly : std::vector <int> {
		using std::vector <int> ::vector;
		void in() { for (int i = 0; i < size(); i++) read(at(i)); }
		void out() const { for (int i = 0; i < size(); i++) print(at(i), " \n"[i == size() - 1]); }
	} f, g;
	using ringo::inv;
	using ringo::fpow;
	inline poly resize(poly f, int n) { return f.resize(n), f; }
	inline poly operator + (poly f, int a) { f[0] = inc(f[0], a); return f; }
	inline poly operator + (int a, poly f) { f[0] = inc(a, f[0]); return f; }
	inline poly operator - (poly f, int a) { f[0] = dec(f[0], a); return f; }
	inline poly operator - (int a, poly f) { for_each(i, f) f[i] = dec(0, f[i]); f[0] = inc(a, f[0]); return f; }
	inline poly operator * (poly f, int a) { for_each(i, f) f[i] = (ll)f[i] * a % mod; return f; }
	inline poly operator * (int a, poly f) { for_each(i, f) f[i] = (ll)f[i] * a % mod; return f; }
	inline poly operator + (poly f, const poly &g) {
		f.resize(std::max(f.size(), g.size()));
		for_each(i, f) f[i] = inc(i < f.size() ? f[i] : 0, i < g.size() ? g[i] : 0);
		return f;
	}
	inline poly operator - (poly f, const poly &g) {
		f.resize(std::max(f.size(), g.size()));
		for_each(i, f) f[i] = dec(i < f.size() ? f[i] : 0, i < g.size() ? g[i] : 0);
		return f;
	}
	namespace cipolla_namespace {
		int t, sqr_w;
		typedef std::pair <int, int> pair;
		inline pair operator * (const pair &a, const pair &b) {
			return std::make_pair(((ll)a.first * b.first + (ll)a.second * b.second % mod * sqr_w) % mod,
				((ll)a.first * b.second + (ll)a.second * b.first) % mod);
		}
		int cipolla(int x) {
			do t = rand() % mod; while (fpow(sqr_w = dec((ll)t * t % mod, x), (mod - 1) >> 1) != mod - 1);
			pair s = std::make_pair(1, 0), a = std::make_pair(t, 1);
			for (int b = (mod + 1) >> 1; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
			return std::min(s.first, mod - s.first);
		}
	} using cipolla_namespace::cipolla;
	void ntt(int *a, int lim) {
		for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
		for (int len = 1; len < lim; len <<= 1)
			for (int i = 0; i < lim; i += (len << 1))
				for (int j = 0; j < len; j++) {
					int x = a[i + j], y = (ll)w[j + len] * a[i + j + len] % mod;
					a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
				}
	}
	int init(int len) {
		int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
		for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
		static int base_len = 1;
		for (int len = base_len, wn; (len << 1) < M; len <<= 1) {
			wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1, base_len = len;
			for (int i = 1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
		}
		return lim;
	}
	inline poly operator * (const poly &f, const poly &g) {
		static int a[M], b[M];
		int lim = init(f.size() + g.size() - 1), inv_lim = inv(lim); poly h;
		memset(&a[f.size()], 0, (lim - f.size()) << 2); for_each(i, f) a[i] = f[i];
		memset(&b[g.size()], 0, (lim - g.size()) << 2); for_each(i, g) b[i] = g[i];
		ntt(a, lim), ntt(b, lim);
		for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod;
		std::reverse(a + 1, a + lim), ntt(a, lim);
		for (int i = 0, l = f.size() + g.size() - 1; i < l; i++) h.push_back((ll)a[i] * inv_lim % mod);
		return h;
	}
	inline poly inv(const poly &f) {
		static int a[M], b[M];
		poly g(1, inv(f[0]));
		for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
			int lim = init(len << 1), inv_lim = inv(lim);
			memset(&a[len], 0, len << 2); for (int i = 0; i < len; i++) a[i] = i < f.size() ? f[i] : 0;
			memset(&b[len], 0, len << 2); for (int i = 0; i < len; i++) b[i] = i < g.size() ? g[i] : 0;
			ntt(a, lim), ntt(b, lim);
			for (int i = 0; i < lim; i++) a[i] = (ll)a[i] * b[i] % mod * b[i] % mod;
			std::reverse(a + 1, a + lim), ntt(a, lim), g.resize(len);
			for_each(i, g) g[i] = dec(inc(g[i], g[i]), (ll)a[i] * inv_lim % mod);
		} return g.resize(f.size()), g;
	}
	inline poly sqrt(const poly &f) {
		poly g(1, cipolla(f[0]));
		for (int len = 2; (len >> 1) < f.size(); len <<= 1)
			g = resize(resize(resize(g * g, len) + f, len) * inv(resize(2 * g, len)), len);
		return g.resize(f.size()), g;
	}
	inline poly deri(const poly &f) {
		poly g;
		for (int i = 0; i < f.size() - 1; i++) g.push_back((ll)(i + 1) * f[i + 1] % mod);
		return g.push_back(0), g;
	}
	inline poly inte(poly f) {
		poly g(1, 0);
		for (int i = 0; i < f.size() - 1; i++) g.push_back((ll)inv(i + 1) * f[i] % mod);
		return g;
	}
	inline poly ln(const poly &f) {
		return inte(resize(deri(f) * inv(f), f.size()));
	}
	inline poly exp(const poly &f) {
		poly g(1, 1);
		for (int len = 2; (len >> 1) < f.size(); len <<= 1)
			g = resize(g * (1 - ln(resize(g, len)) + resize(f, len)), len);
		return g.resize(f.size()), g;
	}
	inline poly simple_fpow(poly a, int b) {
		a = ln(a);
		for_each(i, a) a[i] = mul(a[i], b);
		a = exp(a);
		return a;
	}
	inline std::pair<int, bool> bordered_fpow(int x, int b) {
		std::pair<int, bool> s(1, false), a(x, false);
		for (; b; b >>= 1, a.second |= (ll)a.first * a.first >= mod, a.first = mul(a.first, a.first))
			if (b & 1) s.second |= a.second || (ll)a.first * s.first >= mod, s.first = mul(a.first, s.first);
		return s;
	}
	inline poly fpow(poly a, int b) {
		poly ans(a.size()); int cnt = 0;
		if (!b) { ans[0] = 1; return ans; }
		while (a[cnt] == 0 && cnt < a.size()) ++cnt;
		for (int i = 0; i + cnt < a.size(); i++) a[i] = a[i + cnt];
		a.resize(a.size() - cnt);
		int tim = a[0], inv_tim = inv(tim), pow_tim = fpow(tim, b);
		for_each(i, a) a[i] = mul(a[i], inv_tim);
		a = ln(a);
		for_each(i, a) a[i] = mul(a[i], b);
		a = exp(a);
		for_each(i, a) a[i] = mul(a[i], pow_tim);
		std::pair<int, bool> it = bordered_fpow(cnt, b);
		if (it.second || it.first >= ans.size()) return ans;
		for (int i = it.first; i < ans.size(); i++) ans[i] = a[i - it.first];
		return ans;
	}
} using namespace poly;

void main() {
    srand(20040725);
    read(n), read(k), f.resize(n + 1), f.in();
    g = deri(fpow(1 + ln(2 + f - f[0] - exp(inte(inv(sqrt(f))))), k));
    for (int i = 0; i < g.size() - 1; i++) print(g[i], " \n"[i == g.size() - 2]);
}

// void main() {
// 	read(n), read(k);
// 	poly f(n + 1);
// 	f[0] = 1, f[1] = mod - 2, f[2] = mod - 3;
// 	f = sqrt(f);
// 	for (int i = 0; i <= n; i++) f[i] = opp(f[i]);
// 	f[0] = inc(f[0], 1), f[1] = inc(f[1], 1);
// 	f.out();  
// 	f = ln(f);
// 	for (auto &x : f) x = mul(x, k - 1);
// 	f = exp(f);
// 	f.out();
// 	print(f[n], " \n"[i == n]);
// }

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	return ringo::main(), 0;
}
