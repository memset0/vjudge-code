// =================================
//   author: memset0
//   date: 2019.04.06 11:29:18
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

const int N = 2e5 + 10;
int n, m;

struct seg {
	static const int M = N * 30;
	int rt, cnt, lim[M], lc[M], rc[M];
	void modify(int &u, int ql, int qr, int v, int l, int r) {
		if (!u) u = ++cnt;
		// printf(">> modify %d %d %d %d %d %d\n", u, ql, qr, v, l, r);
		if (ql == l && qr == r) { lim[u] = std::max(lim[u], v); return; }
		int mid = (l + r) >> 1;
		if (qr <= mid) modify(lc[u], ql, qr, v, l, mid);
		else if (ql > mid) modify(rc[u], ql, qr, v, mid + 1, r);
		else modify(lc[u], ql, mid, v, l, mid), modify(rc[u], mid + 1, qr, v, mid + 1, r);
	}
	int query(int u, int ql, int qr, int l, int r) {
		if (!u) return 0;
		if (ql == l && qr == r) return lim[u];
		int mid = (l + r) >> 1;
		if (qr <= mid) return std::max(lim[u], query(lc[u], ql, qr, l, mid));
		if (ql > mid) return std::max(lim[u], query(rc[u], ql, qr, mid + 1, r));
		return std::max(lim[u], std::max(query(lc[u], ql, mid, l, mid), query(rc[u], mid + 1, qr, mid + 1, r)));
	}
	inline int query(int k) { return query(rt, k, k, 1, n); }
	inline void modify(int k, int v) { modify(rt, k, k, v, 1, n); }
	inline int query(int l, int r) { return query(rt, l, r, 1, n); }
	inline void modify(int l, int r, int v) { modify(rt, l, r, v, 1, n); }
} l, u;

int main() {
	read(n), read(m);
	for (int i = 1, x, y, opt, limit; i <= m; i++) {
		read(x), read(y), opt = getchar();
		// printf(">>> %d %d %c\n", x, y, opt);
		if (opt == 'U') {
			limit = u.query(x);
			print(y - limit, '\n');
			if (y != limit) {
				u.modify(x, y);
				l.modify(x, n - limit, x);
			}
		} else if (opt == 'L') {
			limit = l.query(x);
			print(x - limit, '\n');
			if (x != limit) {
				l.modify(x, x);
				u.modify(limit + 1, x, y);
			}
		}
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}