// luogu-judger-enable-o2
#include <bits/stdc++.h>
namespace ringo {
typedef long long ll;

template < class T >
inline void read(T &x) {
	x = 0; register char c = getchar(); register bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}

template < class T >
inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar('0' + x % 10);
}

template < class T >
inline void print(T x, char c) {
	print(x), putchar(c);
};

const int N = 2e5 + 10;
int n, m, a, b, c, d, l, r, tn, mid, ans, cnt;
int v[N], t[N], rt[N], q[4];
std::vector < int > vet[N];

inline void decode(int &x) { x = (x + ans) % n + 1; }

struct pair {
	int sum, ansl, ansr, ans;
	void init(int x) {
		sum = ansl = ansr = ans = x;
	}
};
inline pair operator + (const pair &a, const pair &b) {
	return (pair) {
		a.sum + b.sum,
		std::max(a.ansl, a.sum + b.ansl),
		std::max(b.ansr, b.sum + a.ansr),
		std::max(a.ansr + b.ansl, std::max(a.ans, b.ans))
	};
}

struct node {
	int lc, rc;
	pair x;
} p[N * 100];

void build(int &u, int l, int r) {
	u = ++cnt;
	if (l == r) { p[u].x.init(1); return; }
	int mid = (l + r) >> 1;
	build(p[u].lc, l, mid);
	build(p[u].rc, mid + 1, r);
	p[u].x = p[u << 1].x + p[u << 1 | 1].x;
}

void modify(int &u, int k, int x, int l = 1, int r = tn) {
	p[++cnt] = p[u], u = cnt;
	if (l == r) { p[u].x.init(x); return; }
	int mid = (l + r) >> 1;
	if (k <= mid) modify(p[u].lc, k, x, l, mid);
	else modify(p[u].rc, k, x, mid + 1, r);
	p[u].x = p[u << 1].x + p[u << 1 | 1].x;
}

pair query(int u, int ql, int qr, int l = 1, int r = tn) {
	if (ql > qr) return (pair){0, 0, 0, 0};
	if (ql == l && qr == r) return p[u].x;
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(p[u].lc, ql, qr, l, mid);
	if (ql > mid) return query(p[u].rc, ql, qr, mid + 1, r);
	return query(p[u].lc, ql, mid, l, mid) + query(p[u].rc, mid + 1, qr, mid + 1, r);
}

bool check(int x) {
	return (
		query(rt[x], a, b).ansr +
		query(rt[x], b + 1, c - 1).ans +
		query(rt[x], c, d).ansl
	) >= 0;
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++)
		read(v[i]), t[i] = v[i];
	std::sort(t + 1, t + n + 1);
	tn = std::unique(t + 1, t + n + 1) - t - 1;
	for (int i = 1; i <= n; i++) {
		v[i] = std::lower_bound(t + 1, t + tn + 1, v[i]) - t;
		vet[v[i]].push_back(i);
	}
	build(rt[0], 1, tn);
	for (int i = 1; i <= tn; i++) {
		rt[i] = rt[i - 1];
		for (std::vector < int > ::iterator it = vet[i - 1].begin(); it != vet[i - 1].end(); it++)
			modify(rt[i], *it, -1);
		for (std::vector < int > ::iterator it = vet[i].begin(); it != vet[i].end(); it++)
			modify(rt[i], *it, 0);
	}
	read(m);
	for (int i = 1; i <= m; i++) {
		read(q[0]), read(q[1]), read(q[2]), read(q[3]);
		for (int i = 0; i < 4; i++) q[i] = (q[i] + ans) % n + 1;
		std::sort(q, q + 4), a = q[0], b = q[1], c = q[2], d = q[3];
		l = 1, r = tn;
		while (l <= r) {
			mid = (l + r) >> 1;
			if (check(mid)) l = mid + 1, ans = t[mid];
			else r = mid - 1;
		}
		print(ans, '\n');
	}
}

} signed main() { return ringo::main(), 0; }