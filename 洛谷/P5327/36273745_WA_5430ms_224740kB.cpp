// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.02 08:47:42
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

const int N = 1e5 + 10, M = N * 200;
ll ans;
int n, m, pos, nod;
std::vector<int> G[N];
std::vector<std::pair<int, int>> to_inc[N], to_dec[N];
int rt[N], fa[N], siz[N], dep[N], son[N], id[N], wid[N], top[N], dfn[N];

struct node {
	int lc, rc, sum, mrk;
} p[M];

inline void maintain(int u, int l, int r) {
	p[u].sum = p[u].mrk > 0 ? r - l + 1 : p[p[u].lc].sum + p[p[u].rc].sum;
}

void modify(int &u, int ql, int qr, int w, int l, int r) {
	if (!u) u = ++nod;
	if (ql == l && qr == r) {
		p[u].mrk += w;
	} else {
		int mid = (l + r) >> 1;
		if (qr <= mid) modify(p[u].lc, ql, qr, w, l, mid);
		else if (ql > mid) modify(p[u].rc, ql, qr, w, mid + 1, r);
		else modify(p[u].lc, ql, mid, w, l, mid), modify(p[u].rc, mid + 1, qr, w, mid + 1, r);
	}
	maintain(u, l, r);
	if (l == 1 && r == n) {
		// printf("    >> %d %d %d %d %d %d => %d\n", u, ql, qr, w, l, r, p[u].sum);
	}
}

void merge(int &u, int v, int l, int r) {
	if (!v) return;
	if (!u) { u = v; return; }
	if (l == r) {	
		p[u].mrk += p[v].mrk;
	} else {
		p[u].mrk += p[v].mrk;
		int mid = (l + r) >> 1;
		merge(p[u].lc, p[v].lc, l, mid);
		merge(p[u].rc, p[v].rc, mid + 1, r);
	}
	maintain(u, l, r);
}

void dfs1(int u) {
	siz[u] = 1;
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}

void dfs2(int u, int tpt) {
	top[u] = tpt, dfn[u] = ++pos, wid[dfn[u]] = u;
	if (siz[u] == 1) return;
	dfs2(son[u], tpt);
	for (auto v : G[u]) if (v != fa[u] && v != son[u])
		dfs2(v, v);
}

inline int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) std::swap(u, v);
		v = fa[top[v]];
	} return dep[u] < dep[v] ? u : v;
}

std::vector<std::pair<int, int>> split(int u, int v) {
	std::vector<std::pair<int, int>> res;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) std::swap(u, v);
		res.push_back(std::make_pair(dfn[top[v]], dfn[v]));
		v = fa[top[v]];
	}
	if (dep[u] > dep[v]) std::swap(u, v);
	res.push_back(std::make_pair(dfn[u], dfn[v]));
	return res;
}

void solve(int u) {
	for (auto v : G[u]) if (v != fa[u]) {
		solve(v);
		merge(rt[u], rt[v], 1, n);
	}
	for (auto it : to_inc[u])
		modify(rt[u], it.first, it.second, 1, 1, n);
	for (auto it : to_dec[u])
		modify(rt[u], it.first, it.second, -1, 1, n);
	// printf(">>> %d rt=%d sum=%d\n", u, rt[u], p[rt[u]].sum);
	ans += p[rt[u]].sum - 1;
}

void main() {
	read(n), read(m);
	for (int u, v, i = 1; i < n; i++) {
		read(u), read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dep[1] = 1, dfs1(1), dfs2(1, 1);
	// for (int i = 1; i <= n; i++) print(dfn[i], " \n"[i == n]);
	for (int u, v, t, i = 1; i <= m; i++) {
		read(u), read(v), t = lca(u, v);
		// printf(">> %d %d >> %d >> %d %d %d >> %d\n", u, v, t, dep[u], dep[v], dep[t], dep[u] + dep[v] - (dep[t] << 1) + 1);
		for (auto it : split(u, v)) {
			// printf("  >> %d %d\n", it.first, it.second);
			// modify(rt[u], it.first, it.second, 1, 1, n);
			// modify(rt[v], it.first, it.second, 1, 1, n);
			// modify(rt[t], it.first, it.second, -1, 1, n);
			// if (fa[t]) modify(rt[fa[t]], it.first, it.second, -1, 1, n);
			to_inc[u].push_back(it);
			to_inc[v].push_back(it);
			to_dec[t].push_back(it);
			if (fa[t]) to_dec[fa[t]].push_back(it);
		}
	}
	solve(1);
	// print(ans, '\n');
	print(ans >> 1, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}