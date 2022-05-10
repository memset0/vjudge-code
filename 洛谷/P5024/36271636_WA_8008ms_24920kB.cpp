// =================================
//   author: memset0
//   date: 2019.04.13 18:02:46
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

const int N = 1e5 + 10;
int n, m, rt, top;
int a[N], fa[N], tfa[N], stk[N], son[N], siz[N], ch[N][2];
ll f[N][2], lf[N][2];
int tot = 2, hed[N], nxt[N << 1], to[N << 1];

struct matrix {
	ll a[2][2];
	inline void load(ll f0, ll f1, ll w, ll t = 0) { a[0][0] = 1e12, a[0][1] = f0 + t, a[1][0] = a[1][1] = f1 + w; }
	inline void dump(ll &f0, ll &f1) { f0 = std::min(a[0][1], a[0][0]), f1 = std::min(a[1][1], a[1][0]); }
} F[N], G[N];

inline matrix operator * (const matrix &a, const matrix &b) {
	return (matrix){{{
		std::min(a.a[0][0] + b.a[0][0], a.a[0][1] + b.a[1][0]),
		std::min(a.a[0][0] + b.a[0][1], a.a[0][1] + b.a[1][1])}, {
		std::min(a.a[1][0] + b.a[0][0], a.a[1][1] + b.a[1][0]),
		std::min(a.a[1][0] + b.a[0][1], a.a[1][1] + b.a[1][1])
	}}};
}

inline bool is_root(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
inline void maintain(int x) {
	F[x] = G[x];
	if (ch[x][0]) F[x] = F[ch[x][0]] * F[x];
	if (ch[x][1]) F[x] = F[x] * F[ch[x][1]];
}

void dfs(int u) {
	siz[u] = 1;
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != tfa[u]) {
			tfa[v] = u, dfs(v), siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) son[u] = v;
		}
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
			if (v != tfa[u] && v != son[u])
				fa[build(v)] = u;
	top = 0; for (int u = x; u; u = son[u]) stk[++top] = u;
	return sbuild(1, top);
}

void dp(int u) {
	f[u][1] = a[u];
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != tfa[u]) {
			dp(v);
			f[u][0] += f[v][1];
			f[u][1] += std::min(f[v][0], f[v][1]);
			if (v != son[u]) {
				lf[u][0] += f[v][1];
				lf[u][1] += std::min(f[v][0], f[v][1]);
			}
		}
}

void modify(int x, ll w, ll t) {
	// printf("modify %d %lld %lld\n", x, w, t);
	for (int u = x; u; u = fa[u]) {
		// printf("-> %d\n", u);
		if (is_root(u) && fa[u]) {
			F[u].dump(f[u][0], f[u][1]);
			lf[fa[u]][0] -= f[u][1];
			lf[fa[u]][1] -= std::min(f[u][0], f[u][1]);
		}
		if (u == x) G[u].load(lf[u][0], lf[u][1], w, t);
		else G[u].load(lf[u][0], lf[u][1], a[u]);
		maintain(u);
		if (is_root(u) && fa[u]) {
			F[u].dump(f[u][0], f[u][1]);
			lf[fa[u]][0] += f[u][1];
			lf[fa[u]][1] += std::min(f[u][0], f[u][1]);
		}
	}
}

void main() {
	read(n), read(m), getchar(), getchar();
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
	}
	dfs(1), dp(1);
	// for (int i = 1; i <= n; i++) print(f[i][0], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(f[i][1], " \n"[i == n]);
	for (int i = 1; i <= n; i++) G[i].load(lf[i][0], lf[i][1], a[i]);
	rt = build(1);
	// for (int i = 1; i <= n; i++) print(fa[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(siz[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(son[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++)
	// 	printf("F[%d] %lld %lld %lld %lld\n", i, F[i].a[0][0], F[i].a[0][1], F[i].a[1][0], F[i].a[1][1]);
	// for (int i = 1; i <= n; i++) if (ch[i][0])
	// 	printf("F[%d] - lc[%d] %lld %lld %lld %lld\n", i, ch[i][0], F[ch[i][0]].a[0][0], F[ch[i][0]].a[0][1], F[ch[i][0]].a[1][0], F[ch[i][0]].a[1][1]);
	// for (int i = 1; i <= n; i++) if (ch[i][1])
	// 	printf("F[%d] - rc[%d] %lld %lld %lld %lld\n", i, ch[i][1], F[ch[i][1]].a[0][0], F[ch[i][1]].a[0][1], F[ch[i][1]].a[1][0], F[ch[i][1]].a[1][1]);
	// for (int i = 1; i <= n; i++)
	// 	printf("G %lld %lld %lld %lld : %lld %lld\n", G[i].a[0][0], G[i].a[0][1], G[i].a[1][0], G[i].a[1][1], lf[i][0], lf[i][1]);
	ll ans, tmp1, tmp2, ans1, ans2;	
	for (int i = 1, u, x, v, y; i <= m; i++) {
		read(u), read(x), read(v), read(y);
		// printf(">> %d %d %d %d\n", u, x, v, y);
		modify(u, x ? 0 : 1e12, x ? 1e12 : 0);
		modify(v, y ? 0 : 1e12, y ? 1e12 : 0);
		F[rt].dump(ans1, ans2), ans = std::min(ans1, ans2);
		print(ans < 1e12 ? ans : -1, '\n');
		modify(u, a[u], 0), modify(v, a[v], 0);
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}