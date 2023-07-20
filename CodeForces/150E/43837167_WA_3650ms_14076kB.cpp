// =================================
//   author: memset0
//   date: 2019.05.09 15:09:27
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 1e5 + 10;
bool flag;
int siz[N], maxp[N], vis[N];
std::pair<int, int> res, ans;
int n, m, L, R, now, root, fullSize;
int tot = 2, hed[N], to[N << 1], val[N << 1], nxt[N << 1];

struct info {
	int nod, len, val;
};
std::vector<info> vet;

namespace seg {
	int top, tag[N], stk[N];
	struct pair {
		int val, nod;
		inline bool operator<(const pair &other) const {
			return val < other.val;
		}
	};
	struct node {
		int l, r, mid;
		pair key;
	} p[N << 2];
	void build(int u, int l, int r) {
		p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1, p[u].key = {-n, -1};
		if (l == r) return;
		build(u << 1, l, p[u].mid);
		build(u << 1 | 1, p[u].mid + 1, r);
	}
	void modify(int u, int k, int nod, int val) {
		// if (u == 1) printf("modify %d %d %d\n", k, nod, val);
		if (!tag[u]) tag[u] = 1, stk[++top] = u;
		if (p[u].l == p[u].r) { p[u].key = std::max(p[u].key, {val, nod}); return; }
		if (k <= p[u].mid) modify(u << 1, k, nod, val);
		else modify(u << 1 | 1, k, nod, val);
		p[u].key = std::max(p[u << 1].key, p[u << 1 | 1].key);
		// printf("%d : %d : %d [%d %d] <- [%d %d] | [%d %d]\n", u, p[u].l, p[u].r, p[u].key.val, p[u].key.nod, p[u << 1].key.val, p[u << 1].key.nod, p[u << 1 | 1].key.val, p[u << 1 | 1].key.nod);
	}
	pair query(int u, int l, int r) {
		// if (u == 1) printf("query %d %d\n", l, r);
		if (p[u].l == l && p[u].r == r) return p[u].key;
		if (r <= p[u].mid) return query(u << 1, l, r);
		if (l > p[u].mid) return query(u << 1 | 1, l, r);
		return std::max(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
	}
	pair query(int k) {
		if (k >= R) return {-1, -1};
		return query(1, std::max(1, L - k), R - k);
	}
	void clear() {
		for (int i = 1; i <= top; i++) {
			tag[stk[i]] = 0;
			p[stk[i]].key = {-n, -1};
		}
		top = 0;
	}
}

void getRoot(int u, int fa = 0) {
	siz[u] = 1, maxp[u] = 0;
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != fa && !vis[v]) {
			getRoot(v, u);
			siz[u] += siz[v];
			maxp[u] = std::max(maxp[u], siz[v]);
		}
	maxp[u] = std::max(maxp[u], fullSize - siz[u]);
	if (maxp[u] < maxp[root]) root = u;
}

void getInfo(int u, int fa, int len, int cnt) {
	vet.push_back({u, len, cnt});
	for (int i = hed[u], v; v = to[i], i; i = nxt[i])
		if (v != fa && !vis[v]) {
			getInfo(v, u, len + 1, cnt + (val[i] >= now ? 1 : -1));
		}
}

void solve(int u) {
	// printf("solve %d\n", u);
	vis[u] = 1;
	for (int i = hed[u], v; v = to[i], (i && !flag); i = nxt[i])
		if (!vis[v]) {
			vet.clear();
			getInfo(v, 0, 1, (val[i] >= now ? 1 : -1));
			for (auto it : vet) {
				if (it.val >= 0 && L <= it.len && it.len <= R) {
					res.first = u, res.second = it.nod, flag = true;
					break;
				}
				auto qry = seg::query(it.len);
				// printf("[%d] nod=%d val=%d len=%d => val=%d nod=%d\n", v, it.nod, it.val, it.len, qry.val, qry.nod);
				if (~qry.nod && qry.val + it.val >= 0) {
					res.first = qry.nod, res.second = it.nod, flag = true;
					break;
				}
			}
			for (auto it : vet) if (it.len <= R)
				seg::modify(1, it.len, it.nod, it.val);
		}
	seg::clear();
	for (int i = hed[u], v; v = to[i], (i && !flag); i = nxt[i])
		if (!vis[v]) {
			fullSize = maxp[root = 0] = siz[v];
			getRoot(v), solve(root);
		}
}

std::pair<int, int> check(int mid) {
	memset(vis, 0, sizeof(vis));
	flag = false, now = mid, res.first = res.second = -1;
	fullSize = maxp[root = 0] = n;
	getRoot(1), solve(root);
	return res;
}

void main() {
	read(n), read(L), read(R);
	for (int u, v, w, i = 1; i < n; i++) {
		read(u), read(v), read(w);
		nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, val[tot] = w, hed[v] = 	tot++;
	}
	seg::build(1, 1, n);
	int l = 0, r = 1e5, mid;
	while (l <= r) {
		auto res = check(mid = (l + r) >> 1);
		// printf("check %d => %d %d\n", mid, res.first, res.second);
		flag ? (ans = res, l = mid + 1) : r = mid - 1;
	}
	print(ans.first, ' '), print(ans.second, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}