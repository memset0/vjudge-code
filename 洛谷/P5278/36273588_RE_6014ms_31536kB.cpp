// luogu-judger-enable-o2
// =================================
//   author: memset0
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define gcd __gcd
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

const int N = 3e5 + 10;
int n, m, tn;
int a[N], b[N << 1], pre[N];
std::set <int> set[N];

struct node {
	int l, r, mid;
	int max, min, gcd, pre;
} p[N << 2];

struct query {
	int opt, x, y, z;
} q[N];

struct minimax {
	int min, max;
	inline minimax operator ^ (const minimax &other) const {
		return (minimax){std::min(min, other.min), std::max(max, other.max)};
	}
};

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { p[u].max = p[u].min = a[l], p[u].gcd = a[l] - a[l - 1], p[u].pre = pre[l]; return; }
	build(u << 1, l, p[u].mid), build(u << 1 | 1, p[u].mid + 1, r);
	p[u].max = std::max(p[u << 1].max, p[u << 	1 | 1].max), p[u].min = std::min(p[u << 1].min, p[u << 1 | 1].min);
	p[u].gcd = std::gcd(p[u << 1].gcd, p[u << 1 | 1].gcd), p[u].pre = std::max(p[u << 1].pre, p[u << 1 | 1].pre);
}

void modify_val(int u, int k, int v) {
	if (p[u].l == p[u].r) { p[u].min = p[u].max = v; return; }
	modify_val(k <= p[u].mid ? u << 1 : u << 1 | 1, k, v);
	p[u].max = std::max(p[u << 1].max, p[u << 1 | 1].max);
	p[u].min = std::min(p[u << 1].min, p[u << 1 | 1].min);
}

void modify_gcd(int u, int k, int v) {
	if (p[u].l == p[u].r) { p[u].gcd = v; return; }
	modify_gcd(k <= p[u].mid ? u << 1 : u << 1 | 1, k, v);
	p[u].gcd = std::gcd(p[u << 1].gcd, p[u << 1 | 1].gcd);
}

void modify_pre(int u, int k, int v) {
	if (p[u].l == p[u].r) { p[u].pre = v; return; }
	modify_pre(k <= p[u].mid ? u << 1 : u << 1 | 1, k, v);
	p[u].pre = std::max(p[u << 1].pre, p[u << 1 | 1].pre);
}

minimax query_val(int u, int l, int r) {
	if (p[u].l == l && p[u].r == r) return (minimax){p[u].min, p[u].max};
	if (r <= p[u].mid) return query_val(u << 1, l, p[u].mid);
	if (l > p[u].mid) return query_val(u << 1 | 1, p[u].mid + 1, r);
	return query_val(u << 1, l, p[u].mid) ^ query_val(u << 1 | 1, p[u].mid + 1, r);
}

int query_gcd(int u, int l, int r) {
	if (p[u].l == l && p[u].r == r) return p[u].gcd;
	if (r <= p[u].mid) return query_gcd(u << 1, l, r);
	if (l > p[u].mid) return query_gcd(u << 1 | 1, l, r);
	return std::gcd(query_gcd(u << 1, l, p[u].mid), query_gcd(u << 1 | 1, p[u].mid + 1, r));
}

int query_pre(int u, int l, int r) {
	if (p[u].l == l && p[u].r == r) return p[u].pre;
	if (r <= p[u].mid) return query_pre(u << 1, l, r);
	if (l > p[u].mid) return query_pre(u << 1 | 1, l, r);
	return std::max(query_pre(u << 1, l, p[u].mid), query_pre(u << 1 | 1, p[u].mid + 1, r));
}

inline void maintain(int x, int y) {
	std::set <int> ::iterator it = set[a[x]].find(x), tp;
	tp = it; int Pre = tp == set[a[x]].begin() ? -1 : *--tp;
	tp = it, tp = ++tp; int Nxt = tp == set[a[x]].end() ? -1 : *++tp;
	if (~Nxt) pre[Nxt] = Pre, modify_pre(1, Nxt, Pre);
	set[a[x]].erase(x), set[y].insert(x);
	tp = it, Pre = tp == set[y].begin() ? -1 : *--tp;
	tp = it, tp = ++tp, Nxt = tp == set[y].end() ? -1 : *++tp;
	if (~Nxt) pre[Nxt] = x, modify_pre(1, Nxt, x);
	pre[x] = Pre, modify_pre(1, x, Pre);
}

inline bool solve(int l, int r, int k) {
	minimax valQ = query_val(1, l, r);
	if (valQ.max - valQ.min != (ll)k * (r - l)) return false;
	if (l < r && query_gcd(1, l + 1, r) != k) return false;
	if (query_pre(1, l, r) >= l) return false;
	return true;
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(a[i]), b[++tn] = a[i];
	for (int i = 1, x, y, l, r, k, opt; i <= m; i++)
		if (read(opt), opt == 1) read(x), read(y), q[i] = (query){1, x, y, -1}, b[++tn] = y;
		else read(l), read(r), read(k), q[i] = (query){2, l, r, k};
	std::sort(b + 1, b + tn + 1), tn = std::unique(b + 1, b + tn + 1) - b - 1;
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + tn + 1, a[i]) - b - 1, set[a[i]].insert(i);
	for (int i = 1; i <= m; i++) if (q[i].opt == 1) q[i].y = std::lower_bound(b + 1, b + tn + 1, q[i].y) - b - 1;
	for (int i = 1; i <= n; i++) {
		std::set <int> ::iterator it = set[a[i]].find(i);
		pre[i] = it == set[a[i]].begin() ? -1 : *--it;
	} build(1, 1, n);
	for (int i = 1; i <= m; i++)
		if (q[i].opt == 1) maintain(q[i].x, q[i].y);
		else puts(solve(q[i].x, q[i].y, q[i].z) ? "YES" : "NO");
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}