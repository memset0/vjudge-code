// =================================
//   author: memset0
//   date: 2019.04.28 17:50:07
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

const int N = 1e5 + 10, S = 60, K = N / S + 10;
std::pair<int, int> t[N], p[N], q[N];
int tot = 2, hed[N], nxt[N << 1], to[N << 1];
int siz[N], son[N], top[N], fa[N], dfn[N], dep[N];
int n, m, len, pos, plen, qlen, ptop, qtop, encrypt, lastans;
int a[N], b[N], c[N], d[N], tag[N], pto[N], bln[N], fst[N], mov[N], prev[N], next[N], same[N];

void dfs1(int u) {
	siz[u] = 1;
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != fa[u]) {
			fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) son[u] = v;
		}
}

void dfs2(int u, int tpt) {
	// printf("dfs2 %d %d\n", u, tpt);
	top[u] = tpt, dfn[u] = ++pos;
	if (siz[u] == 1) return;
	dfs2(son[u], top[u]);
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != fa[u] && v != son[u])
			dfs2(v, v);
}

inline void do_move(int u, int w) {
	if (w == 1) {
		++mov[u];
		while (~prev[pto[u]] && prev[pto[u]] >= fst[u] && c[prev[pto[u]]] > -mov[u]) {
			// if (prev[pto[u]] == pto[u]) printf("P %d -> %d\n", pto[u], prev[pto[u]]);
			pto[u] = prev[pto[u]];
		}
	} else {
		--mov[u];
		while (~next[pto[u]] && pto[u] < fst[u + 1] && c[pto[u]] <= -mov[u]) {
			// if (next[pto[u]] == pto[u]) printf("N %d -> %d\n", pto[u], next[pto[u]]);
			pto[u] = next[pto[u]];
		}
	}
}

inline void init_movement(int u) {
	pto[u] = fst[u];
	while (pto[u] < fst[u + 1] && c[pto[u]] <= -mov[u])
		++pto[u];
	same[fst[u]] = fst[u];
	for (int i = fst[u] + 1; i < fst[u + 1]; i++)
		if (c[i] == c[i - 1]) same[i] = same[i - 1];
		else same[i] = i;
	prev[fst[u + 1]] = same[fst[u + 1] - 1];
	for (int i = fst[u]; i < fst[u + 1] - 1; i++)
		if (same[i] != same[i + 1])
			prev[same[i + 1]] = same[i];
	next[same[fst[u + 1] - 1]] = fst[u + 1];
	for (int i = fst[u]; i < fst[u + 1] - 1; i++)
		if (same[i] != same[i + 1])
			next[same[i]] = same[i + 1];
	for (int i = fst[u]; i < fst[u + 1]; i++)
		if (i != same[i]) {
			prev[i] = prev[same[i]];
			next[i] = next[same[i]];
		}
}

inline void build(int u) {
	len = fst[u + 1] - fst[u];
	for (int i = fst[u]; i < fst[u + 1]; i++)
		t[i - fst[u] + 1] = std::make_pair(a[i], i);
	std::sort(t + 1, t + len + 1);
	for (int i = fst[u]; i < fst[u + 1]; i++) {
		c[i] = t[i - fst[u] + 1].first;
		d[i] = t[i - fst[u] + 1].second;
		b[t[i - fst[u] + 1].second] = i;
	}
	init_movement(u);
}

inline void rebuild(int u, int l, int r) {
	for (int i = fst[u]; i < fst[u + 1]; i++)
		tag[b[i]] = l <= i && i <= r;
	len = plen = qlen = 0, ptop = qtop = 1;
	for (int i = fst[u]; i < fst[u + 1]; i++)
		(tag[i] ? p[++plen] : q[++qlen]) = std::make_pair(a[d[i]], d[i]);
	while (ptop <= plen && qtop <= qlen) 
		if (p[ptop].first < q[qtop].first)
			t[++len] = p[ptop++];
		else
			t[++len] = q[qtop++];
	while (ptop <= plen) t[++len] = p[ptop++];
	while (qtop <= qlen) t[++len] = q[qtop++];
	for (int i = fst[u]; i < fst[u + 1]; i++) {
		c[i] = t[i - fst[u] + 1].first;
		d[i] = t[i - fst[u] + 1].second;
		b[t[i - fst[u] + 1].second] = i;
	}
	init_movement(u);
}

