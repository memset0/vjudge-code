// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.12 11:23:40
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

const int N = 5e5 + 10;
int n, m, rt, top;
int val[N], fa[N], ch[N][2], stk[N], siz[N], son[N], fa_tree[N];
int tot = 2, hed[N], to[N << 1], nxt[N << 1];

struct matrix {
	int a[2][2];
	inline int& operator [] (int k) { return a[k][0]; }
} f[N], g[N];

inline matrix operator * (const matrix &a, const matrix &b) {
    return (matrix){{{
        std::max(a.a[0][0] + b.a[0][0], a.a[0][1] + b.a[1][0]),
        std::max(a.a[0][0] + b.a[0][1], a.a[0][1] + b.a[1][1])},{	
        std::max(a.a[1][0] + b.a[0][0], a.a[1][1] + b.a[1][0]),
        std::max(a.a[1][0] + b.a[0][1], a.a[1][1] + b.a[1][1])
    }}};
}

void dfs(int u) {
	siz[u] = 1;
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != fa_tree[u]) {
			fa_tree[v] = u, dfs(v), siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) son[u] = v;
		}
}

void dp(int u) {
	f[u][1] = g[u][1] = val[u];
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != fa_tree[u]) {
			dp(v);
			f[u][0] += std::max(f[v][0], f[v][1]), f[u][1] += f[v][0];
			if (v != son[u])
				g[u][0] += std::max(f[v][0], f[v][1]), g[u][1] += f[v][0];
		}
}

inline void maintain(int u) {
	f[u] = g[u];
	if (ch[u][0]) f[u] = f[ch[u][0]] * f[u];
	if (ch[u][1]) f[u] = f[u] * f[ch[u][1]];
}

int sbuild(int l, int r) {
	int sum = 0, now = 0;
	for (int i = l; i <= r; i++) sum += siz[stk[i]] - siz[son[stk[i]]];
	for (int i = l; i <= r; i++) {
		now += siz[stk[i]] - siz[son[stk[i]]];
		if ((now << 1) >= sum) {
			fa[ch[stk[i]][0] = sbuild(l, i - 1)] = stk[i];
			fa[ch[stk[i]][1] = sbuild(i + 1, r)] = stk[i];
			return maintain(stk[i]), stk[i];
		}
	}
	return 0;
}

int build(int x) {
	for (int u = x; u; u = son[u])
		for (int i = hed[u], v; v = to[i], i; i = nxt[i])
			if (v != fa_tree[u] && v != son[u])
				fa[build(v)] = x;
	top = 0; for (int u = x; u; u = son[u]) stk[++top] = u;
	return sbuild(1, top);
}

inline void modify(int k, int delta) {
	// std::cerr << "modify " << k << " " << delta << std::endl;
	for (int u = k; u; u = fa[u]) {
		if (ch[fa[u]][0] != u && ch[fa[u]][1] != u && fa[u]) {
			g[fa[u]][0] -= std::max(f[u][0], f[u][1]), g[fa[u]][1] -= f[u][0], g[fa[u]].a[0][1] = g[fa[u]].a[0][0];
			g[u][1] += u == k ? delta : 0, maintain(u);
			g[fa[u]][0] += std::max(f[u][0], f[u][1]), g[fa[u]][1] += f[u][0], g[fa[u]].a[0][1] = g[fa[u]].a[0][0];
		} else {
			g[u][1] += u == k ? delta : 0, maintain(u);
		}
	}
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(val[i]);
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
	}
	f[0].a[0][0] = f[0].a[1][1] = g[0].a[0][0] = g[0].a[1][1] = 1;	
	dfs(1), dp(1);
	for (int i = 1; i <= n; i++) g[i].a[0][1] = g[i].a[0][0], g[i].a[1][1] = -1e10;
	rt = build(1);
	for (int i = 1, k, w; i <= m; i++) {
		read(k), read(w), modify(k, w - val[k]), val[k] = w;
		print(std::max(f[rt][0], f[rt][1]), '\n');
		// for (int i = 1; i <= n; i++)
		// 	printf("%d %d %d %d | %d %d %d %d\n", f[i].a[0][0], f[i].a[0][1], f[i].a[1][0], f[i].a[1][1], g[i].a[0][0], g[i].a[0][1], g[i].a[1][0], g[i].a[1][1]);
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	return ringo::main(), 0;
}