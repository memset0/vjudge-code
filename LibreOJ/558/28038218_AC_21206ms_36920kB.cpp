// =================================
//   author: memset0
//   date: 2019.03.28 10:21:36
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

const int N = 6e5 + 10;
int n, m, k, nod;

struct link_cut_tree {
	int fa[N], val[N], ch[N][2], siz[N], v_siz[N];
	bool rev[N], tag[N];
	ll sum[N], ansL[N], ansR[N], v_ans[N];
	inline void debug() {
		printf("[F A] "); for (int i = 1; i <= nod; i++) print(fa[i], " \n"[i == nod]);
		printf("[CH0] "); for (int i = 1; i <= nod; i++) print(ch[i][0], " \n"[i == nod]);
		printf("[CH1] "); for (int i = 1; i <= nod; i++) print(ch[i][1], " \n"[i == nod]);
		printf("[TAG] "); for (int i = 1; i <= nod; i++) print(tag[i], " \n"[i == nod]);
		printf("[REV] "); for (int i = 1; i <= nod; i++) print(rev[i], " \n"[i == nod]);
		printf("[ASL] "); for (int i = 1; i <= nod; i++) print(ansL[i], " \n"[i == nod]);
		printf("[ASR] "); for (int i = 1; i <= nod; i++) print(ansR[i], " \n"[i == nod]);
		printf("[ASV] "); for (int i = 1; i <= nod; i++) print(v_ans[i], " \n"[i == nod]);
		printf("[SIZ] "); for (int i = 1; i <= nod; i++) print(siz[i], " \n"[i == nod]);
		printf("[SZV] "); for (int i = 1; i <= nod; i++) print(v_siz[i], " \n"[i == nod]);
	}
	inline bool get_son(int x) { return ch[fa[x]][1] == x; }
	inline bool is_root(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
	inline void maintain(int x) {
		// if (is_root(x)) v_ans[fa[x]] -= ansL[x], v_siz[fa[x]] -= siz[x];
		sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
		siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + tag[x] + v_siz[x];
		ansL[x] = v_ans[x] + ansL[ch[x][0]] + ansL[ch[x][1]] + (siz[ch[x][1]] + v_siz[x] + tag[x]) * (val[x] + sum[ch[x][0]]);
		ansR[x] = v_ans[x] + ansR[ch[x][0]] + ansR[ch[x][1]] + (siz[ch[x][0]] + v_siz[x] + tag[x]) * (val[x] + sum[ch[x][1]]);
		// if (is_root(x)) v_ans[fa[x]] += ansL[x], v_siz[fa[x]] += siz[x], maintain(fa[x]);
	}
	inline void pushup(int x) {
		rev[x] ^= 1;
		// if (is_root(x)) v_ans[fa[x]] -= ansL[x];
		std::swap(ch[x][0], ch[x][1]), std::swap(ansL[x], ansR[x]);
		// if (is_root(x)) v_ans[fa[x]] += ansL[x];
	}
	inline void pushdown(int x) { if (rev[x]) pushup(ch[x][0]), pushup(ch[x][1]), rev[x] = 0; }
	inline void rotate(int x) {
		if (!x || !fa[x]) return;
		int f = fa[x], fs = get_son(x), ff = fa[f], ffs = get_son(f), y = ch[x][fs ^ 1];
		if (!is_root(f)) ch[ff][ffs] = x; ch[x][fs ^ 1] = f, ch[f][fs] = y;
		fa[y] = f, fa[f] = x, fa[x] = ff, maintain(f), maintain(x);
	}
	inline void clean(int x) { if (!is_root(x)) clean(fa[x]); pushdown(x); }
	inline void splay(int x) {
		clean(x);
		for (int f = fa[x]; !is_root(x); rotate(x), f = fa[x])
			if (!is_root(f)) rotate(get_son(x) == get_son(f) ? f : x);
		maintain(x);
	}
	inline void access(int x) {
		for (int y = 0; x; y = x, x = fa[x]) {
			splay(x);
			v_siz[x] += siz[ch[x][1]] - siz[y];
			v_ans[x] += ansL[ch[x][1]] - ansL[y];
			ch[x][1] = y, maintain(x);
		}
	}
	inline void make_root(int x) { access(x), splay(x), pushup(x); }
	inline void split(int x, int y) { make_root(x), access(y), splay(y); }
	inline int get_root(int x) { access(x), splay(x); while (ch[x][0]) x = ch[x][0]; return x; }
	inline void link(int x, int y) {
		if (get_root(x) != get_root(y)) {
			make_root(x), fa[x] = y;
			v_ans[y] += ansL[x], v_siz[y] += siz[x];
			maintain(y);
		}
	}
	inline void cut(int x, int y) {
		if (get_root(x) == get_root(y)) {
			split(x, y);
			if (!ch[x][1] && ch[y][0] == x && fa[x] == y)
				fa[x] = ch[y][0] = 0, maintain(y);
		}
	}
} lct;

std::map <int, int> map[N];
inline void add_edge(int u, int v, int w) {
	lct.val[++nod] = w, lct.maintain(nod);
	lct.link(u, nod), lct.link(nod, v);
	map[u][v] = map[v][u] = nod;
}
inline void del_edge(int u, int v) {
	int e = map[u][v];
	lct.cut(u, e), lct.cut(e, v);
}

void main() {
	read(n), read(m), read(k), nod = n;
	for (int i = 1, u, v, w; i <= m; i++) read(u), read(v), read(w), add_edge(u, v, w);
	for (int i = 1, u, v, w, opt; i <= k; i++) {
		while (opt = getchar(), !isupper(opt));
		switch (opt) {
			case 'L': read(u), read(v), read(w), add_edge(u, v, w); break;
			case 'C': read(u), read(v), del_edge(u, v); break;
			case 'F': read(u), lct.make_root(u), lct.tag[u] ^= 1, lct.maintain(u); break;
			case 'Q': read(u), lct.make_root(u), print(lct.ansL[u], '\n'); break;
		}
		// printf(">>> %c\n", opt), lct.debug();
	}
}

} signed main() { return ringo::main(), 0; }
