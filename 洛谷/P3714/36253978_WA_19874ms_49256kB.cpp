// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i, l, r) for (int i = l; i <= r; ++i)
namespace ringo {

template < class T > il void read(T &x) {
	x = 0; rg char c = getc(); rg bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getc();
	while (isdigit(c)) x = x * 10 + c - '0', c = getc();
	if (f) x = -x;
}

template < class T > il void print(T x) {
	if (x < 0) putc('-'), x = -x;
	if (x > 9) print(x / 10);
	putc('0' + x % 10);
}

const int maxn = 200010, inf = 1000000000;
int n, m, l, r, u, v, w, ans, root, full_size;
int c[maxn], dis[maxn], cst[maxn], col[maxn], vis[maxn], siz[maxn], maxp[maxn];
int tot = 2, hed[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1];
std::vector < int > rub1, rub2;

struct status { int node, col, dis, cst; };
std::vector < status > vet;
typedef std::vector < status > ::iterator iterator;

void get_root(int u, int father) {
	siz[u] = 1, maxp[u] = 0;
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (!vis[v] && v != father) {
			get_root(v, u);
			siz[u] += siz[v];
			maxp[u] = std::max(maxp[u], siz[v]);
		}
	maxp[u] = std::max(maxp[u], full_size - siz[u]);
	if (maxp[u] < maxp[root]) root = u;
}

void get_dis(int u, int father) {
	vet.push_back((status){u, col[u], dis[u], cst[u]});
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (!vis[v] && v != father) {
			dis[v] = dis[u] + 1, cst[v] = cst[u] + (val[i] == col[u] ? 0 : c[val[i]]), col[v] = val[i];
			get_dis(v, u);
		}
}

namespace seg1 {
	struct node { int l, r, mid, mx1, mx2, at; } p[maxn << 2];
	void build(int u, int l, int r) {
		p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
		p[u].mx1 = p[u].mx2 = -inf, p[u].at = 0;
		if (l == r) return;
		build(u << 1, l, p[u].mid);
		build(u << 1 | 1, p[u].mid + 1, r);
	}
	void modify(int u, int k, int c, int v) {
		// printf("modify %d %d %d %d\n", u, k, c, v);
		if (p[u].l == p[u].r) {
			if (v > p[u].mx1) p[u].mx2 = p[u].mx1, p[u].mx1 = v, p[u].at = c;
			else if (v > p[u].mx2 && c != p[u].at) p[u].mx2 = v;
			return;
		}
		modify(k <= p[u].mid ? u << 1 : u << 1 | 1, k, c, v);
		if (p[u << 1].mx1 > p[u << 1 | 1].mx1) {
			p[u].mx1 = p[u << 1].mx1, p[u].at = p[u << 1].at;
			p[u].mx2 = std::max(p[u << 1].mx2, p[u << 1 | 1].mx1);
		} else {
			p[u].mx1 = p[u << 1 | 1].mx1, p[u].at = p[u << 1 | 1].at;
			p[u].mx2 = std::max(p[u << 1 | 1].mx2, p[u << 1].mx1);
		}
	}
	void erase(int u, int k) {
		p[u].mx1 = p[u].mx2 = -inf, p[u].at = 0;
		if (p[u].l == p[u].r) { return; }
		erase(k <= p[u].mid ? u << 1 : u << 1 | 1, k);
	}
	int query(int u, int l, int r, int c) {
		if (p[u].l == l && p[u].r == r) return p[u].at == c ? p[u].mx2 : p[u].mx1;
		if (r <= p[u].mid) return query(u << 1, l, r, c);
		if (l > p[u].mid) return query(u << 1 | 1, l, r, c);
		return std::max(query(u << 1, l, p[u].mid, c), query(u << 1 | 1, p[u].mid + 1, r, c));
	}
}

namespace seg2 {
	const int maxm = maxn * 20;
	int cnt, root[maxn], lc[maxm], rc[maxm], max[maxm];
	void modify(int &u, int k, int v, int l, int r) {
		if (!u) u = ++cnt, lc[u] = rc[u] = 0, max[u] = -inf;
		max[u] = std::max(max[u], v);
		if (l == r) { max[u] = std::max(max[u], v); return; }
		int mid = (l + r) >> 1;
		if (k <= mid) modify(lc[u], k, v, l, mid);
		else modify(rc[u], k, v, mid + 1, r);
	}
	int query(int u, int ql, int qr, int l, int r) {
		if (!u) return -inf;
		if (ql == l && qr == r) return max[u];
		int mid = (l + r) >> 1;
		if (qr <= mid) return query(lc[u], ql, qr, l, mid);
		if (ql > mid) return query(rc[u], ql, qr, mid + 1, r);
		return std::max(query(lc[u], ql, mid, l, mid), query(rc[u], mid + 1, qr, mid + 1, r));
	}
}

void solve(int u) {
	// printf("===== solve %d =====\n", u);
	vis[u] = 1;
	seg1::modify(1, 0, 0, 0);
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (!vis[v]) {
			// printf("----- %d -----\n", v);
			dis[v] = 1, cst[v] = c[val[i]], col[v] = val[i];
			vet.clear(), get_dis(v, u);
			for (iterator it = vet.begin(); it != vet.end(); it++) {
				// printf("%d %d %d %d\n", it->node, it->col, it->dis, it->cst);
				if (r - it->dis < 0) continue;
				int other = seg2::query(seg2::root[col[v]], std::max(l - it->dis, 0), r - it->dis, 0, n) - c[col[v]];
				other = std::max(other, seg1::query(1, std::max(l - it->dis, 0), r - it->dis, col[v]));
				ans = std::max(ans, other + it->cst);
			}
			for (iterator it = vet.begin(); it != vet.end(); it++) {
				seg1::modify(1, it->dis, col[v], it->cst);
				seg2::modify(seg2::root[col[v]], it->dis, it->cst, 0, n);
				rub1.push_back(it->dis), rub2.push_back(it->col);
			}
		}
	seg2::cnt = 0;
	for (std::vector < int > ::iterator it = rub1.begin(); it != rub1.end(); it++)
		seg1::erase(1, *it);
	for (std::vector < int > ::iterator it = rub2.begin(); it != rub2.end(); it++)
		seg2::root[*it] = 0;
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (!vis[v]) {
			root = 0, maxp[root] = full_size = siz[v];
			get_root(v, u), solve(root);
		}
}

void main() {
	read(n), read(m), read(l), read(r), ans = -inf;
	for (int i = 1; i <= m; i++) read(c[i]);
	seg1::build(1, 0, n);
	for (int i = 1; i < n; i++) {
		read(u), read(v), read(w);
		nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, val[tot] = w, hed[v] = tot++;
	}
	root = 0, maxp[root] = full_size = n;
	get_root(1, 0), solve(root);
	print(ans), putc('\n');
}

} int main() { return ringo::main(), 0; }
