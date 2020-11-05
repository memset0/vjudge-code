// =================================
//   author: memset0
//   date: 2019.03.20 22:54:35
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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

const int N = 1e5 + 10;
int n, m, k, ans, a[N], f[N];

struct seg {
	int min[N << 2];
	void modify(int u, int k, int v, int l = 0, int r = n) {
		// printf("modify %d %d %d %d %d\n", u, k, v, l, r);
		if (l == r) { min[u] = v; return; }
		int mid = (l + r) >> 1;
		if (k <= mid) modify(u << 1, k, v, l, mid);
		else modify(u << 1 | 1, k, v, mid + 1, r);
		min[u] = std::min(min[u << 1], min[u << 1 | 1]);
	}
	int query(int u, int ql, int qr, int l = 0, int r = n) {
		// printf("query %d %d %d %d %d : %d\n", u, ql, qr, l, r, min[u]);
		if (ql > qr) return f[N - 1];
		if (ql == l && qr == r) return min[u];
		int mid = (l + r) >> 1;
		if (qr <= mid) return query(u << 1, ql, qr, l, mid);
		if (ql > mid) return query(u << 1 | 1, ql, qr, mid + 1, r);
		return std::min(query(u << 1, ql, mid, l, mid), query(u << 1 | 1, mid + 1, qr, mid + 1, r));
	}
} s[2];

void main() {
	memset(f, 0x3f, sizeof(f));
	memset(s[0].min, 0x3f, sizeof(s[0].min));
	memset(s[1].min, 0x3f, sizeof(s[1].min));
	read(n), read(m), read(k);
	for (int i = 1; i <= n; i++) read(a[i]);
	f[0] = 0;
	s[0].modify(1, 0, -2 * a[1]);
	s[1].modify(1, 0, 0);
	for (int i = 1, from; i <= n; i++) {
		int j = std::lower_bound(a, a + i, (a[i] * 2 - k + 1) >> 1) - a - 1;
		f[i] = std::min(f[i], 3 * a[i] + s[0].query(1, std::max((int)0, (int)0), std::min(n, j - 1)));
		f[i] = std::min(f[i], a[i] + k + s[1].query(1, std::max((int)0, (int)j), std::min(n, i - 1)));
		s[0].modify(1, i, f[i] - a[i] - 2 * a[i + 1]);
		s[1].modify(1, i, f[i] - a[i]);
		// printf("[%d %d] %d %d | [%d %d] %d %d\n",
		// 	0, j - 1, 3 * a[i], s[0].query(1, 0, j - 1),
		// 	j, i - 1, a[i] + k, s[1].query(1, j, i - 1));
	}
	ans = f[n] + m - a[n];
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }