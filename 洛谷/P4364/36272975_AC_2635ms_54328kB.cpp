// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.07 21:12:07
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

const int N = 5e5 + 10;
int n;
double k;
int a[N], fa[N], siz[N], cnt[N], ans[N], use[N];
bool tag[N];
std::vector <int> son[N];

inline bool cmp(int a, int b) { return a > b; }

struct node {
	int l, r, mid;
	int min, lazy;
} p[N << 2];

inline void pushup(int u, int x) {
	p[u].min += x, p[u].lazy += x;
}

inline void pushdown(int u) {
	if (!p[u].lazy || p[u].l == p[u].r) return;
	pushup(u << 1, p[u].lazy);
	pushup(u << 1 | 1, p[u].lazy);
	p[u].lazy = 0;
}

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { p[u].min = l; return; }
	build(u << 1, l, p[u].mid);
	build(u << 1 | 1, p[u].mid + 1, r);
	p[u].min = std::min(p[u << 1].min, p[u << 1 | 1].min);
}

void modify(int u, int l, int r, int x) {
	// printf("modify %d %d %d %d\n", u, l, r, x);
	pushdown(u);
	if (p[u].l == l && p[u].r == r) return pushup(u, x);
	if (r <= p[u].mid) modify(u << 1, l, r, x);
	else if (l > p[u].mid) modify(u << 1 | 1, l, r, x);
	else modify(u << 1, l, p[u].mid, x), modify(u << 1 | 1, p[u].mid + 1, r, x);
	p[u].min = std::min(p[u << 1].min, p[u << 1 | 1].min);
}

int query(int u, int x) {
	// printf("query %d[%d %d : %d] %d\n", u, p[u].l, p[u].r, p[u].min, x);
	pushdown(u);
	if (p[u].l == p[u].r) return p[u].min >= x ? p[u].l : p[u].l + 1;
	if (p[u << 1 | 1].min >= x) return query(u << 1, x);
	return query(u << 1 | 1, x);
}

void dfs(int u) {
	pushdown(u);
	if (p[u].l == p[u].r) return (void)(print(p[u].min, " \n"[p[u].l == n]));
	dfs(u << 1), dfs(u << 1 | 1);
}

void main() {
	read(n), scanf("%lf", &k);
	for (int i = 1; i <= n; i++) read(a[i]);
	std::sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) son[fa[i] = (i / k)].push_back(i), siz[i] = 1;
	for (int i = n; i >= 1; i--) siz[fa[i]] += siz[i];
	for (int i = n - 1; i >= 1; i--) cnt[i] = a[i] == a[i + 1] ? cnt[i + 1] + 1 : 0;
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		if (fa[i] && tag[fa[i]]) modify(1, ans[fa[i]], n, siz[fa[i]] - 1), tag[fa[i]] = 0;
		ans[i] = query(1, siz[i]), ans[i] += cnt[ans[i]], ans[i] -= use[ans[i]]++;
		tag[i] = 1, modify(1, ans[i], n, -siz[i]);
		// dfs(1);
		// printf(">>> %d %d\n", i, ans[i]);
	}
	for (int i = 1; i <= n; i++) print(a[ans[i]], " \n"[i == n]);
}

} signed main() { return ringo::main(), 0; }