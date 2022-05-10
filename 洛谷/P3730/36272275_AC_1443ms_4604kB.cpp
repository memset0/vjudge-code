// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.07 10:11:47
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
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

const int N = 1e5 + 10, M = 400;
int n, m, tn, sqn, lim, a[N], b[N], bln[N], ans[N], fst[M];

namespace bok {
	int cnt[N], cnt_blk[M];
	inline void add(int x) { ++cnt[x], ++cnt_blk[bln[x]]; }
	inline void dec(int x) { --cnt[x], --cnt_blk[bln[x]]; }
	inline int query(int k) {
		for (int i = 1; i <= lim; i++)
			if (k <= cnt_blk[i]) {
				for (int j = fst[i]; j < fst[i + 1]; j++)
					if (k <= cnt[j]) return j;
					else k -= cnt[j];
			} else k -= cnt_blk[i];
		return -1;
	}
}

namespace moq {
	int cnt[N];
	inline void add(int x) { debug("add %d\n", x), bok::dec(cnt[x]), ++cnt[x], bok::add(cnt[x]); }
	inline void dec(int x) { debug("dec %d\n", x), bok::dec(cnt[x]), --cnt[x], bok::add(cnt[x]); }
}

struct query {
	int l, r, k, i;
	inline bool operator < (const query &other) const {
		return bln[l] == bln[other.l] ? r < other.r : l < other.l;
	}
} q[N];

void main() {
	read(n), read(m), sqn = sqrt(n);
	for (int i = 1; i <= n; i++) read(a[i]), bln[i] = (i - 1) / sqn + 1, b[++tn] = a[i];
	std::sort(b + 1, b + tn + 1), tn = std::unique(b + 1, b + tn + 1) - b - 1;
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + tn + 1, a[i]) - b;
	for (int i = 1; i <= n; i++) debug("%d%c", a[i], " \n"[i == n]);
	for (int i = 1; i <= m; i++) read(q[i].l), read(q[i].r), read(q[i].k), q[i].i = i;
	for (int i = n; i >= 1; i--) fst[bln[i]] = i;
	std::sort(q + 1, q + m + 1), lim = (n - 1) / sqn + 1, fst[lim + 1] = n + 1;
	for (int i = 1; i <= m; i++) debug("l=%d r=%d k=%d i=%d\n", q[i].l, q[i].r, q[i].k, q[i].i);
	for (int i = 1, ul = 1, ur = 0, ql, qr; i <= m; i++) {
		ql = q[i].l, qr = q[i].r;
		while (ul > ql) moq::add(a[--ul]);
		while (ur < qr) moq::add(a[++ur]);
		while (ul < ql) moq::dec(a[ul++]);
		while (ur > qr) moq::dec(a[ur--]);
		ans[q[i].i] = bok::query(q[i].k);
	}
	for (int i = 1; i <= n; i++) print(ans[i], '\n');
}

} signed main() { return ringo::main(), 0; }