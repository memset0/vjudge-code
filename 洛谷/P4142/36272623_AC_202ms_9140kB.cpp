// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.10 08:14:13
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

const int N = 55, Nd = 5010, Ed = 1000010;
int n, m, k, l, r, u, s, e, ts, nod, flow, cost;
int a[N][N], id[N][N], id2[N][N], pre[Nd], dis[Nd], q[Nd];
int tot = 2, hed[Nd], nxt[Ed], to[Ed], val[Ed], cst[Ed];
bool b[N][N], inq[Nd];
ll ans;

inline void add_edge(int u, int v, int w, int c) {
	// printf("add edge %d %d %d %d\n", u, v, w, c);
	nxt[tot] = hed[u], to[tot] = v, val[tot] = w, cst[tot] = c, hed[u] = tot++;
	nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, cst[tot] =-c, hed[v] = tot++;
}

bool spfa() {
	memset(pre, 0, sizeof(pre));
	memset(dis, -63, sizeof(dis));
	q[l = r = 0] = s, dis[s] = 0, inq[s] = 1;
	while (l <= r) {
		u = q[(l++) % Nd], inq[u] = 0;
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
			if (val[i] && dis[u] + cst[i] > dis[v]) {
				dis[v] = dis[u] + cst[i], pre[v] = i;
				if (!inq[v]) inq[q[(++r) % Nd] = v] = 1;
			}
	}
	// for (int i = 1; i <= nod; i++) print(dis[i], " \n"[i == nod]);
	return pre[e];
}

void main() {
	read(n), read(m), read(k);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) read(a[i][j]), ans += a[i][j];
	for (int i = 1, x, y; i <= k; i++) read(x), read(y), b[x][y] = 1;
	s = ++nod, e = ++nod, ts = ++nod;
	add_edge(s, ts, m, 0);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) id[i][j] = ++nod, id2[i][j] = ++nod;
	// puts("");
	// for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) print(id[i][j], " \n"[j == n]);
	// puts("");
	// for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) print(id2[i][j], " \n"[j == n]);
	// puts("");
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			static const int nxt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
			if (b[i][j]) continue;
			if ((i + j) & 1) {
				add_edge(id[i][j], id2[i][j], 1, a[i][j]);
				for (int t = 0, x, y; t < 4; t++) {
					x = i + nxt[t][0], y = j + nxt[t][1];
					if (b[x][y] || x < 1 || y < 1 || x > n || y > n) continue;
					if (x & 1) add_edge(id2[x][y], id[i][j], 1, 0);
					else add_edge(id2[i][j], id[x][y], 1, 0);
				}
			} else {
				add_edge(id[i][j], id2[i][j], 1, 0);
				if (i & 1) add_edge(ts, id[i][j], 1, 0);
				else add_edge(id2[i][j], e, 1, 0);
			}
		}
	while (spfa()) {
		flow = 1e9, cost = 0;
		for (int i = pre[e]; i; i = pre[to[i ^ 1]]) flow = std::min(flow, val[i]);
		for (int i = pre[e]; i; i = pre[to[i ^ 1]]) val[i] -= flow, val[i ^ 1] += flow;
		for (int i = pre[e]; i; i = pre[to[i ^ 1]]) cost += flow * cst[i];
		if (cost <= 0) break;
		ans -= cost;
		// std::cout << cost << std::endl;
	}
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }