#include <bits/stdc++.h>
const int N = 510, M = 1000010;
int n, m, ans, vis[N];
char a[N][N];
std::vector<int> G[N];
template<int N, int M> struct Dinic {
	int tot, s, t, cur[N], hed[N], dep[N], to[M << 1], val[M << 1], nxt[M << 1];
	Dinic() { tot = 0, memset(hed, -1, sizeof(hed)); }
	inline void add(int u, int v, int w) {
		nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, hed[v] = tot++;
	}
	bool bfs() {
		static int u, l, r, q[N];
		memset(dep + 1, 0, t << 2), l = r = dep[s] = 1, q[1] = s;
		while (l <= r && (u = q[l++]))
			for (int i = hed[u]; ~i; i = nxt[i])
				if (val[i] && !dep[to[i]])
					dep[to[i]] = dep[u] + 1, q[++r] = to[i];
		return dep[t];
	}
	int dfs(int u, int d) {
		if (u == t) return d;
		int s = 0;
		for (int& i = cur[u]; ~i; i = nxt[i])
			if (val[i] && dep[to[i]] == dep[u] + 1)
				if (int e = dfs(to[i], std::min(d - s, val[i]))) {
					s += e, val[i] -= e, val[i ^ 1] += e;
					if (s == d) return s;
				}
		return s ? s : dep[s] = 0;
	}
	int dinic() {
		int r = 0;
		while (bfs()) memcpy(cur + 1, hed + 1, t << 2), r += dfs(s, 1e9);
		return r;
	}
};
Dinic<N, M> dinic;
struct atom {
	int id, ch[26];
	inline bool operator<(const atom& oth) const {
		for (int i = 0; i < 26; i++)
			if (ch[i] != oth.ch[i]) return ch[i] < oth.ch[i];
		return false;
	}
} b[N];
void dfs(int u, int c, std::vector<int>& s0, std::vector<int>& s1) {
	vis[u] = 1;
	(c ? s1 : s0).push_back(u);
	for (int v : G[u])
		if (!vis[v]) { dfs(v, c ^ 1, s0, s1); }
}
int main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	m = strlen(a[1] + 1);
	dinic.s = n + 1;
	dinic.t = n + 2;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			int cnt = 0;
			for (int k = 1; k <= m; k++) cnt += a[i][k] != a[j][k];
			if (cnt == 2) {
				G[i].push_back(j);
				G[j].push_back(i);
			}
		}
	for (int i = 1; i <= n; i++)
		if (!vis[i]) {
			std::vector<int> s0, s1;
			dfs(i, 0, s0, s1);
			for (int x : s0) dinic.add(dinic.s, x, 1);
			for (int y : s1) dinic.add(y, dinic.t, 1);
			for (int x : s0)
				for (int y : G[x]) dinic.add(x, y, 1);
		}
	printf("%d\n", n - dinic.dinic());
}