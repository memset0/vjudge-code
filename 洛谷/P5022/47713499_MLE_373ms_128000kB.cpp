#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

void openFile() { freopen("travel.in", "r", stdin); freopen("travel.out", "w", stdout); }
void closeFile() { fclose(stdin); fclose(stdout); }

inline int read() {
	char c = getchar(); int n = 0;
	while (c < '0' || c > '9') { c = getchar(); }
	while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
	return n;
}

const int maxN = 5005;

int n, m, t, ban, num[maxN], dfn[maxN], low[maxN];
int k, res[maxN], ans[maxN];
bool flag = true, used[maxN];

struct Edge { int u, v; } edg[maxN];
struct Ed { int v, id; } e[maxN][maxN];
bool cmp(Ed x, Ed y) { return x.v < y.v; }

void dfs1(int u, int fa) {
	if (flag) { printf("%d", u); flag = false; } else { printf(" %d", u); }
	for (int i = 1; i <= num[u]; i++) {
		int v = e[u][i].v;
		if (v != fa) { dfs1(v, u); }
	}
}

void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++t;
	for (int i = 1; i <= num[u]; i++) {
		int v = e[u][i].v;
		if (v != fa) {
			if (!dfn[v]) {
				tarjan(v, u);
				if (low[u] > low[v]) { low[u] = low[v]; }
			} else {
				if (low[u] > dfn[v]) { low[u] = dfn[v]; }
			}
			if (low[v] <= dfn[u]) { used[e[u][i].id] = true; }
		}
	}
}

void dfs2(int u, int fa) {
	res[++k] = u;
	for (int i = 1; i <= num[u]; i++) {
		int v = e[u][i].v;
		if (v != fa && e[u][i].id != ban) { dfs2(v, u); }
	}
}

inline bool check() {
	for (int i = 1; i <= n; i++) {
		if (res[i] != ans[i]) { return res[i] < ans[i]; }
	}
	return false;
}

int main() {
	n = read(); m = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read(); edg[i].u = u, edg[i].v = v;
		e[u][++num[u]].v = v; e[v][++num[v]].v = u; e[u][num[u]].id = e[v][num[v]].id = i;
	}
	for (int i = 1; i <= n; i++) { std::sort(e[i] + 1, e[i] + num[i] + 1, cmp); }
	if (m == n - 1) { dfs1(1, 0); } else {
		for (int i = 1; i <= n; i++) {
			if (!dfn[i]) { tarjan(i, 0); }
		}
		ans[1] = n + 1;
		for (int i = 1; i <= m; i++) {
			if (used[i]) {
				ban = i; k = 0; dfs2(1, 0);
				if (check()) { memcpy(ans, res, sizeof(res)); }
			}
		}
		for (int i = 1; i <= n; i++) {
			if (i == 1) { printf("%d", ans[i]); } else { printf(" %d", ans[i]); }
		}
	}
	printf("\n");
	closeFile();
	return 0;
}
