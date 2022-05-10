// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.18 11:23:52
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

const int N = 5e3 + 10, M = 1e5 + 10, inf = 1e9;
int n, m, s, e, cnt;
bool inq[N];
ll dis[N], cost, ans_cost;
int pre[N], flow, ans_flow;
int tot = 2, hed[N], to[M], val[M], cst[M], nxt[M];

bool spfa() {
	static int q[N];
	memset(pre, 0, (cnt + 1) << 2);
	memset(dis, 0x3f, (cnt + 1) << 3);
	int l = 0, r = 0, u; q[0] = s, dis[s] = 0;
	while (l <= r) {
		u = q[(l++) % cnt], inq[u] = 0;
		// printf("> %d\n", u);
		for (int i = hed[u], v; v = to[i], i; i = nxt[i])
			if (val[i] && dis[u] + cst[i] < dis[v]) {
				dis[v] = dis[u] + cst[i], pre[v] = i;
				if (!inq[v]) inq[q[(++r) % cnt] = v] = 1;
			}
	}
	return pre[e];
}

void main() {
	read(n), read(m), read(s), read(e), cnt = n;
	for (int i = 1, u, v, w, c; i <= m; i++) {
		read(u), read(v), read(w), read(c);
		nxt[tot] = hed[u], to[tot] = v, val[tot] = w, cst[tot] =  c, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, cst[tot] = -c, hed[v] = tot++;
	}
	while (spfa()) {
		flow = inf, cost = 0;
		for (int i = pre[e]; i; i = pre[to[i ^ 1]]) flow = std::min(flow, val[i]);
		for (int i = pre[e]; i; i = pre[to[i ^ 1]]) val[i] -= flow, val[i ^ 1] += flow, cost += flow * cst[i];
		// printf("flow %d : cost %d\n", flow, cost);
		ans_flow += flow, ans_cost += cost;
	}
	print(ans_flow, ' '), print(ans_cost, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("flow.in", "r", stdin);
	// freopen("mora1.in", "r", stdin);
	// freopen("mora1.out", "w", stdout);
#else
	freopen("mora.in", "r", stdin);
	freopen("mora.out", "w", stdout);	
#endif
	return ringo::main(), 0;
}