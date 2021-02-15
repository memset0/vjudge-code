// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.29 17:59:31
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

const int N = 2e5 + 10, mod = 1e9 + 7;
std::set<int> set[N];
std::map<std::pair<int, int>, int> map;
int fa[N], fac[N], ifac[N], root[N];
int W, n, m, cnt, nod, sum, ans, baseans, basesum;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int C(int a, int b) { return a < b ? 0 : mul(fac[a], mul(ifac[b], ifac[a - b])); }

struct node {
	int left, right, lson, rson, siz;
	inline void init(int l, int r) { left = l, right = r; }
} p[N];

void build(int u) {
	map[std::make_pair(p[u].left, p[u].right)] = u;
	if (p[u].left + 1 < p[u].right) {
		int mid = *set[p[u].right].upper_bound(p[u].left);
		p[u].lson = ++nod, p[nod].init(p[u].left, mid), fa[nod] = u, build(nod);
		p[u].rson = ++nod, p[nod].init(mid, p[u].right), fa[nod] = u, build(nod);
		p[u].siz = p[p[u].lson].siz + p[p[u].rson].siz + 1;
	}
	// printf("%d : %d %d : %d %d\n", u, p[u].left, p[u].right, p[u].lson, p[u].rson);
	ans = mul(ans, C(p[p[u].lson].siz + p[p[u].rson].siz, p[p[u].rson].siz));
}

void main() {
	read(W), read(n), sum = n - 3;
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= n; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	for (int i = 1; i <= n; i++) {
		set[i].insert(i == n ? 1 : i + 1);
		set[i].insert(i == 1 ? n : i - 1);
	}
	for (int i = 1, u, v; i <= n - 3; i++) {
		read(u), read(v);
		set[u].insert(v), set[v].insert(u);
		if (u == n || v == n) sum--;
	}
	ans = fac[sum];
	int last = -1;
	for (auto u : set[n]) {
		if (~last) {
			root[++cnt] = ++nod, p[nod].init(last, u);
			build(nod), ans = mul(ans, ifac[p[root[cnt]].siz]);
		}
		last = u;
	}
	baseans = ans, basesum = sum;
	W ? (print(sum, ' '), print(ans, '\n')) : print(sum, '\n');
	read(m);
	for (int i = 1, a, b, c, d; i <= m; i++) {
		read(a), read(c), sum = basesum, ans = baseans;
		if (a > c) std::swap(a, c);
		b = *set[c].upper_bound(a);
		d = *set[c].rbegin() == a ? *set[c].begin() : *set[c].rbegin();
		// printf(">> %d %d %d %d | %d %d\n", a, b, c, d, set[a].count(c), set[b].count(d));
		ans = mul(ans, ifac[sum]);
		sum += (a == n || c == n) - (b == n || d == n);
		ans = mul(ans, fac[sum]);
		if (W && d == n) {
			int u = map[std::make_pair(a, c)];
			ans = mul(ans, mul(ifac[p[p[u].lson].siz], ifac[p[p[u].rson].siz]));
			ans = mul(ans, mul(fac[p[u].siz], inv(C(p[p[u].lson].siz + p[p[u].rson].siz, p[p[u].rson].siz))));
		} else if (W) {
			int u = map[std::make_pair(a, d)], v = p[u].lson;
			int x = p[v].lson, y = p[v].rson, z = p[u].rson;
			ans = mul(ans, inv(C(p[p[u].lson].siz + p[p[u].rson].siz, p[p[u].rson].siz)));
			ans = mul(ans, inv(C(p[p[v].lson].siz + p[p[v].rson].siz, p[p[v].rson].siz)));
			ans = mul(ans, C(p[x].siz + p[y].siz + p[z].siz + 1, p[x].siz));
			ans = mul(ans, C(p[y].siz + p[z].siz, p[y].siz));
		}
		W ? (print(sum, ' '), print(ans, '\n')) : print(sum, '\n');
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}