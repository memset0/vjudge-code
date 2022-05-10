// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

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

const int maxn = 100010, maxm = maxn * 60;

int n, m, u, k, ta, tb, tc, tn, cnt, lastans;
int b[maxn], rt[maxn];
int lc[maxm], rc[maxm], sum[maxm], siz[maxm];

struct node {
	int l, r, v;
} a[maxn];

struct todo {
	int k, v;
};
std::vector < todo > c[maxn];

void build(int &u, int l, int r) {
	u = ++cnt;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(lc[u], l, mid);
	build(rc[u], mid + 1, r);
}

void insert(int &u, int v, int k, int c, int l, int r) {
	u = ++cnt, lc[u] = lc[v], rc[u] = rc[v];
	if (l == r) {
		siz[u] += c;
		sum[u] += b[k] * c;
		return;
	}
	int mid = (l + r) >> 1;
	if (k <= mid) insert(lc[u], lc[v], k, c, l, mid);
	else insert(rc[u], rc[v], k, c, mid + 1, r);
	siz[u] = siz[lc[u]] + siz[rc[u]];
	sum[u] = sum[lc[u]] + sum[rc[u]];
}

int query(int u, int k, int l = 1, int r = tn) {
//	printf("query %d(%d) %d(%d) %d(%d) %d %d %d\n", u, sum[u], lc[u], sum[lc[u]], rc[u], sum[rc[u]], k, l, r);
	if (l == r) {
		return sum[u];
	}
	int mid = (l + r) >> 1;
	if (k <= siz[lc[u]])
		return query(lc[u], k, l, mid);
	else
		return query(rc[u], k - siz[lc[u]], mid + 1, r) + sum[lc[u]];
}

int main() {

	read(n), read(m);
	for (int i = 1; i <= n; i++)
		read(a[i].l), read(a[i].r), read(a[i].v);
	for (int i = 1; i <= n; i++)
		b[i] = a[i].v;
	std::sort(b + 1, b + n + 1);
	tn = std::unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++)
		a[i].v = std::lower_bound(b + 1, b + tn + 1, a[i].v) - b;
	for (int i = 1; i <= m; i++) {
		c[a[i].l].push_back(todo{a[i].v, 1});
		c[a[i].r + 1].push_back(todo{a[i].v, -1});
	}
	build(rt[0], 1, tn);
	for (int i = 1; i <= n; i++) {
		for (std::vector < todo > ::iterator it = c[i].begin(); it != c[i].end(); it++) {
			insert(rt[i], rt[i] ? rt[i] : rt[i - 1], it->k, it->v, 1, tn);
//			printf(">>> %d %d %d\n", i, it->k, it->v);
		}
	}
	lastans = 1;
	for (int i = 1; i <= m; i++) {
		read(u), read(ta), read(tb), read(tc);
		k = 1 + (lastans * ta + tb) % tc;
//		printf("<<< %d %d\n", u, k);
		print(lastans = query(rt[u], k), '\n');
	}
	
	return 0;
}