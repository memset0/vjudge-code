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

char readc() {
	char c = getchar();
	while (c != '+' && c != '-' && c != '?') c = getchar();
	return c;
}

const int maxn = 100010;
int n, m, mn, mx, opt, pos, u, v, w, x, points, x1, x2;
int id[maxn], dep[maxn], f[maxn][20];
ll ans, g[maxn][20];
set < int > s;
set < int > ::iterator it;
int tot = 2, hed[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1];

void add_edge(int u, int v, int w) {
	nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
}

void dfs1(int u) {
	id[u] = ++pos;
	for (int i = hed[u]; i; i = nxt[i])
		if (!id[to[i]])
			dfs1(to[i]);
}

void dfs2(int u)  {
	for (int i = hed[u]; i; i = nxt[i])
		if (id[to[i]] != f[id[u]][0]) {
			f[id[to[i]]][0] = id[u];
			g[id[to[i]]][0] = val[i];
			dep[id[to[i]]] = dep[id[u]] + 1;
			dfs2(to[i]);
		}
}

int lca(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	for (int i = 19; i >= 0; i--)
		if (dep[f[v][i]] >= dep[u])
			v = f[v][i];
//	printf("%d %d\n", dep[u], dep[v]);
	if (u == v) return u;
	for (int i = 19; i >= 0; i--)
		if (f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}

ll dis(int u, int v) {
	int t = lca(u, v);
	ll ans = 0;
//	printf("dis(%d, %d) => %d, ", u, v, t);
	for (int i = 19; i >= 0; i--)
		if (dep[f[u][i]] > dep[t]) {
			ans += g[u][i];
			u = f[u][i];
		}
//	printf("%d, ", ans);
	if (u != t) ans += g[u][0];
//	printf("%d, ", ans);
	for (int i = 19; i >= 0; i--)
		if (dep[f[v][i]] > dep[t]) {
			ans += g[v][i];
			v = f[v][i];
		}
//	printf("[%d]", v);
//	printf("%d, ", ans);
	if (v != t) ans += g[v][0];
//	printf("%d\n", ans);
	return ans;
}

int main() {
//	freopen("data.txt", "r", stdin);
//	freopen("1.txt", "w", stdout);
//	freopen("stone.in", "r", stdin);
//	freopen("stone.out", "w", stdout);
	n = read();
	for (int i = 1; i < n; i++) {
		u = read(), v = read(), w = read();
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	dfs1(1);
	dep[1] = 1, dfs2(1);
//	print(id);
//	print(dep);
	for (int i = 1; i < 20; i++)
		for (int j = 1; j <= n; j++) {
			f[j][i] = f[f[j][i - 1]][i - 1];
			g[j][i] = g[f[j][i - 1]][i - 1] + g[j][i - 1];
		}
	m = read();
	for (int i = 1; i <= m; i++) {
		opt = readc();
		if (opt == '+') {
			x = id[read()];
			points++;
			if (points == 1) {
				mn = mx = x;
				ans = 0;
				s.insert(x);
			} else {
				if (x < mn) {
					ans -= dis(mn, mx);
					mn = x;
					ans += dis(mn, mx);
					x1 = *s.begin();
					ans += dis(x1, x);
				} else if (x > mx) {
					ans -= dis(mn, mx);
					mx = x;
					ans += dis(mn, mx);
					x2 = *--s.end();
					ans += dis(x, x2);
				} else {
					x1 = (*--s.lower_bound(x));
					x2 = (*s.upper_bound(x));
					ans -= dis(x1, x2);
					ans += dis(x1, x);
					ans += dis(x, x2);
				}
				s.insert(x);
			}
		} else if (opt == '-') {
			x = id[read()];
			points--;
			if (points == 0) {
				ans = 0;
				mn = mx = -1;
				s.erase(x);
			} else {
				if (x == mn) {
					ans -= dis(mn, mx);
					mn = *++s.begin();
					ans += dis(mn, mx);
					ans -= dis(x, mn);
				} else if (x == mx) {
					ans -= dis(mn, mx);
					mx = *----s.end();
					ans += dis(mn, mx);
					ans -= dis(mx, x);
				} else {
					x1 = (*--s.lower_bound(x));
					x2 = (*s.upper_bound(x));
					ans += dis(x1, x2);
					ans -= dis(x1, x);
					ans -= dis(x, x2);
				}
				s.erase(x);
			}
		} else {
			printf("%lld\n", ans >> 1);
		}
//		printf("%c >>> %d\n", opt, ans);
//		for (set < int > ::iterator it = s.begin(); it != s.end(); it++)
//			printf("%d ", *it);
//		puts("");
	}
	return 0;
}
