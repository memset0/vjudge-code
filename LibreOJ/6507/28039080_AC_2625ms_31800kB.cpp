// =================================
//   author: memset0
//   date: 2018.12.28 08:23:53
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)

namespace ringo {
typedef long long ll;
typedef unsigned long long ull;

const int IN_LEN = 1000000, OUT_LEN = 10000000;
char buf[IN_LEN], *s, *t, obuf[OUT_LEN], *ooh = obuf;
inline char read() {
	return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}
inline void print(char c) {
	if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
	*ooh++ = c;
}
template <class T> inline void read(T &x) {
	static bool f = 0; static char c = read();
	for (x = 0; !isdigit(c); c = read()) { f ^= c == '-'; if (c == -1) return; }
	for (; isdigit(c); c = read()) x = ((x + (x << 2)) << 1) + (c ^ '0');
	if (f) x = -x;
}
template<class T> inline void print(T x) {
	static int buf[30], cnt;
	if (!x) { print('0'); return; }
	if (x < 0) print('-'), x = -x;
	for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + '0';
	while (cnt) print((char)buf[cnt--]);
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), print(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 5e5 + 10;
int n, m, a[N];

struct node {
	int l, r, mid, x, y, min, lazy;
	// x => and, y => or
} p[N << 1];

inline void pushup(int u, int dta) {
	p[u].lazy += dta, p[u].x += dta, p[u].y += dta, p[u].min += dta;
}

inline void pushdown(int u) {
	if (!p[u].lazy || p[u].l == p[u].r) return;
	pushup(u << 1, p[u].lazy);
	pushup(u << 1 | 1, p[u].lazy);
	p[u].lazy = 0;
}

inline void maintain(int u) {
	p[u].min = std::min(p[u << 1].min, p[u << 1 | 1].min);
	p[u].x = p[u << 1].x & p[u << 1 | 1].x;
	p[u].y = p[u << 1].y | p[u << 1 | 1].y;
}

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { p[u].x = p[u].y = p[u].min = a[l]; return; }
	build(u << 1, l, p[u].mid), build(u << 1 | 1, p[u].mid + 1, r);
	maintain(u);
}

void modify_x(int u, int l, int r, int x) {
	pushdown(u);
	if (p[u].y == (p[u].y & x)) return;
	if (p[u].l == p[u].r || (l == p[u].l && p[u].r == r && (p[u].x & x) - p[u].x == (p[u].y & x) - p[u].y))
		{ pushup(u, (p[u].x & x) - p[u].x); return; }
	if (r <= p[u].mid) modify_x(u << 1, l, r, x);
	else if (l > p[u].mid) modify_x(u << 1 | 1, l, r, x);
	else modify_x(u << 1, l, p[u].mid, x), modify_x(u << 1 | 1, p[u].mid + 1, r, x);
	maintain(u);
}

void modify_y(int u, int l, int r, int x) {
	pushdown(u);
	if (p[u].x == (p[u].x | x)) return;
	if (p[u].l == p[u].r || (l == p[u].l && p[u].r == r && (p[u].x | x) - p[u].x == (p[u].y | x) - p[u].y))
		{ pushup(u, (p[u].x | x) - p[u].x); return; }
	if (r <= p[u].mid) modify_y(u << 1, l, r, x);
	else if (l > p[u].mid) modify_y(u << 1 | 1, l, r, x);
	else modify_y(u << 1, l, p[u].mid, x), modify_y(u << 1 | 1, p[u].mid + 1, r, x);
	maintain(u);
}

int query(int u, int l, int r) {
	pushdown(u);
	if (p[u].l == l && p[u].r == r) return p[u].min;
	if (r <= p[u].mid) return query(u << 1, l, r);
	if (l > p[u].mid) return query(u << 1 | 1, l, r);
	return std::min(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(a[i]);
	build(1, 1, n);
	for (int i = 1, l, r, x, op; i <= m; i++) {
		read(op), read(l), read(r);
		if (op == 1) read(x), modify_x(1, l, r, x);
		else if (op == 2) read(x), modify_y(1, l, r, x);
		else print(query(1, l, r), '\n');
	}
}

} signed main() { return ringo::main(), ringo::flush(), 0; }
