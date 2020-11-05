      // =================================
//   author: memset0
//   date: 2019.05.19 18:03:40
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

const int N = 1e5 + 10, M = 205, mod = 1e9 + 7;
int n, m, ans, fa[N], siz[N], f[N][M], res[M], tmp[M], fac[M], ifac[M], s[M][M];
std::vector<int> G[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void dfs(int u) {
	siz[u] = f[u][0] = 1;
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u, dfs(v), siz[u] += siz[v];
		memset(tmp, 0, (m + 1) << 2);
		for (int i = 0; i <= m; i++) {
			tmp[i] = inc(tmp[i], inc(f[v][i], f[u][i]));
			if (i + 1 <= m) tmp[i + 1] = inc(tmp[i + 1], f[v][i]);
		}
		// printf("%d => %d : ", u, v), print(tmp, 0, m);
		for (int i = 0; i < siz[u] - siz[v] && i <= m; i++)
			for (int j = 0; j < siz[v] && i + j <= m; j++) {
				int now = mul(f[u][i], f[v][j]);
				if (i + j <= m) {
					tmp[i + j] = inc(tmp[i + j], now);
					res[i + j] = inc(res[i + j], now);
				}
				if (i + j + 1 <= m) {
					tmp[i + j + 1] = inc(tmp[i + j + 1], now);
					res[i + j + 1] = inc(res[i + j + 1], now);
				}
			}
		for (int i = 0; i < siz[u] && i <= m; i++) f[u][i] = tmp[i];
	}
}

void main() {
	read(n), read(m);
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= m; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= m; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= m; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	for (int i = 0; i <= m; i++) {
		s[i][i] = 1;
		for (int j = 1; j < i; j++) s[i][j] = inc(s[i - 1][j - 1], mul(j, s[i - 1][j]));
	}
	for (int u, v, i = 1; i < n; i++) {
		read(u), read(v);
		G[u].push_back(v), G[v].push_back(u);
	}
	dfs(1);
	for (int i = 1; i <= m; i++) ans = inc(ans, mul(mul(fac[i], s[m][i]), res[i]));
	// for (int i = 1; i <= n; i++)
	// 	for (int j = 0; j <= m; j++)
	// 		print(f[i][j], " \n"[j == m]);
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}