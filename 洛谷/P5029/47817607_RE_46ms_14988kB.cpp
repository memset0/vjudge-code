// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.28 10:42:07
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

const int N = 1e5 + 10, M = 2e4 + 10, inf = 1e9, Nd = 3e5, Ed = 1e6;
int n, m, k, s, e, cnt;
int at[N], pre[Nd], cur[Nd], gap[Nd], dep[Nd];
int tot = 2, hed[Nd], nxt[Ed], val[Ed], to[Ed];

struct Node {
	int l, r, mid, id;
} p[N << 2];

inline void add(int u, int v, int w) {
	// printf("add %d %d %d\n", u, v, w);
	nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
	nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, hed[v] = tot++;
}

inline void add2(int u, int v, int w) {
	nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
	nxt[tot] = hed[v], to[tot] = u, val[tot] = w, hed[v] = tot++;
}

void build(int l, int r, int u) {
	for (int i = l; i <= r; i++) at[i] = ++cnt;
	// p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1, p[u].id = ++cnt;
	// if (l == r) { at[l] = p[u].id; return; }
	// build(l, p[u].mid, u << 1), build(p[u].mid + 1, r, u << 1 | 1);
	// add2(p[u].id, p[u << 1].id, inf), add2(p[u].id, p[u << 1 | 1].id, inf);
}

void link(int l, int r, int v, bool rev, int u = 1) {
	for (int i = l; i <= r; i++) rev ? add(v, at[i], inf) : add(at[i], v, inf);
	// if (p[u].l == l && p[u].r == r) { rev ? add(p[u].id, v, inf) : add(v, p[u].id, inf); return; }
	// if (r <= p[u].mid) link(l, p[u].mid, v, rev, u << 1);
	// else if (l > p[u].mid) link(p[u].mid + 1, r, v, rev, u << 1 | 1);
	// else link(l, p[u].mid, v, rev, u << 1), link(p[u].mid + 1, r, v, rev, u << 1 | 1);
}

int isap() {
	int ans = 0, flow, u = s, flag; gap[0] = cnt;
	while (dep[s] < cnt) {
		flag = 0;
		for (int &i = cur[u]; i; i = nxt[i]) if (val[i] && dep[u] == dep[to[i]] + 1)
			{ flag = 1, u = to[i]; pre[u] = i; break; }
		if (!flag) {
			if (!--gap[dep[u]]) break;
			dep[u] = cnt;
			for (int i = hed[u]; i; i = nxt[i]) if (val[i] && dep[u] > dep[to[i]] + 1)
				dep[u] = dep[to[i]] + 1, cur[u] = hed[u];
			++gap[dep[u]]; if (u != s) u = to[pre[u] ^ 1];
		} else if (u == e) {
			flow = inf;
			for (int i = pre[e]; i; i = pre[to[i ^ 1]]) flow = std::min(flow, val[i]);
			for (int i = pre[e]; i; i = pre[to[i ^ 1]]) val[i] -= flow, val[i ^ 1] += flow;
			ans += flow, u = s;
			// printf(">>> ans += %d\n", flow);
		}
		// printf(">> %d %d : %d \n", u, ans, flag);
	}
	return ans;
}

void main() {
	read(n), read(m), read(k);
	build(1, k, 1), add(s = ++cnt, at[1], n), add(at[k], e = ++cnt, n);
	for (int i = 1, a, b, a1, a2, b1, b2, op, lim; i <= m; i++) {
		read(op), read(lim);
		if (op == 1) read(a), read(b), add(at[a], at[b], lim);
		else if (op == 2) read(a1), read(a2), read(b), link(a1, a2, ++cnt, 0), add(cnt, at[b], lim);
		else if (op == 3) read(a), read(b1), read(b2), link(b1, b2, ++cnt, 1), add(at[a], cnt, lim);
		else read(a1), read(a2), read(b1), read(b2), link(a1, a2, ++cnt, 0), link(b1, b2, ++cnt, 1), add(cnt - 1, cnt, lim);
	} print(isap(), '\n');
}

} signed main() { return ringo::main(), 0; }