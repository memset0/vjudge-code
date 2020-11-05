// =================================
//   author: memset0
//   date: 2019.03.21 08:21:30
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

const int N = 1e5 + 10;
typedef int arr[N];

int n, m, k, rt, ans, pos, tim, c_stk;
int f[N][20], g[N][20], h[N][20];
std::vector <int> vet, G[N], P[N];
arr a, fa, dep, siz, son, top, id, wid, tmp, cid, stk, in, out, max_dep, tag, dis;

namespace tools {

	void dfs1(int u) {
		siz[u] = 1, max_dep[u] = dep[u];
		for (auto v : G[u])
			if (v != fa[u]) {
				fa[v] = u, dep[v] = dep[u] + 1;
				dfs1(v);
				siz[u] += siz[v];
				max_dep[u] = std::max(max_dep[u], max_dep[v]);
				if (siz[v] > siz[son[u]]) son[u] = v;
			}
	}

	void dfs2(int u, int tpt) {
		top[u] = tpt, id[u] = ++pos, wid[id[u]] = u;
		if (siz[u] == 1) return;
		dfs2(son[u], tpt);
		for (auto v : G[u])
			if (v != fa[u] && v != son[u])
				dfs2(v, v);
	}

	inline int lca(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]])
				std::swap(u, v);
			v = fa[top[v]];
		}
		return dep[u] < dep[v] ? u : v;
	}

	inline int jump(int u, int k) {
		for (int i = 19; i >= 0; i--)
			if (k >= (1 << i))
				u = h[u][i], k -= 1 << i;
		return u;
	}
	
	inline int jumpF(int u, int k) {
		int ans = -1e9, dep = 0;
		for (int i = 19; i >= 0; i--)
			if (k >= (1 << i)) {
				ans = std::max(ans, f[u][i] + dep);
				u = h[u][i], k -= 1 << i, dep += 1 << i;
			}
		return ans;
	}
	
	inline int jumpG(int u, int k) {
		int ans = -1e9, dep = 0;
		for (int i = 19; i >= 0; i--)
			if (k >= (1 << i)) {
				ans = std::max(ans, g[u][i] - dep);
				u = h[u][i], k -= 1 << i, dep += 1 << i;
			}
		return ans;
	}

	inline int get_dis(int u, int v) {
		int ans = 0;
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]])
				std::swap(u, v);
			ans = dep[v] - dep[fa[top[v]]], v = fa[top[v]];
		}
		ans += dep[u] < dep[v] ? dep[v] - dep[u] : dep[u] - dep[v];
		return ans;
	}

	void preDis1(int u) {
		dis[u] = tag[u] ? 0 : 1e9;
		for (auto v : P[u]) {
			preDis1(v);
			dis[u] = std::min(dis[u], dis[v] + dep[v] - dep[u]);
		}
	}

	void preDis2(int u) {
		for (auto v : P[u]) {
			dis[v] = std::min(dis[v], dis[u] + dep[v] - dep[u]);
			preDis2(v);
		}
	}

}
using namespace tools;

namespace S {

	int cnt, rt[N];
	struct node {
		int l, r, mid, max, lc, rc;
	} p[N << 3];

	void build(int &u, int l, int r) {
		u = ++cnt, p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
		if (l == r) { p[u].max = tmp[l]; return; }
		build(p[u].lc, l, p[u].mid);
		build(p[u].rc, p[u].mid + 1, r);
		p[u].max = std::max(p[p[u].lc].max, p[p[u].rc].max);
	}

	void modify(int u, int k, int v) {
		if (p[u].l == p[u].r) { p[u].max = v; return; }
		if (k <= p[u].mid) modify(p[u].lc, k, v);
		else modify(p[u].rc, k, v);
		p[u].max = std::max(p[p[u].lc].max, p[p[u].rc].max);
	}

	int query(int u, int l, int r) {
		if (p[u].l == l && p[u].r == r) return p[u].max;
		if (r <= p[u].mid) return query(p[u].lc, l, r);
		if (l > p[u].mid) return query(p[u].rc, l, r);
		return std::max(query(p[u].lc, l, p[u].mid),
			query(p[u].rc, p[u].mid + 1, r));
	}

}

#define top c_stk

inline bool sort_by_dfn(int a, int b) {
	return in[a] < in[b];
}

inline void stk_push(int x) {
	if (x != stk[top]) {
		stk[++top] = x;
		vet.push_back(x);
	}
}

inline void stk_pop() {
	// printf("%d -> %d\n", stk[top - 1], stk[top]);
	P[stk[top - 1]].push_back(stk[top]);
	top--;
}

