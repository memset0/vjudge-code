// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.08 08:18:26
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

const int N = 5e3 + 10;
int n, m, q;
bool a[N];
char s[N], f[N][N];
std::vector <int> G[N];

int dfs(int u, int v) {
	// printf("dfs %d[%d] %d[%d]\n", u, a[u], v, a[v]);
	if (~f[u][v]) return f[u][v];
	f[u][v] = 0;
	for (auto _u : G[u])	
		for (auto _v : G[v]) {
			if (dfs(_u, _v))
				return f[u][v] = 1;
		}
	return 0;
}

void main() {
	memset(f, -1, sizeof(f));
	read(n), read(m), read(q), scanf("%s", s + 1);
	for (int i = 1; i <= n; i++) a[i] = s[i] - '0', f[i][i] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (a[i] != a[j]) f[i][j] = 0;
	for (int i = 1, u, v; i <= m; i++) 	{
		read(u), read(v), G[u].push_back(v), G[v].push_back(u);
		if (a[u] == a[v]) f[u][v] = f[v][u] = 1;
	}
	for (int i = 1, u, v; i <= q; i++) read(u), read(v), puts(dfs(u, v) ? "YES" : "NO");
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}	