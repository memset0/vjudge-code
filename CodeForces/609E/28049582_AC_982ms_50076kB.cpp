// =================================
//   author: memset0
//   date: 2019.04.05 14:57:42
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
template <class T> inline void print(T x, char c) {
	print(x), putchar(c);
}

const int N = 4e5 + 10;
int n, m, fa[N];
ll base, ans[N];

namespace lct { 
	int max[N], val[N], rev[N], ch[N][2], fa[N];
	inline bool getSon(int u) { return ch[fa[u]][1] == u; }
	inline bool isRoot(int u) { return ch[fa[u]][0] != u && ch[fa[u]][1] != u; }
	inline void maintain(int u) { max[u] = std::max(val[u], std::max(max[ch[u][0]], max[ch[u][1]])); }
	inline void rotate(int x) {
		if (!x || !fa[x]) return;
		int f = fa[x], fs = getSon(x), ff = fa[f], ffs = getSon(f), y = ch[x][fs ^ 1];
		if (!isRoot(f)) ch[ff][ffs] = x; ch[x][fs ^ 1] = f, ch[f][fs] = y;
		fa[y] = f, fa[f] = x, fa[x] = ff, maintain(f), maintain(x);
	}
	void cleanUp(int x) {
		if (!isRoot(x)) cleanUp(fa[x]);
		if (rev[x]) rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1, std::swap(ch[x][0], ch[x][1]), rev[x] = 0;
	}
	void splay(int x) {
		cleanUp(x);
		for (int f = fa[x]; !isRoot(x); rotate(x), f = fa[x])
			if (!isRoot(f)) rotate(getSon(f) == getSon(x) ? f : x);
		maintain(x);	
	}
	inline void access(int x) {
		for (int y = 0; x; y = x, x = fa[x])
			splay(x), ch[x][1] = y, maintain(x);
	}
	inline void mroot(int x) { access(x), splay(x), rev[x] ^= 1; }
	inline void split(int x, int y) { mroot(x), access(y), splay(y); }
	inline void link(int x, int y) { mroot(x), fa[x] = y, maintain(y); }
	inline void cut(int x, int y) { split(x, y), fa[x] = ch[y][0] = 0, maintain(y); }
}

struct edge {
	int u, v, w, id;
	inline bool operator < (const edge &other) const {
		return w < other.w;
	}
} e[N];

int find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void main() {
	read(n), read(m);
	for (int i = 1, u, v, w; i <= m; i++) {
		read(u), read(v), read(w);
		e[i] = (edge){u, v, w, i};
	}
	std::sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1, u, v, w; i <= m; i++) {
		u = e[i].u, v = e[i].v, w = e[i].w;
		lct::max[n + i] = lct::val[n + i] = w;
		if (find(u) != find(v)) {
			fa[find(u)] = find(v);
			// printf("%d -> %d -> %d : %d\n", u, i, v, w);
			lct::link(u, n + i);
			lct::link(v, n + i);
			base += w;
		}
	}
	// printf(">> base = %lld\n", base);
	for (int i = 1, u, v, w; i <= m; i++) {
		u = e[i].u, v = e[i].v, w = e[i].w;
		lct::split(u, v);
		// printf("split %d %d => %d %d\n", u, v, lct::max[v], w);
		ans[e[i].id] = base - lct::max[v] + w;
	}
	for (int i = 1; i <= m; i++) print(ans[i], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}