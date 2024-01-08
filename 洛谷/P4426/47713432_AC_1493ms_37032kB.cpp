// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.12 20:31:10
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

const int N = 2e5 + 10, mod = 998244353;
int n, m, sum;
int fa[N], vis[N], tag[N], siz[N], son[N], dep[N], top[N], faT[N];
int ans[N][2], mrk[N][2], preT[N][2];
std::vector <int> node, G[N], T[N];
std::vector <std::pair <int, int> > E, F, H[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }

struct status {
	int a, b, c;
	inline status operator + (const status &other) const {
		return (status){a + other.a, b + other.b, c + other.c};
	}
	inline status operator * (const status &other) const {
		if (!other.a && !other.b) return (status){mul(a, other.c), mul(b, other.c), mul(c, other.c)};
		if (!a && !b) return (status){mul(other.a, c), mul(other.b, c), mul(other.c, c)};
		puts("!");
	}
} dp[N][2], pre[N][2];

void dfs1(int u) {
	vis[u] = 1;
	for (auto it : H[u]) if (!vis[it.first])
		tag[it.second] = 1, dfs1(it.first);
}

void dfs2(int u) {
	siz[u] = 1;
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u, dep[v] = dep[u] + 1, dfs2(v), siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}

void dfs3(int u, int tpt) {
	top[u] = tpt; if (siz[u] == 1) return; dfs3(son[u], top[u]);
	for (auto v : G[u]) if (v != fa[u] && v != son[u]) dfs3(v, v);
}

inline int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) std::swap(u, v);
		v = fa[top[v]];
	} return dep[u] < dep[v] ? u : v;
}

void dfs4(int u) {
	// printf("dfs4 %d\n", u);
	if (tag[u]) return;
	vis[u] = 1, dp[u][1] = dp[u][0] = {0, 0, 1};
	for (auto v : G[u]) if (v != fa[u]) {
		dfs4(v);
		dp[u][1] = dp[u][1] * dp[v][0];
		dp[u][0] = dp[u][0] * (dp[v][0] + dp[v][1]);
	}
}

void dfs5(int u) {
	static int count = 0;
	// printf(">> dfs5 %d %d\n", u, ++count);
	vis[u] = tag[u];
	if (tag[u] && u != 1) {
		// printf(">>> search %d\n", u);
		int f = u; for (; !tag[fa[f]] && fa[f]; f = fa[f]);
		dp[u][0] = (status){1, 0, 0}, dp[u][1] = (status){0, 1, 0}, dfs4(f);
		T[fa[f]].push_back(u), T[u].push_back(fa[f]), faT[u] = fa[f], pre[u][0] = dp[f][0], pre[u][1] = dp[f][1];
	}
	for (auto v : G[u]) if (v != fa[u]) dfs5(v);
}

void dfs6(int u) {
	ans[u][0] = mrk[u][0] * preT[u][0], ans[u][1] = mrk[u][1] * preT[u][1];
	for (auto v : T[u]) if (v != faT[u]) {
		dfs6(v);
		int sol_0 = sub(pre[v][0].c, sub(mul(pre[v][0].a, ans[v][0]), mul(pre[v][0].b, ans[v][1])));
		int sol_1 = sub(pre[v][1].c, sub(mul(pre[v][1].a, ans[v][0]), mul(pre[v][1].b, ans[v][1])));
		if (mrk[u][0]) ans[u][0] = mul(ans[u][0], sub(sol_0, sol_1));
		if (mrk[u][1]) ans[u][1] = mul(ans[u][1], sol_0);
	}
	// printf("dfs6[%d] => %d %d\n", u, ans[u][0], ans[u][1]);
}

void dfs7(int u) {
	preT[u][0] = preT[u][1] = vis[u] = 1;
	for (auto v : G[u]) if (v != fa[u]) {
		dfs7(v);
		preT[u][0] = mul(preT[u][0], sub(preT[v][0], preT[v][1]));
		preT[u][1] = mul(preT[u][1], preT[v][0]);
	}
}