void buildTree() {
	vet.clear(), top = 0;
	// printf("buildTree => %d\n", rt);
	std::sort(a + 1, a + k + 1, sort_by_dfn);
	// for (int i = 1; i <= n; i++) print(a[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(in[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(out[i], " \n"[i == n]);
	for (int i = 1, u, t; u = a[i], i <= k; i++) {
		while (top > 1 && in[u] < in[stk[top - 1]] && out[stk[top - 1]] < out[u])
			stk_pop();
		if (in[u] < in[stk[top]] && out[stk[top]] < out[u])
			P[u].push_back(stk[top--]);
		t = lca(stk[top], u);
		// printf("u=[%d %d] t=[%d %d] top=[%d %d] top-1=[%d %d]\n", in[u], out[u], in[t], out[t], in[stk[top]], out[stk[top]], in[stk[top - 1]], out[stk[top - 1]]);
		while (top > 1 && in[t] < in[stk[top - 1]] && out[stk[top - 1]] < out[t])
			stk_pop();
		if (in[t] < in[stk[top]] && out[stk[top]] < out[t])
			P[t].push_back(stk[top--]);
		stk_push(t);
		stk_push(u);
		// printf(">> %d : ", i);
		// for (int i = 1; i <= top; i++) print(stk[i], ' ');
		// putchar('\n');
	}
	// for (int i = 1; i <= top; i++) print(stk[i], " \n"[i == top]);
	while (top > 1) stk_pop();
	// for (auto u : vet) {
	// 	printf("%d(%d) : ", u, P[u].size());
	// 	for (auto v : P[u]) print(v, ' ');
	// 	putchar('\n');
	// }
}
#undef top

void dfs3(int u) {
	in[u] = ++tim;
	int cnt = 0;
	for (auto v : G[u])
		if (v != fa[u]) {
			cid[v] = ++cnt;
			tmp[cnt] = max_dep[v];
		}
	if (cnt) S::build(S::rt[u], 1, cnt);
	for (auto v : G[u])
		if (v != fa[u])
			dfs3(v);
	out[u] = ++tim;
}

void solve(int u) {
	// printf("solve %d\n", u);
	ans = std::max(ans, dis[u]);
	if (P[u].size()) {
		int cnt = 0;
		for (auto v : P[u])
			tmp[++cnt] = jump(v, dep[v] - dep[u] - 1);
		// 子树无虚树节点
		for (int i = 1; i <= cnt; i++)
			S::modify(S::rt[u], cid[tmp[i]], -1);
		// printf("%d : 无虚树节点 => %d : %d %d %d\n", u, dis[u] + S::p[S::rt[u]].max - dep[u], dis[u], S::p[S::rt[u]].max, dep[u]);
		ans = std::max(ans, dis[u] + S::p[S::rt[u]].max - dep[u]);
		for (int i = 1; i <= cnt; i++)
			S::modify(S::rt[u], cid[tmp[i]], max_dep[tmp[i]]);
		// 子树有虚树节点
		for (auto v : P[u]) {
			int len = dep[v] - dep[u] - 1;
			int mid = ((dis[u] + dis[v] + len) >> 1) - dis[v];
			mid = std::max(0, std::min(len, mid));
			// printf("%d(%d) : 有虚树节点 => uDep=%d vDep=%d mid=%d len=%d\n", u, v, dep[u], dep[v], mid, len);
			// printf("                   => [%d %d] %d %d | [%d %d] %d %d\n", v, mid, dis[v], jumpF(v, mid),
			// 							jump(v, mid), len - mid, dis[u], jumpG(jump(v, mid), len - mid) + 1 + len - mid);
			ans = std::max(ans, dis[v] + jumpF(v, mid));
			ans = std::max(ans, dis[u] + jumpG(jump(v, mid), len - mid) + 1 + len - mid);
		}
		for (auto v : P[u])
			solve(v);
	} else {
		ans = std::max(ans, dis[u] + S::p[S::rt[u]].max - dep[u]);
	}
}

void main() {

	read(n), read(m);
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dep[1] = 1, dfs1(1), dfs2(1, 1), dfs3(1);
	for (int i = 1, val; i <= n; i++) {
		// printf("prepare %d\n", i);
		if (i == 1) val = -1e9;
		else {
			// printf(">> %d\n", S::p[S::rt[fa[i]]].max);
			S::modify(S::rt[fa[i]], cid[i], -1);
			// printf(">> %d %d\n", S::p[S::rt[fa[i]]].max, dep[fa[i]]);
			val = std::max(S::p[S::rt[fa[i]]].max - dep[fa[i]], 0);
			S::modify(S::rt[fa[i]], cid[i], max_dep[i]);
		}
		h[i][0] = fa[i];
		f[i][0] = val + 1;
		g[i][0] = val - 1;
	}
	// for (int i = 1; i <= n; i++) printf("[%d %d %d]%c", f[i][0], g[i][0], h[i][0], " \n"[i == n]);
	for (int i = 1; i < 20; i++)
		for (int j = 1; j <= n; j++) {
			h[j][i] = h[h[j][i - 1]][i - 1];
			f[j][i] = std::max(f[j][i - 1], f[h[j][i - 1]][i - 1] + (1 << (i - 1)));
			g[j][i] = std::max(g[j][i - 1], g[h[j][i - 1]][i - 1] - (1 << (i - 1)));
		}

	for (int i = 1; i <= m; i++) {
		read(k);
		for (int i = 1; i <= k; i++) read(a[i]), tag[a[i]] = 1;
		rt = a[1];
		for (int i = 2; i <= k; i++) rt = lca(rt, a[i]);
		buildTree(), preDis1(rt), preDis2(rt), solve(rt);
		if (rt != 1) ans = std::max(ans, dis[rt] + jumpF(rt, dep[rt] - 1));
		print(ans, '\n');
		for (auto u : vet) P[u].clear(), ans = 0;
		for (int i = 1; i <= k; i++) tag[a[i]] = 0;
	}
}

} signed main() { return ringo::main(), 0; }
