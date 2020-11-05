// =================================
//   author: memset0
//   date: 2019.02.25 10:40:21
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

const int N = 2e5 + 10;
int n, m, ans, pos, lazy_tag;
int a[N], id[N], fa[N], dep[N], son[N], top[N], siz[N], dfn[N];
std::vector <int> G[N];

void dfs1(int u) {
	siz[u] = 1;
	for (auto v : G[u]) {
		fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}

void dfs2(int u, int tpt) {
	top[u] = tpt, dfn[u] = ++pos;
	if (siz[u] == 1) return; dfs2(son[u], top[u]);
	for (auto v : G[u]) if (v != son[u]) dfs2(v, v);
}

inline int lca(int u, int v) {
	// printf("lca %d %d \n", u, v);
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) std::swap(u, v);
		v = fa[top[v]];
	} return dep[u] < dep[v] ? u : v;
}

inline bool inside(int u, int v) {
	return dfn[v] <= dfn[u] && dfn[u] < dfn[v] + siz[v];
}

inline bool check_on(int x, int y, int u, int v) {
	return (inside(u, x) || inside(v, x)) && inside(x, y);
}

inline bool check(int a, int b, int u, int v) {
	int t = lca(u, v);
	if (!check_on(a, t, u, v)) return false;
	if (!check_on(b, t, u, v)) return false;
	// printf("=> [%d %d]\n", u, v);
	return true;
}

struct status {
	int u, v; bool live;
	inline status() {}
	inline status(int k) { u = v = k, live = 1; }
	inline status(int a, int b, int c = 1) { u = a, v = b, live = c; }
	friend inline status merge(const status &a, const status &b) {
		if (!a.live || !b.live) return status(-1, -1, 0);
		// printf("merge [%d %d %d] [%d %d %d]\n", a.u, a.v, a.live, b.u, b.v, b.live);
		if (check(b.u, b.v, a.u, a.v)) return a;
		if (check(a.u, a.v, b.u, b.v)) return b;
		if (check(a.u, b.v, b.u, a.v)) return status(b.u, a.v);
		if (check(b.u, a.v, a.u, b.v)) return status(a.u, b.v);
		if (check(a.v, b.v, a.u, b.u)) return status(a.u, b.u);
		if (check(a.u, b.u, a.v, b.v)) return status(a.v, b.v);
		return status(-1, -1, 0);
	}
};

struct node {
	int l, r, mid;
	status info;
} p[N << 2];

void build(int u, int l, int r) {
	// printf("build %d %d %d\n", u, l, r);
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { p[u].info = status(id[l]); return; }
	build(u << 1, l, p[u].mid), build(u << 1 | 1, p[u].mid + 1, r);
	p[u].info = merge(p[u << 1].info, p[u << 1 | 1].info);
}

void modify(int u, int k) {
	// printf("modify %d %d\n", u, k);
	if (p[u].l == p[u].r) { p[u].info = status(id[k]); return; }
	modify(k <= p[u].mid ? u << 1 : u << 1 | 1, k);
	p[u].info = merge(p[u << 1].info, p[u << 1 | 1].info);
}

status query(int u, int l, int r) {
	// printf("query %d %d %d\n", u, l, r);
	if (l == p[u].l && r == p[u].r) return p[u].info;
	if (r <= p[u].mid) return query(u << 1, l, r);
	if (l > p[u].mid) return query(u << 1 | 1, l, r);
	return merge(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
}

void dfs(int u) {
	// printf("%d [%d %d] => [%d %d %d]\n", u, p[u].l, p[u].r, p[u].info.u, p[u].info.v, p[u].info.live);
	if (p[u].l == p[u].r) return;
	dfs(u << 1), dfs(u << 1 | 1);
}

void solve() {
	ans = 0;
	// dfs(1);
	for (int l = 1, r = n, mid; mid = (l + r) >> 1, l <= r; ) {
		// printf("[[%d %d %d]] => %d\n", l, mid, r, query(1, 0, mid - 1).live);
		if (query(1, 0, mid - 1).live) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]), id[a[i]] = i;
	for (int i = 2; i <= n; i++) read(fa[i]), G[fa[i]].push_back(i);
	dep[1] = 1, dfs1(1), dfs2(1, 1), read(m), build(1, 0, n - 1);
	for (int i = 1, u, v, op; i <= m; i++)
		if (read(op), op == 1) {
			read(u), read(v), std::swap(a[u], a[v]);
			id[a[u]] = u, id[a[v]] = v, modify(1, a[u]), modify(1, a[v]), lazy_tag = false;
		} else {
			if (!lazy_tag) solve(), lazy_tag = true;
			print(ans, '\n');
		}
}

} signed main() { return ringo::main(), 0; }