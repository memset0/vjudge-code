// =================================
//   author: memset0
//   date: 2019.03.20 16:10:00
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
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

const int N = 1e5 + 10;
int n, dep[N], dfn[N], f[N][20];
char s[N]; ll ans;

template <class T> inline T pre(T x) { return --x; }
template <class T> inline T aft(T x) { return ++x; }
struct dfn_order { inline bool operator () (int a, int b) { return dfn[a] < dfn[b]; } };
std::set <int, dfn_order> set;

namespace dict {
	int cnt = 1, lst = 1, fa[N], chr[N], ch[N][26];
	std::vector <int> vet;
}

namespace sam {
	const int M = N << 1;
	int lst = 1, nod = 1, tim, id[M], id2[M], len[M], fa[M], ch[M][26];
	std::vector <int> son[M];
	void append(int from, int now, int c) {
		int f = id[from], u = ++nod; id[now] = nod;
		// debug("append %d %d | %d %d | %d\n", from, now, f, u, c);
		len[u] = len[f] + 1;
		// printf(">>> %d\n", f);
		while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
		if (!f) { fa[u] = 1; return; }
		int s = ch[f][c];
		if (len[s] == len[f] + 1) { fa[u] = s; return; }
		int p = ++nod; id2[now] = nod;
		fa[p] = fa[s], fa[u] = fa[s] = p, len[p] = len[f] + 1;
		for (int i = 0; i < 26; i++) ch[p][i] = ch[s][i];
		while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
	}
	// void insert(int c) {
	// 	int f = lst, u = ++nod; len[lst = u] = ++cnt, siz[u] = 1;
	// 	while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
	// 	if (!f) return (void)(fa[u] = 1);
	// 	int s = ch[f][c];
	// 	if (len[s] == len[f] + 1) return (void)(fa[u] = s);
	// 	int p = ++nod; fa[p] = fa[s], len[p] = len[f] + 1, fa[s] = fa[u] = p;
	// 	for (register int i = 0; i < 26; i++) ch[p][i] = ch[s][i];
	// 	while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
	// }
	void dfs(int u, int depth = 1) {
		dfn[u] = ++tim, dep[u] = depth;
		for (auto v : son[u]) dfs(v, depth + 1);
	}
	void init() {
		id[1] = 1;
		for (int i = 2; i <= dict::cnt; i++) append(dict::fa[i], i, dict::chr[i] - 'a');
		for (int i = 2; i <= nod; i++) son[fa[i]].push_back(i), f[i][0] = fa[i];
		dfs(1);
		for (int i = 1; i < 20; i++)
			for (int j = 1; j <= nod; j++)
				f[j][i] = f[f[j][i - 1]][i - 1];
	}
}

namespace dict {
	void init() {
		for (int i = 1, c; c = s[i], i <= n; i++)
			if (c == '-') {
				lst = fa[lst], vet.push_back(lst);
			} else {
				if (ch[lst][c - 'a']) lst = ch[lst][c - 'a'];
				else fa[++cnt] = lst, chr[cnt] = c, ch[lst][c - 'a'] = cnt, lst = cnt;
				vet.push_back(lst);
			}
	}
}

inline int lca(int u, int v) {
	debug(">> lca %d %d", u, v);
	if (dep[u] > dep[v]) std::swap(u, v);
	// for (int i = 0; i < 20; i++) print(f[u][i], " \n"[i == 19]);
	// for (int i = 0; i < 20; i++) print(f[v][i], " \n"[i == 19]);
	for (int i = 19; i >= 0; i--)
		if (dep[f[v][i]] >= dep[u])
			v = f[v][i];
	if (u == v) debug(" => %d\n", u);
	if (u == v) return u;
	for (int i = 19; i >= 0; i--)
		if (f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	debug(" => %d\n", f[u][0]);
	return f[u][0];
}

struct info {
	int a, b, c, d, e, f;
	template <class T> inline info (const T &it) {
		a = c = d = e = f = 0, b = *it;
		if (it != set.begin()) a = *pre(it);
		if (aft(it) != set.end()) c = *aft(it);
		if (a && b) d = lca(a, b);
		if (b && c) e = lca(b, c);
		if (a && c) f = lca(a, c);
	}
};

inline void add(int x) {
	using sam::len;
	set.insert(x);
	info it(set.find(x));
	debug(">> add %d => %d %d %d %d %d %d | %d %d %d %d %d %d \n", x, it.a, it.b, it.c, it.d, it.e, it.f,
		len[it.a], len[it.b], len[it.c], len[it.d], len[it.e], len[it.f]);
	ans = (ans + len[it.b] + len[it.f] - len[it.d] - len[it.e]);
}

inline void del(int x) {
	using sam::len;
	info it(set.find(x));
	debug(">> del %d => %d %d %d %d %d %d | %d %d %d %d %d %d \n", x, it.a, it.b, it.c, it.d, it.e, it.f,
		len[it.a], len[it.b], len[it.c], len[it.d], len[it.e], len[it.f]);
	ans = (ans - len[it.b] - len[it.f] + len[it.d] + len[it.e]);
	set.erase(x);
}

void main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	dict::init(), sam::init();
	// for (int i = 1; i <= sam::nod; i++) print(sam::fa[i], " \n"[i == sam::nod]);
	// for (int i = 1; i <= sam::nod; i++) print(sam::len[i], " \n"[i == sam::nod]);
	// for (int i = 1; i <= sam::nod; i++) if (sam::son[i].size()) {
	// 	printf("%d : ", i);
	// 	for (auto u : sam::son[i]) print(u, ' ');
	// 	putchar('\n');
	// }
	for (int i = 1, c, u = 1; c = s[i], i <= n; i++) {
		if (c == '-') {
			del(sam::id[u]);// if (sam::id2[u]) del(sam::id2[u]);
			u = dict::fa[u];
		} else {
			u = dict::ch[u][c - 'a'];
			add(sam::id[u]);// if (sam::id2[u]) add(sam::id2[u]);
		}
		print(ans, '\n');
	}
}

} signed main() { return ringo::main(), 0; }