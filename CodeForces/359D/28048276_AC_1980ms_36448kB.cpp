// =================================
//   author: memset0
//   date: 2019.04.05 17:15:57
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

const int N = 3e5 + 10;
int n, m, max_len, a[N], L[N], R[N];
std::set <int> ans;

struct node {
	int l, r, mid, gcd;
} p[N << 2];

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { p[u].gcd = a[l]; return; }
	build(u << 1, l, p[u].mid);
	build(u << 1 | 1, p[u].mid + 1, r);
	p[u].gcd = std::__gcd(p[u << 1].gcd, p[u << 1 | 1].gcd);
}

int query(int u, int l, int r) {
	if (p[u].l == l && p[u].r == r) return p[u].gcd;
	if (r <= p[u].mid) return query(u << 1, l, r);
	if (l > p[u].mid) return query(u << 1 | 1, l, r);
	return std::__gcd(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]);
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		for (int l = 1, r = i, mid; mid = (l + r) >> 1, l <= r; )
			query(1, mid, i) % a[i] == 0 ? L[i] = mid, r = mid - 1 : l = mid + 1;
		for (int l = i, r = n, mid; mid = (l + r) >> 1, l <= r; )
			query(1, i, mid) % a[i] == 0 ? R[i] = mid, l = mid + 1 : r = mid - 1;
		int len = R[i] - L[i];
		if (len > max_len) max_len = len, ans.clear();
		if (len == max_len) ans.insert(L[i]);
	}
	printf("%d %d\n", ans.size(), max_len);
	for (auto i : ans) print(i, ' ');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}