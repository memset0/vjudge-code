// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.05 14:57:27
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

const int N = 110, M = 1010, mod = 31011;
int n, m, ans, fa[N], vis[N], map[N], A[N][N];
std::vector <int> G[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }

inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

struct edge {
	int u, v, w;
	inline bool operator < (const edge &other) const {
		return w < other.w;
	}
} e[M];

void dfs(int u, std::vector <int> &node) {
	vis[u] = 1, map[u] = node.size(), node.push_back(u);
	for (auto v : G[u]) if (!vis[v]) dfs(v, node);
}

int calc(int a[N][N], int n) {
	// printf("calc %d ans = %d a[1][1] = %d\n", n, ans, a[1][1]);
	if (n == 1) return a[1][1];
	static double tmp, f[N][N];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			f[i][j] = a[i][j];
	for (int i = 1, j; i <= n; i++) {
		for (j = i; j <= n; j++)
			if (fabs(f[j][i]) > 1e-7) break;
		if (j > n) return 0;
		if (i != j) std::swap(f[i], f[j]);
		for (int j = i + 1; j <= n; j++) {
			tmp = f[j][i] / f[i][i];
			for (int k = i; k <= n; k++) f[j][k] -= f[i][k] * tmp;
		}
		// for (int i = 1; i <= n; i++)
		// 	for (int j = 1; j <= n; j++)
		// 		printf("%.6lf%c", f[i][j], " \n"[j == n]);
		// puts("");
	}
	double ans = 1;
	for (int i = 1; i <= n; i++) ans = ans * f[i][i];
	// printf(">> %.6lf %d\n", ans, (int)(ans + .5));
	return (int)(ans + .5);
}

void solve(int u) {
	// printf(">> solve %d\n", u);
	std::vector <int> node; dfs(u, node);
	if (node.size() == 1) return;
	for (int i = 0; i < node.size(); i++)
		for (int j = 0; j < node.size(); j++)
			A[i][j] = 0;
	for (int i = 0; i < node.size(); i++) A[i][i] = G[node[i]].size();
	for (int i = 0; i < node.size(); i++)
		for (auto v : G[node[i]])
			A[i][map[v]]--;
	ans = (ll)ans * calc(A, node.size() - 1) % mod;
}

void main() {
	read(n), read(m);
	for (int i = 1, u, v, w; i <= m; i++) {
		read(u), read(v), read(w);
		e[i] = (edge){u, v, w};
	}
	for (int i = 1; i <= n; i++) fa[i] = i;
	std::sort(e + 1, e + m + 1);
	ans = 1;
	for (int L = 1, R = 0; L <= m; L = R + 1) {
		while (1) { ++R; if (e[R + 1].w != e[R].w) break; }
		// printf("[L = %d] [R = %d]\n", L, R);
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		for (int u, v, i = L; i <= R; i++) {
			u = find(e[i].u), v = find(e[i].v);
			if (u != v) G[u].push_back(v), G[v].push_back(u);
		}
		for (int i = 1; i <= n; i++) if (!vis[i]) solve(i);
		for (int i = L, u, v; i <= R; i++) {
			u = find(e[i].u), v = find(e[i].v);
			if (u != v) fa[u] = v;
		}
	}
	// printf(">>> ans = %d\n", ans);
	for (int i = 1; i <= n; i++) if (find(i) != find(1)) { ans = 0; break; }
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }