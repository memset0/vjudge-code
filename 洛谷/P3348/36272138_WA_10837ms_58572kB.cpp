// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.28 18:26:24
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

const int N = 4e5 + 10;
int n, m, cnt, lst, nod, ans[N], ql[N], qr[N], qid[N], qnd[N], qrt[N], rst[N], rnd[N], rtd[N];
std::vector <int> nodS[N], nodE[N], rotS[N], rotE[N];

struct query {
	int opt, l, r, x;
} q[N];
std::vector <query> qry[N];

inline void print(std::string name, std::vector <int> vet) {
	std::cout << name << " :";
	for (auto i : vet) std::cout << " " << i;
	std::cout << std::endl;
}

struct link_cut_tree {
	int sum[N], tag[N], ch[N][2], fa[N], rev[N];
	inline bool get_son(int x) { return ch[fa[x]][1] == x; }
	inline bool is_root(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
	inline void maintain(int x) {
		sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + tag[x];
	}
	inline void rotate(int x) {
		if (!x || !fa[x]) return;
		int f = fa[x], ff = fa[f], fs = get_son(x), ffs = get_son(f), y = ch[x][fs ^ 1];
		if (!is_root(f)) ch[ff][ffs] = x; ch[x][fs ^ 1] = f, ch[f][fs] = y;
		fa[y] = f, fa[f] = x, fa[x] = ff, maintain(f), maintain(x);
	}
	inline void pushup(int x) { rev[x] ^= 1, std::swap(ch[x][0], ch[x][1]); }
	inline void pushdown(int x) { if (rev[x]) pushup(ch[x][0]), pushup(ch[x][1]), rev[x] = 0; }
	inline void clean_up(int x) { if (!is_root(x)) clean_up(fa[x]); pushdown(x); }
	inline void splay(int x) {
	 	clean_up(x);
		for (int f = fa[x]; !is_root(x); rotate(x), f = fa[x])
			if (!is_root(f)) rotate(get_son(f) == get_son(x) ? f : x);
		maintain(x);
	}
	inline int access(int x) {
		int y = 0;
		while (x) {
			splay(x), ch[x][1] = y, maintain(x);
			y = x, x = fa[x];
		}
		return y;
	}
	inline void make_root(int x) { access(x), splay(x), pushup(x); }
	inline void split(int x, int y) { make_root(x), access(y), splay(y); }
	inline int get_root(int x) { access(x), splay(x); while (ch[x][0]) x = ch[x][0]; return x; }
	inline void link(int x, int y) {
		// printf("link %d %d\n", x, y);
		if (get_root(x) != get_root(y)) {
			make_root(x), fa[x] = y, maintain(y);
		}
	}
	inline void cut(int x, int y) {
		// printf("cut %d %d\n", x, y);
		if (get_root(x) == get_root(y)) {
			split(x, y);
			// printf(">>> %d %d %d\n", ch[x][1], fa[x], y, ch[y][0], x);
			if (!ch[x][1] && fa[x] == y && ch[y][0] == x)
				fa[x] = ch[y][0] = 0, maintain(y);
		}
	}
	void dfs(int u) {
		if (!u) return;
		dfs(ch[u][0]);
		printf("[%d] ", u, tag[u]);
		dfs(ch[u][1]);
	}
	inline int query(int u, int v) {
		// split(u, v);
		// return sum[v] - 1;
		int w, dis = 0;
		make_root(1), access(u), w = access(v);
		// printf(">> query %d %d %d\n", u, v, w);
		access(u), splay(u), dis += sum[u];
		// printf("u[%d] : %d %d : %d %d %d\n", u, sum[u], tag[u], fa[u], ch[u][0], ch[u][1]), dfs(u), puts("");
		access(v), splay(v), dis += sum[v];
		// printf("v[%d] : %d %d : %d %d %d\n", v, sum[v], tag[v], fa[v], ch[v][0], ch[v][1]), dfs(v), puts("");
		access(w), splay(w), dis -= (sum[w] << 1) + tag[w] - 1;
		// printf("w[%d] : %d %d : %d %d %d\n", w, sum[w], tag[w], fa[w], ch[w][0], ch[w][1]), dfs(w), puts("");
		return dis;
	}
} lct;

void main() {
	read(n), read(m);
	for (int i = 1, u, v, l, r, x, opt; i <= m; i++)
		switch (read(opt), opt) {
			case 0: read(l), read(r), q[i] = (query){opt, l, r, -1}, ++cnt; break;
			case 1: read(l), read(r), read(x), q[i] = (query){opt, l, r, x}; break;
			case 2: read(x), read(u), read(v), q[i] = (query){opt, u, v, x}; break;
		}
	for (int i = 1; i <= cnt + 1; i++) lct.tag[i] = lct.sum[i] = 1;
	nod = ++cnt, cnt = 1, lst = ++nod, lct.link(lst, 1);
	for (int i = 1; i <= m; i++)
		if (q[i].opt == 0) {
			++cnt, ql[cnt] = q[i].l, qr[cnt] = q[i].r, qid[cnt] = i, qnd[i] = cnt, qrt[i] = lst;
			nodS[q[i].l].push_back(i), nodE[q[i].r].push_back(i);
		} else if (q[i].opt == 1) {
			q[i].l = std::max(q[i].l, ql[q[i].x]), q[i].r = std::min(q[i].r, qr[q[i].x]);
			rst[i] = lst, rnd[i] = ++nod, rtd[i] = q[i].x, lct.link(nod, lst), lst = nod;
			rotS[q[i].l].push_back(i), rotE[q[i].r].push_back(i);
		} else {
			qry[q[i].x].push_back((query){3, q[i].l, q[i].r, i});
		}
	for (int u = 1; u <= n; u++) {
		// printf("=== %d ===\n", u);
		// print("nodS", nodS[u]);
		// print("rotS", rotS[u]);
		// print("nodE", nodE[u]);
		// print("rotE", rotE[u]);
		for (int i : nodS[u]) lct.link(qnd[i], qrt[i]);
		for (int i : rotS[u]) lct.cut(rnd[i], rst[i]), lct.link(rnd[i], rtd[i]);
		for (auto &it : qry[u]) ans[it.x] = lct.query(it.l, it.r);
		for (int i : rotE[u]) lct.cut(rnd[i], rtd[i]), lct.link(rnd[i], rst[i]);
		for (int i : nodE[u]) lct.cut(qnd[i], qrt[i]);
	}
	for (int i = 1; i <= m; i++) if (q[i].opt == 2) print(ans[i], '\n');
}

} signed main() { return ringo::main(), 0; }