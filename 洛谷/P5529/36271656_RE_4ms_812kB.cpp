// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.20 16:42:07
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

const int N = 1e3 + 10;
int n, m, max, min, fa[N], val[N], dep[N];
std::vector<int> nod, son[N], G[N];

void dfs(int u, int fa = 0) {
	for (auto v : son[u]) {
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

void split(int u, int fa = 0) {
	nod.push_back(u);
	for (auto v : G[u])
		if (val[u] == val[v] && v != fa) {
			split(v, u);
		}
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) {
		read(fa[i]), son[fa[i]].push_back(i);
		G[i].push_back(fa[i]), G[fa[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) read(val[i]);
	dfs(1);
	read(m);
	for (int i = 1, x, y, opt; i <= m; i++) 
		switch (read(opt), opt) {
		case 1:
			read(x), read(y);
			// printf("[1] %d %d\n", x, y);
			val[x] = y;
			break;
		case 2:
			read(x), read(y);
			// printf("[2] %d %d\n", x, y);
			nod.clear(), split(x);
			for (auto u : nod) {
				val[u] = y;
			}
			break;
		case 3:
			read(x);
			// printf("[3] %d\n", x);
			nod.clear(), split(x);
			max = dep[x], min = dep[x];
			for (auto u : nod) {
				max = std::max(max, dep[u]);
				min = std::min(min, dep[u]);
			}
			print(val[x], ' ');
			print(nod.size(), ' ');
			print(max - min + 1, '\n');
			break;
		}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}