// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 10010, maxm = 100010;

int n, m, l, r, u, v, top, ans, cnt, tim;
int w[maxn], q[maxn], a[maxn];
int ind[maxn], ins[maxn], stk[maxn], dfn[maxn], low[maxn], fa[maxn], dis[maxn];
int tot = 2, hed[maxn], nxt[maxm], to[maxm];

struct edge {
	int u, v;
	edge () {}
	edge (int a, int b) { u = a, v = b; }
} e[maxm];

void add_edge(int u, int v) {
	nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
}

void tarjan(int u) {
	dfn[u] = low[u] = ++tim;
	stk[++top] = u, ins[u] = 1;
	for (int i = hed[u]; i; i = nxt[u]) {
		int v = to[i];
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		while (top) {
			int v = stk[top--];
			fa[v] = u;
			ins[v] = 0;
			if (u == v) break;
		}
	}
}

int dp() {
	l = 1, r = 0;
	memset(dis, -1, sizeof(dis));
	for (int i = 1; i <= n; i++)
		if (!ind[fa[i]] && dis[fa[i]] == -1) {
			dis[fa[i]] = w[fa[i]];
			q[++r] = fa[i];
		}
	for (int i = 1; i <= n; i++)
		if (w[fa[i]] > ans)
			ans = w[fa[i]];
	while (l <= r) {
		u = q[l++];
//		cout << u << endl;
		for (int i = hed[u]; i; i = nxt[i]) {
			int v = to[i];
			ind[v]--;
			if (!ind[v]) q[++r] = v;
			if (dis[v] == -1 || dis[u] + w[v] < dis[v]) {
				dis[v] = dis[u] + w[v];
				if (dis[v] > ans) ans = dis[v];
			}
		}
	}
	return ans;
}

int main() {
	
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= m; i++) {
		u = read(), v = read();
		e[i] = edge(u, v);
		add_edge(u, v);
	}
	
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i);
		
	for (int i = 1; i <= n; i++)
		w[fa[i]] += a[i];
	
	tot = 2;
	memset(hed, 0, sizeof(hed));
	for (int i = 1; i <= m; i++) {
		u = fa[e[i].u], v = fa[e[i].v];
		if (u != v) {
			add_edge(u, v);
			ind[v] = u;
		}
	}
	
	printf("%d\n", dp());
	
	return 0;
}