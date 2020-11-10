// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.28 17:19:06
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

const int N = 50, M = 110, P = 810, Nd = 80110, Ed = 2e7 + 10;
int n, m, s, e, cnt, ans, sum, cos;
int a[N], w[N][M], at[N], id[M][P], pre[Nd], dis[Nd], vis[Nd], lst[M], bln[Nd];
int tot = 2, hed[Nd], nxt[Ed], to[Ed], val[Ed], cst[Ed];

inline void add(int u, int v, int w, int c) {
	// printf("add edge %d %d %d %d\n", u, v, w, c);
	nxt[tot] = hed[u], to[tot] = v, val[tot] = w, cst[tot] =  c, hed[u] = tot++;
	nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, cst[tot] = -c, hed[v] = tot++;
}

bool spfa() {
	for (int i = 1; i <= cnt; i++) pre[i] = 0, dis[i] = 0x3f3f3f3f;
	static int q[Nd], l, r, u; vis[q[l = r = 1] = s] = 1, dis[s] = 0;
	while (l <= r) {
		vis[u = q[(l++) % Nd]] = 0;
		// for (int i = 1; i <= cnt; i++) print(dis[i], " \n"[i == cnt]);
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
			if (val[i] && dis[u] + cst[i] < dis[v]) {
				dis[v] = dis[u] + cst[i], pre[v] = i;
				// printf("%d -> %d : %d => %d\n", u, v, dis[u], dis[v]);
				if (!vis[v]) vis[q[(++r) % Nd] = v] = 1;
			}
	} return pre[e];
}

void main() {
	read(n), read(m), s = ++cnt, e = ++cnt;
	for (int i = 1; i <= n; i++) read(a[i]), at[i] = ++cnt, sum += a[i];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) read(w[i][j]);
	for (int i = 1; i <= n; i++) add(s, at[i], a[i], 0);
	for (int i = 1; i <= m; i++) for (int j = 1; j <= sum; j++) id[i][j] = ++cnt, bln[cnt] = i;
	for (int i = 1; i <= m; i++) {
		add(id[i][lst[i] = 1], e, 1, 0);
		for (int j = 1; j <= n; j++) add(at[j], id[i][1], 1, w[j][i]);
	}
	for (int t = 1; t <= sum; t++) {
		spfa();
		for (int i = pre[e]; i; i = pre[to[i ^ 1]])
			--val[i], ++val[i ^ 1], ans += cst[i];
		cos = bln[to[pre[e] ^ 1]];
		add(id[cos][++lst[cos]], e, 1, 0);
		for (int i = 1; i <= n; i++) add(at[i], id[cos][lst[cos]], 1, lst[cos] * w[i][cos]);
		// printf(">>> choose = %d answer = %d\n", cos, ans);
	} print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }
