// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.28 09:44:13
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

const int N = 3e5 + 10;
int n, m;

struct link_cut_tree {
	int val[N], sum[N], fa[N], ch[N][2]; bool rev[N];
	inline bool get_son(int x) { return ch[fa[x]][1] == x; }
	inline bool is_root(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
	inline void maintain(int x) { sum[x] = sum[ch[x][0]] ^ sum[ch[x][1]] ^ val[x]; }
	inline void pushdown(int x) {
		if (rev[x]) {
			rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1;
			std::swap(ch[x][0], ch[x][1]), rev[x] = 0;
		}
	}
	inline void rotate(int x) {
		if (!x || !fa[x]) return;
		int f = fa[x], ff = fa[f], fs = get_son(x), ffs = get_son(f), y = ch[x][fs ^ 1];
		if (!is_root(f)) ch[ff][ffs] = x; ch[x][fs ^ 1] = f, ch[f][fs] = y;
		fa[y] = f, fa[f] = x, fa[x] = ff, maintain(f), maintain(x);
	}
	void splay(int x) {
		clean(x);
		for (int f = fa[x]; !is_root(x); rotate(x), f = fa[x])
			if (!is_root(f)) rotate(get_son(f) == get_son(x) ? f : x);
	}
	void access(int x) {
		for (int y = 0; x; y = x, x = fa[x])
			splay(x), ch[x][1] = y, maintain(x);
	}
	void clean(int x) { if (!is_root(x)) clean(fa[x]); pushdown(x); }
	void make_root(int x) { access(x), splay(x), rev[x] ^= 1; }
	void split(int x, int y) { make_root(x), access(y), splay(y); }
	int get_root(int x) { access(x), splay(x); while (ch[x][0]) x = ch[x][0]; return x; }
	void link(int x, int y) { if (get_root(x) != get_root(y)) make_root(x), fa[x] = y, maintain(y); }
	void cut(int x, int y) { if (get_root(x) == get_root(y)) { split(x, y); if (!ch[x][1]) fa[x] = ch[y][0] = 0, maintain(y); }}
} lct;

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(lct.val[i]), lct.maintain(i);
	for (int i = 1, x, y, opt; i <= m; i++) {
		read(opt), read(x), read(y);
		switch (opt) {
			case 0: lct.split(x, y), print(lct.sum[y], '\n'); break;
			case 1: lct.link(x, y); break;
			case 2: lct.cut(x, y); break;
			case 3: lct.val[x] = y; lct.maintain(x); break;
		}
	}
}

} signed main() { return ringo::main(), 0; }