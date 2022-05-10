// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.28 19:15:09
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)

namespace ringo {
typedef long long ll;
typedef unsigned long long ull;
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
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 3e5 + 10, P = 998244353;
int n, tn, cnt, inv_10000;
int rt[N], fa[N], val[N], son[N][2], siz[N], b[N];

int fpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % P)
		if (b & 1) s = (ll)s * a % P;
	return s;
}

struct node {
	int lc, rc, sum, lazy;
} p[N * 30];
int new_node() { int u = ++cnt; p[u].lazy = 1; return u; }

inline void pushup(int u, int x) {
	if (!u) return;
	p[u].lazy = (ll)p[u].lazy * x % P;
	p[u].sum = (ll)p[u].sum * x % P;
}

inline void pushdown(int u) {
	if (!u || p[u].lazy == 1) return;
	pushup(p[u].lc, p[u].lazy);
	pushup(p[u].rc, p[u].lazy);
	p[u].lazy = 1;
}

inline void maintain(int u) {
	p[u].sum = (p[p[u].lc].sum + p[p[u].rc].sum) % P;
}

void build(int &u, int k, int l = 1, int r = tn) {
	// printf("build %d %d %d %d\n", u, k, l, r);
	u = new_node();
	if (l == r) { p[u].sum = 1; return; }
	int mid = (l + r) >> 1;
	k <= mid ? build(p[u].lc, k, l, mid) : build(p[u].rc, k, mid + 1, r);
	maintain(u);
}

int merge(int x, int y, int pL, int pR, int sumXL = 0, int sumXR = 0, int sumYL = 0, int sumYR = 0, int l = 1, int r = tn) {
	// printf("merge %d %d %d %d %d %d %d %d %d %d\n", x, y, pL, pR, sumXL, sumXR, sumYL, sumYR, l, r);
	if (!x && !y) return 0;
	int u = new_node(), mid = (l + r) >> 1;
	if (!x) { p[u] = p[y], pushup(u, ((ll)pL * sumXL + (ll)pR * sumXR) % P); return u; }
	if (!y) { p[u] = p[x], pushup(u, ((ll)pL * sumYL + (ll)pR * sumYR) % P); return u; }
	pushdown(x), pushdown(y);
	p[u].lc = merge(p[x].lc, p[y].lc, pL, pR, sumXL, (sumXR + p[p[x].rc].sum) % P, sumYL, (sumYR + p[p[y].rc].sum) % P, l, mid);
	p[u].rc = merge(p[x].rc, p[y].rc, pL, pR, (sumXL + p[p[x].lc].sum) % P, sumXR, (sumYL + p[p[y].lc].sum) % P, sumYR, mid + 1, r);
	// printf(">>> %d %d %d\n", u, p[u].lc, p[u].rc);
	return maintain(u), u;
}

void output(int u, int l = 1, int r = tn) {
	if (!u) return; pushdown(u);
	printf("[%d => %d %d => %d %d] %d %d\n", u, l, r, p[u].lc, p[u].rc, p[u].sum, p[u].lazy);
	int mid = (l + r) >> 1;
	output(p[u].lc, l, mid), output(p[u].rc, mid + 1, r);
}

void dfs(int u) {
	for (int i = 0; i < siz[u]; i++) dfs(son[u][i]);
	if (!siz[u]) build(rt[u], val[u]);
	else if (siz[u] == 1) rt[u] = rt[son[u][0]];
	else rt[u] = merge(rt[son[u][0]], rt[son[u][1]], val[u], (1 - val[u] + P) % P);
	// printf("dfs %d\n", u);
	// output(rt[u]);
}

int calc(int u, int l = 1, int r = tn) {
	if (!u) return 0; pushdown(u);
	// printf("calc %d => %d %d => %d %d\n", u, l, r, p[u].lc, p[u].rc);
	// if (l == r) printf("[%d] %d %d %d => %d\n", u, l, b[l], p[u].sum, (ll)l * b[l] % P * p[u].sum % P * p[u].sum % P);
	if (l == r) return (ll)l * b[l] % P * p[u].sum % P * p[u].sum % P;
	int mid = (l + r) >> 1;
	return (calc(p[u].lc, l, mid) + calc(p[u].rc, mid + 1, r)) % P;
}

void main() {
	read(n), inv_10000 = fpow(10000, P - 2);
	for (int i = 1; i <= n; i++) {
		read(fa[i]);
		if (fa[i]) son[fa[i]][siz[fa[i]]++] = i;
	}
	for (int i = 1; i <= n; i++) {
		read(val[i]);
		if (!siz[i]) b[++tn] = val[i];
		else val[i] = (ll)val[i] * inv_10000 % P;
	}
	std::sort(b + 1, b + tn + 1);
	for (int i = 1; i <= n; i++) if (!siz[i])
		val[i] = std::lower_bound(b + 1, b + tn + 1, val[i]) - b;
	dfs(1), print(calc(rt[1]), '\n');
}

} signed main() { return ringo::main(), 0; }