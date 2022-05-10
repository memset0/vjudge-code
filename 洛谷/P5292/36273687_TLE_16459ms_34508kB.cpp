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
int n, m, p;
char s[N];
bool a[N], f[N][N];
std::vector <int> G[2][N];
std::queue <std::pair <int, int> > q;

void main() {
	read(n), read(m), read(p), scanf("%s", s + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = s[i] - '0';
		f[i][i] = 1, q.push(std::make_pair(i, i));
	}
	for (int i = 1, u, v; i <= m; i++) {
		read(u), read(v), G[a[v]][u].push_back(v), G[a[u]][v].push_back(u);
		if (a[u] == a[v]) {
			f[u][v] = 1, q.push(std::make_pair(u, v));
			f[v][u] = 1, q.push(std::make_pair(v, u));
		}
	}
	while (q.size()) {
		int u = q.front().first, v = q.front().second; q.pop();
		for (int k = 0; k < 2; k++)
			for (auto _u : G[k][u]) for (auto _v : G[k][v]) {
				if (!f[_u][_v]) { f[_u][_v] = 1, q.push(std::make_pair(_u, _v)); }
			}
	}
	for (int i = 1, u, v, ans; i <= p; i++) {
		read(u), read(v), ans = f[u][v];
		// if (!ans) printf(">> %d %d\n", u, v);
		puts(ans ? "YES" : "NO");
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}