void dfs8(int u) {
	// printf(">> dfs8 %d\n", u);
	preT[u][0] = preT[u][1] = 1;
	for (auto v : G[u]) if (v != fa[u] && !vis[v]) {
		dfs7(v);
		// printf("%d -> %d\n", u, v);
		preT[u][0] = mul(preT[u][0], sub(preT[v][0], preT[v][1]));
		preT[u][1] = mul(preT[u][1], preT[v][0]);
	}
	for (auto v : G[u]) if (v != fa[u]) dfs8(v);
}

void dfs9(int u) {
	ans[u][0] = ans[u][1] = 1;
	for (auto v : G[u]) if (v != fa[u]) {
		dfs9(v);
		ans[u][0] = mul(ans[u][0], sub(ans[v][0], ans[v][1]));
		ans[u][1] = mul(ans[u][1], ans[v][0]);
	}
}

void main() {
	read(n), read(m);
	for (int i = 1, u, v; i <= m; i++) {
		read(u), read(v);
		E.push_back(std::make_pair(u, v));
		H[u].push_back(std::make_pair(v, i - 1));
		H[v].push_back(std::make_pair(u, i - 1));
	} dfs1(1);
	// for (auto it : E) printf("E : %d %d\n", it.first, it.second);
	for (int i = 0; i < m; i++) if (tag[i]) {
		G[E[i].first].push_back(E[i].second);
		G[E[i].second].push_back(E[i].first);
	} else F.push_back(E[i]);
	// for (auto it : F) printf("F : %d %d\n", it.first, it.second);
	memset(tag, 0, sizeof(tag)), dep[1] = 1, dfs2(1), dfs3(1, 1);
	for (auto pair : F) node.push_back(pair.first), node.push_back(pair.second);
	// for (int u : node) printf("node:1 %d\n", u);
	if (!node.size()) { dfs9(1), print(sub(ans[1][0], ans[1][1])); return; }
	tag[1] = 1;
	for (int u : node) for (auto v : node) tag[lca(u, v)] = 1;
	node.clear();
	for (int i = 1; i <= n; i++) if (tag[i]) node.push_back(i);
	// for (int u : node) printf("node:2 %d\n", u);
	dfs5(1);
	dfs8(1);
	// for (int u : node) printf("%d -> %d -> %d\n", u, G[u].size(), T[u].size());
	for (int x = 0, flag; x < (1 << F.size()); x++) {
		// printf(">>>> x=%d\n", x);
		// for (int i = 0; i < F.size(); i++) print((x >> i) & 1, " \n"[i == F.size() - 1]);
		for (int u : node) mrk[u][0] = mrk[u][1] = 1;
		for (int i = 0; i < F.size(); i++)
			if ((x >> i) & 1) mrk[F[i].first][1] = 0;
			else mrk[F[i].first][0] = mrk[F[i].second][1] = 0;
		// for (int u : node) printf("[%d %d]%c", mrk[u][0], mrk[u][1], ' '); puts("");
		flag = true;
		for (int u : node) flag &= mrk[u][0] || mrk[u][1];
		if (flag) dfs6(node[0]), sum = sub(sum, sub(ans[node[0]][0], ans[node[0]][1]));
	}
	// for (int i = 1; i <= n; i++) printf("dp [%d %d %d] [%d %d %d]\n", dp[i][0].a, dp[i][0].b, dp[i][0].c, dp[i][1].a, dp[i][1].b, dp[i][1].c);
	// for (int u : node) printf("pre [%d %d %d] [%d %d %d]\n", pre[u][0].a, pre[u][0].b, pre[u][0].c, pre[u][1].a, pre[u][1].b, pre[u][1].c);
	print(sum, '\n');
}

} signed main() { return ringo::main(), 0; }