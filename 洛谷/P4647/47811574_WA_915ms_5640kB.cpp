// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.03 19:23:30
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

const int N = 1e5 + 10;
int n, m; ll ans;

struct node {
	int h, k;
	inline bool operator < (const node &other) const {
		return h < other.h;
	}
} a[N];

struct seg_node {
	int l, r, mid, sum;
} p[N << 2];

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { return; }
	build(u << 1, l, p[u].mid), build(u << 1 | 1, p[u].mid + 1, r);
}

void modify(int u, int l, int r, int x) {
	if (l == p[u].l && r == p[u].r) { p[u].sum += x; return; }
	if (r <= p[u].mid) modify(u << 1, l, r, x);
	else if (l > p[u].mid) modify(u << 1 | 1, l, r, x);
	else modify(u << 1, l, p[u].mid, x), modify(u << 1 | 1, p[u].mid + 1, r, x);
}

int query(int u, int k) {
	if (p[u].l == p[u].r) return p[u].sum;
	return query(k <= p[u].mid ? u << 1 : u << 1 | 1, k) + p[u].sum;
}

int query_bound(int _l, int _r, int k) {
	int ans = _l - 1;
	// printf("query bound %d %d %d\n", _l, _r, k);
	for (int l = _l, r = _r, mid, x; mid = (l + r) >> 1, l <= r; ) {
		x = query(1, mid);
		if (x == k) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return ans;
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i].h), read(a[i].k);
	std::sort(a + 1, a + n + 1), build(1, 1, m = a[n].h);
	for (int i = 1, pos, limit = m + 1, length; i <= n; i++) {
		limit -= a[i].h - a[i - 1].h;
		// printf("main [%d %d] %d\n", a[i].h, a[i].k, limit);
		modify(1, limit, limit + a[i].k - 1, 1);
		// for (int i = 1; i <= m; i++)
		// 	print(query(1, i), " \n"[i == m]);
		if (limit + a[i].k - 1 == m) continue;
		if (query(1, limit + a[i].k - 1) > query(1, limit + a[i].k)) {
			pos = query_bound(limit, limit + a[i].k - 1, query(1, limit + a[i].k) + 1);
			// printf("========> %d %d\n", query(1, m) + 1, query(1, limit + a[i].k - 1));
			length = limit + a[i].k - pos;
			// printf("len=%d [%d %d] [%d %d]\n", length, pos, pos + length - 1, n - length + 1, n);
			modify(1, pos, pos + length - 1, -1);
			modify(1, m - length + 1, m, 1);
		}
		// for (int i = 1; i <= m; i++)
		// 	print(query(1, i), " \n"[i == m]);
		// puts("");
	}
	for (int i = 1, x; i <= m; i++)
		x = query(1, i), ans += (ll)x * (x - 1) / 2;
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }