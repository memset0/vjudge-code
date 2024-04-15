// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

#define int long long

template <typename T> inline void read(T &x) {
	x = 0; register char ch; register bool fl = 0;
	while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
	while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
	if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
	while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
	static int buf[40];
	if (x == 0) { putc('0'); putc(c); return; }
	if (x < 0) putc('-'), x = -x;
	for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
	while (buf[0]) putc((char) buf[buf[0]--]);
	putc(c);
}

const int maxn = 100010;
int n, m, l, r, w, opt;
int a[maxn];

struct node {
	int l, r, mid;
	int sum, tag;
} p[maxn << 2];

inline void pushup(int u, int x) {
	p[u].tag += x;
	p[u].sum += x * (p[u].r - p[u].l + 1);
}

inline void pushdown(int u) {
	if (p[u].tag) {
		if (p[u].l == p[u].r)
			return;
		pushup(u << 1, p[u].tag);
		pushup(u << 1 | 1, p[u].tag);
		p[u].tag = 0;
	}
}

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) {
		p[u].sum = a[l];
		return;
	}
	build(u << 1, l, p[u].mid);
	build(u << 1 | 1, p[u].mid + 1, r);
	p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
}

void modify(int u, int l, int r, int x) {
	pushdown(u);
	if (p[u].l == l && p[u].r == r) {
		pushup(u, x);
		return;
	}
	if (r <= p[u].mid) modify(u << 1, l, r, x);
	else if (l > p[u].mid) modify(u << 1 | 1, l, r, x);
	else {
		modify(u << 1, l, p[u].mid, x);
		modify(u << 1 | 1, p[u].mid + 1, r, x);
	}
	p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
}

int query(int u, int l, int r) {
	pushdown(u);
//	printf("query %d %d %d %d %d\n", u, l, r, p[u].l, p[u].r);
	if (p[u].l == l && p[u].r == r)
		return p[u].sum;
	if (r <= p[u].mid) return query(u << 1, l, r);
	else if (l > p[u].mid) return query(u << 1 | 1, l, r);
	else return query(u << 1, l, p[u].mid) +
		query(u << 1 | 1, p[u].mid + 1, r);
}

signed main() {
//	freopen("INPUT", "r", stdin);
	
	read(n), read(m);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		readc(opt), read(l), read(r);
		if (opt == 'Q') print(query(1, l, r), '\n');
		else read(w), modify(1, l, r, w);
	}

	return 0;
}