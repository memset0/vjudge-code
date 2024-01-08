// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.10 17:34:23
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

const int N = 5e4 + 10, mod = 998244353;
int n, m, k, pos, ans[N];
std::vector<std::pair<int, int>> qry[N];
int tot = 2, hed[N], to[N << 1], nxt[N << 1];
int dep[N], fa[N], top[N], siz[N], son[N], id[N], wid[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

struct node {
	int l, r, mid;
	int mul, sum, tag;
} p[N << 2];

inline void pushup(int u, int w) {
	p[u].tag = inc(p[u].tag, w);
	p[u].sum = inc(p[u].sum, mul(w, p[u].mul));
}

inline void pushdown(int u) {
	if (p[u].tag) {
		pushup(u << 1, p[u].tag);
		pushup(u << 1 | 1, p[u].tag);
		p[u].tag = 0;
	}
}

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { p[u].mul = dec(fpow(dep[wid[l]], k), fpow(dep[fa[wid[l]]], k)); return; }
	build(u << 1, l, p[u].mid);
	build(u << 1 | 1, p[u].mid + 1, r);
	p[u].mul = inc(p[u << 1].mul, p[u << 1 | 1].mul);
}

void modify(int u, int l, int r) {
	pushdown(u);
	// if (u == 1) printf("modify %d %d\n", l, r);
	if (p[u].l == l && p[u].r == r) { pushup(u, 1); return; }
	if (r <= p[u].mid) modify(u << 1, l, r);
	else if (l > p[u].mid) modify(u << 1 | 1, l, r);
	else modify(u << 1, l, p[u].mid), modify(u << 1 | 1, p[u].mid + 1, r);
	p[u].sum = inc(p[u << 1].sum, p[u << 1 | 1].sum);
}

int query(int u, int l, int r) {
	pushdown(u);
	if (p[u].l == l && p[u].r == r) return p[u].sum;
	if (r <= p[u].mid) return query(u << 1, l, r);
	if (l > p[u].mid) return query(u << 1 | 1, l, r);
	return inc(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
}

void dfs1(int u) {
	siz[u] = 1;
	for (int i = hed[u], v; v = to[i], i; i = nxt[i]) {
		fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}

void dfs2(int u, int tpt) {
	id[u] = ++pos, wid[id[u]] = u, top[u] = tpt;
	if (siz[u] == 1) return;
	dfs2(son[u], tpt);
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != son[u]) dfs2(v, v);
}

void modify(int u) {
	while (top[u]) {
		modify(1, id[top[u]], id[u]);
		u = fa[top[u]];
	}
}

int query(int u) {
	int ans = 0;
	while (top[u]) {
		ans = inc(ans, query(1, id[top[u]], id[u]));
		u = fa[top[u]];
	}
	return ans;
}

void main() {
	read(n), read(m), read(k);
	for (int i = 2; i <= n; i++) {
		read(fa[i]);
		nxt[tot] = hed[fa[i]], to[tot] = i, hed[fa[i]] = tot++;
	}
	for (int i = 1, x, y; i <= m; i++) {
		read(x), read(y);
		qry[x].push_back(std::make_pair(y, i));
	}
	dep[1] = 1, dfs1(1), dfs2(1, 1), build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		// printf("===== %d =====\n", i);
		modify(i);
		// for (int i = 1; i <= n; i++) print(query(i), " \n"[i == n]);
		for (auto it : qry[i]) ans[it.second] = query(it.first);
	}
	for (int i = 1; i <= m; i++) print(ans[i], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}