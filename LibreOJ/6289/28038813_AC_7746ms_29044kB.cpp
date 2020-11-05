// =================================
//   author: memset0
//   date: 2019.03.02 22:27:23
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

const int N = 8e4 + 10, mod = 998244353;
int n, m, pos;
int b[N], w[N << 2], rev[N << 2], son[N], siz[N], fa[N], top[N];
int tot = 2, hed[N], nxt[N << 1], to[N << 1];
std::vector <int> link[N];

typedef std::vector <int> poly;
poly f[N], g[N], F[N], G[N];
inline void print(const poly &a) {
	for (size_t i = 0; i < a.size(); i++)
		print(a[i], ' ');
	putchar('\n');
}

struct matrix {
	poly _00, _01, _10, _11;
};

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

inline void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = mul(w[j + len], a[i + j + len]);
				a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
			}
}

inline poly operator + (const poly &a, const poly &b) {
	poly c(std::max(a.size(), b.size()));
	for (int i = 0; i < c.size(); i++) c[i] = sub(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
	return c;
}

inline poly operator * (const poly &a, const poly &b) {
	if (!a.size() || !b.size()) return poly();
	// if ((ll)a.size() * b.size() < 3000) {
	// 	poly c(std::min((size_t)(m + 1), a.size() + b.size() - 1));
	// 	for (int i = 0; i < a.size(); i++)
	// 		for (int j = 0; j < b.size(); j++)
	// 			if (i + j < m + 1)
	// 				c[i + j] = sub(c[i + j], mul(a[i], b[j]));
	// 	return c;
	// }
	static int f[N << 2], g[N << 2];
	int len = a.size() + b.size() - 1, lim = 1, k = 0;
	while (lim < len) lim <<= 1, ++k; int inv_lim = inv(lim);
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int i = 0; i < lim; i++) f[i] = i < a.size() ? a[i] : 0;
	for (int i = 0; i < lim; i++) g[i] = i < b.size() ? b[i] : 0;
	ntt(f, lim), ntt(g, lim);
	for (int i = 0; i < lim; i++) f[i] = mul(f[i], g[i]);
	std::reverse(f + 1, f + lim), ntt(f, lim);
	poly c(std::min((size_t)(m + 1), a.size() + b.size() - 1));
	for (int i = 0; i < c.size(); i++) c[i] = mul(f[i], inv_lim);
	return c;
}

void dfs1(int u) {
	siz[u] = 1;
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != fa[u]) {
			fa[v] = u, dfs1(v), siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) son[u] = v;
		}
}

void dfs2(int u, int tpt) {
	top[u] = tpt;
	if (siz[u] == 1) return;
	dfs2(son[u], tpt);
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != fa[u] && v != son[u])
			dfs2(v, v);
}

matrix solve_link(int l, int r, const std::vector <int> &link) {
	if (l == r) return (matrix){g[link[l]], poly(), poly(), f[link[l]]};
	int mid = (l + r) >> 1;
	matrix a = solve_link(l, mid, link), b = solve_link(mid + 1, r, link);
	return (matrix){
		a._00 * b._00 + a._01 * b._00 + a._00 * b._10, // 00
		a._00 * b._01 + a._00 * b._11 + a._01 * b._01, // 01
		a._10 * b._00 + a._10 * b._10 + a._11 * b._00, // 10
		a._10 * b._11 + a._11 * b._01 + a._10 * b._01  // 11
	};
}

std::pair <poly, poly> solve_sons(int l, int r, const std::vector <int> &sons) {
	if (l == r) return std::make_pair(G[sons[l]], F[sons[l]] + G[sons[l]]);
	int mid = (l + r) >> 1;
	std::pair <poly, poly> L = solve_sons(l, mid, sons), R = solve_sons(mid + 1, r, sons);
	return std::make_pair(L.first * R.first, L.second * R.second);
}

void solve(int u, int top) {
	link[top].push_back(u);
	if (siz[u] == 1) {
		f[u].push_back(0), f[u].push_back(b[u]), g[u].push_back(1);
		matrix ans = solve_link(0, link[top].size() - 1, link[top]);
		F[top] = ans._10 + ans._11, G[top] = ans._00 + ans._01;
		link[top].clear();
		return;
	}
	std::vector <int> sons;
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != fa[u] && v != son[u]) {
			solve(v, v);
			sons.push_back(v);
		}
	if (sons.size()) {
		std::pair <poly, poly> ret = solve_sons(0, sons.size() - 1, sons);
		f[u] = ret.first, g[u] = ret.second;
		f[u].insert(f[u].begin(), 0); if (f[u].size() > m + 1) f[u].resize(m + 1);
		for (int i = 0; i < f[u].size(); i++) f[u][i] = mul(f[u][i], b[u]);
	} else {
		f[u].push_back(0), f[u].push_back(b[u]), g[u].push_back(1);
	}
	solve(son[u], top);
}

void main() {
	read(n), read(m);
	for (int wn, len = 1; (len << 1) <= ((m + 1) << 2); len <<= 1) {
		wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
		for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn);
	}
	for (int i = 1; i <= n; i++) read(b[i]);
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
	}
	dfs1(1), dfs2(1, 1), solve(1, 1);
	poly ans = F[1] + G[1];
	// for (int i = 1; i <= n; i++) printf("F[%d] ", i), print(F[i]);
	// for (int i = 1; i <= n; i++) printf("G[%d] ", i), print(G[i]);
	// for (int i = 1; i <= n; i++) printf("f[%d] ", i), print(f[i]);
	// for (int i = 1; i <= n; i++) printf("g[%d] ", i), print(g[i]);
	print(m < ans.size() ? ans[m] : 0);
}

} signed main() { return ringo::main(), 0; }
