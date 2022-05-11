// =================================
//   author: memset0
//   date: 2019.04.21 20:47:16
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
int n, m, ans[N];
std::unordered_multiset<int> G[N];

struct edge {
	int u, v, w;
} e[N];

inline void add(int u, int v) {
	G[u].insert(v);
}

inline void del(int u, int v) {
	G[u].erase(G[u].find(v));
}

bool check(int s, int e) {
	static bool vis[N];
	static int l, r, u, q[N], dep[N];
	memset(vis, 0, n + 1);
	l = r = 0, q[0] = s, dep[s] = 0, vis[s] = 1;
	if (s == e) return true;
	while (l <= r) {
		u = q[l++]; 
		for (auto v : G[u])
			if (!vis[v]) {
				if (v == e) return true;
				q[++r] = v, vis[v] = 1;
			}
	}
	return false;
}

void main() {
	read(n), read(m);
	for (int i = 1, u, v, w; i <= m; i++) {
		read(u), read(v), read(w), e[i] = {u, v, w};
		if (w) add(u, v);
		else add(u, v), add(v, u);
	}
	for (int i = 1, u, v, w; i <= m; i++) {
		u = e[i].u, v = e[i].v, w = e[i].w;
		if (!w) {
			del(u, v), del(v, u);
			if (check(u, v)) ans[i] = 1, add(v, u);
			else add(u, v);
		}
	}
	for (int i = 1; i <= m; i++) print(ans[i], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}