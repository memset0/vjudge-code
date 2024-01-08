// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.14 19:02:00
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define poly std::vector <int>
#define rep(i, l, r) for (register int i = (l), __lim = (r); i < __lim; ++i)
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
inline void read(poly &a, int n) { for (int i = 0, x; i < n; i++) read(x), a.push_back(x); }
inline void print(const poly &a) { for (int i = 0; i < a.size(); i++) print(a[i], " \n"[i == a.size() - 1]); }

const int N = 1e5 + 10, mod = 998244353;
int n, m, a[N], b[N], ans[N], w[N << 2], rev[N << 2];

inline int upd(ll a) { a %= mod; return a < 0 ? a + mod : a; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int upd(int a) { return a < 0 ? a + mod : a >= mod ? a - mod : a; }
inline int inv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

inline int init(int len) {
	int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
	rep(i, 0, lim) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int len = 1, wn; len < lim; len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		rep(i, 1, len) w[i + len] = (ll)w[i + len - 1] * wn % mod;
	} return lim;
}

inline void ntt(int *a, int lim) {
	rep(i, 0, lim) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = (ll)w[j + len] * a[i + j + len] % mod;
				a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
			}
}

inline poly operator + (const poly &f, const poly &g) {
	poly h(std::max(f.size(), g.size()));
	rep(i, 0, h.size()) h.push_back(sub(i < f.size() ? f[i] : 0, i < g.size() ? g[i] : 0));
	return h;
}

inline poly operator - (const poly &f, const poly &g) {
	poly h(std::max(f.size(), g.size()));
	rep(i, 0, h.size()) h.push_back(sub(i < f.size() ? f[i] : 0, i < g.size() ? g[i] : 0));
	return h;
}

inline poly operator * (const poly &f, const poly &g) {
	static int a[N << 2], b[N << 2]; poly h;
	int lim = init(f.size() + g.size() - 1), inv_lim = inv(lim);
	memset(a, 0, lim << 2), memset(b, 0, lim << 2);
	rep(i, 0, f.size()) a[i] = f[i]; rep(i, 0, g.size()) b[i] = g[i];
	ntt(a, lim), ntt(b, lim);
	rep(i, 0, lim) a[i] = (ll)a[i] * b[i] % mod;
	std::reverse(a + 1, a + lim), ntt(a, lim);
	rep(i, 0, f.size() + g.size() - 1) h.push_back((ll)a[i] * inv_lim % mod); return h;
}

inline poly resize(const poly &f, int n) {
	poly g = f; g.resize(n); return g;
}

inline poly inverse(const poly &f) {
	poly g; g.push_back(inv(f[0]));
	for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
		poly t;
		rep(i, 0, len) t.push_back(f[i]);
		t = g * t, t.resize(len);
		rep(i, 0, len) t[i] = dec(i ? 0 : 2, t[i]);
		g = g * t, g.resize(len);
		// printf(">>> [len = %d] ", len), print(g), print(t);
	} g.resize(f.size()); return g;
}

inline poly reverse(const poly &f) {
	poly g = f; std::reverse(g.begin(), g.end()); return g;
}

inline poly model(const poly &f, const poly &g) {
	int len = f.size() - g.size() + 1; 
	poly q = f * inverse(g); q.resize(len);
	poly r = f - q * g; return r;
}

inline std::pair <poly, poly> division(const poly &f, const poly &g) {
	// printf("division %d %d\n", f.size(), g.size());
	int len = f.size() - g.size() + 1;
	// print(f), print(g), print(reverse(f)), print(reverse(g));
	// print(inverse(reverse(f))), print(inverse(resize(reverse(f), len)));
	// print(reverse(f) * inverse(reverse(f))), print(reverse(f) * inverse(resize(reverse(f), len)));
	poly q = reverse(resize(resize(reverse(f), len) * inverse(resize(reverse(g), len)), len));
	poly r = f - q * g; r.resize(g.size() - 1);
	// print(q), print(r);
	return std::make_pair(q, r);
}

std::map <std::pair <int, int> , poly> map;

poly divide(int l, int r) {
	poly F;
	if (l == r) F.push_back(-b[l]), F.push_back(1);
	else {
		int mid = (l + r) >> 1;
		F = divide(l, mid) * divide(mid + 1, r);
	}
	map[std::make_pair(l, r)] = F;
	return F;
}

void solve(int l, int r, poly U) {
	if (l == r) { ans[l] = U[0]; return; }
	int mid = (l + r) >> 1;
	solve(l, mid, model(U, map[std::make_pair(l, mid)]));
	solve(mid + 1, r, model(U, map[std::make_pair(mid + 1, r)]));
}

// void main() {
// 	int _n, _m; poly a;
// 	read(_n), read(_m), ++_n;
// 	for (int i = 0, x; i < _n; i++) read(x), a.push_back(x);
// 	for (int i = 0, x; i < _m; i++) read(b[i]);
// 	n = std::max(_n + 1, _m);
// 	divide(0, n - 1), solve(0, n - 1, a);
// 	for (int i = 0; i < _m; i++) print(ans[i], " \n"[i == _m - 1]);
// }

void main() {
	int n, m, x; poly a, b;
	read(n), read(m);
	for (int i = 0; i <= n; i++) read(x), a.push_back(x);
	for (int i = 0; i <= m; i++) read(x), b.push_back(x);
	auto [q, r] = division(a, b);
	for (auto x : q) print(x, ' '); puts("");
	for (auto x : r) print(x, ' '); puts("");
}

} signed main() { return ringo::main(), 0; }