inline void modify(int l, int r, int w) {
	if (bln[l] == bln[r]) {
		for (int i = l; i <= r; i++) a[i] += w;
		rebuild(bln[l], l, r);
	} else {
		for (int i = bln[l] + 1; i < bln[r]; i++) do_move(i, w);
		for (int i = l; i < fst[bln[l] + 1]; i++) a[i] += w;
		for (int i = fst[bln[r]]; i <= r; i++) a[i] += w;
		rebuild(bln[l], l, fst[bln[l] + 1] - 1);
		rebuild(bln[r], fst[bln[r]], r);
	}
}

inline int query(int l, int r) {
	int ans = 0, tmp;
	if (bln[l] == bln[r]) {
		tmp = mov[bln[l]];
		for (int i = l; i <= r; i++) ans += a[i] + tmp > 0;
	} else {
		for (int i = bln[l] + 1; i < bln[r]; i++) ans += fst[i + 1] - pto[i];
		tmp = mov[bln[l]];
		for (int i = l; i < fst[bln[l] + 1]; i++) ans += a[i] + tmp > 0;
		tmp = mov[bln[r]];
		for (int i = fst[bln[r]]; i <= r; i++) ans += a[i] + tmp > 0;
	}
	return ans;
}

inline void tree_modify(int u, int v, int w) {
	// printf("tree modify %d(dfn=%d top=%d) %d(dfn=%d top=%d) %d\n", u, dfn[u], top[u], v, dfn[v], top[v], w);
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) std::swap(u, v);
		modify(dfn[top[v]], dfn[v], w);
		v = fa[top[v]];
	}
	if (dfn[u] > dfn[v]) std::swap(u, v);
	modify(dfn[u], dfn[v], w);
}

inline int tree_query(int u, int v) {
	// printf("tree query %d(dfn=%d top=%d) %d(dfn=%d top=%d)\n", u, dfn[u], top[u], v, dfn[v], top[v]);
	int ans = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) std::swap(u, v);
		ans += query(dfn[top[v]], dfn[v]);
		v = fa[top[v]];
	}
	if (dfn[u] > dfn[v]) std::swap(u, v);
	return ans + query(dfn[u], dfn[v]);
}

void main() {
	memset(prev, -1, sizeof(prev));
	memset(next, -1, sizeof(next));
	read(n), read(m), read(encrypt);
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
	}
	dep[1] = 1, dfs1(1), dfs2(1, 1);
	for (int i = 1; i <= n; i++) {
		read(a[dfn[i]]);
		bln[i] = (i - 1) / S + 1;
	}
	fst[bln[n] + 1] = n + 1;
	for (int i = n; i >= 1; i--) fst[bln[i]] = i;
	for (int i = 1; i <= bln[n]; i++) build(i);
	for (int i = 1, x, y, z, opt; i <= m; i++) {
		read(opt);
		if (opt == 1) {
			read(x), read(y), read(z);
			if (encrypt) x ^= lastans, y ^= lastans;
			tree_modify(x, y, z);
		} else if (opt == 2) {
			read(x), read(y);
			if (encrypt) x ^= lastans, y ^= lastans;
			print(lastans = tree_query(x, y), '\n');
		} else {
			read(x); if (encrypt) x ^= lastans;
			print(lastans = query(dfn[x], dfn[x] + siz[x] - 1), '\n');
		}
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
	// freopen("comp/data.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	return ringo::main(), 0;
}//dfasdfadsfasf