// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.06.26 13:23:03
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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

const int N = 20;
std::vector<int> G[N], E[N];
int n, m, cnt, sum, ans, dp[N][N], vis[N];

void dfs(int u, int father = 0) {
	for (int i = 1; i <= n; i++)
		if (vis[i]) dp[u][i] = 1;
	for (auto v : G[u]) if (v != father) {
		dfs(v, u);
		for (int x = 1; x <= n; x++) if (vis[x]) {
			int sum = 0;
			for (auto y : E[x]) if (vis[y]) {
				// (u, x) -> (v, y)
				sum += dp[v][y];
			}
			dp[u][x] *= sum;
		}
	}
}

void main() {
	read(n), read(m);
	for (int i = 1, u, v; i <= m; i++) {
		read(u), read(v);
		E[u].push_back(v), E[v].push_back(u);
	}
	for (int i = 1, u, v; i <= n - 1; i++) {
		read(u), read(v);
		G[u].push_back(v), G[v].push_back(u);
	}
	for (int S = 0; S < (1 << n); S++, sum = 0) {
		for (int i = 1; i <= n; i++) vis[i] = (S >> (i - 1)) & 1;
		dfs(1);
		for (int i = 1; i <= n; i++) if (vis[i]) sum += dp[1][i];
		// for (int i = 1; i <= n; i++) print(dp[1][i], " \n"[i == n]);
		ans += n + __builtin_popcount(S) & 1 ? -sum : sum;
		// printf("[%d] >> %d %d %d >> ", S, sum, n + __builtin_popcount(S) & 1, ans);
		// for (int i = 1; i <= n; i++) print(vis[i], " \n"[i == n]);
	}
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}
