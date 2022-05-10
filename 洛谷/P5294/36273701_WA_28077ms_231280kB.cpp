// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.10 22:05:25
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
	x = 0; char c = getchar(); bool f = 0;
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

const int N = 1e5 + 10, mod = 998244353;
int n, m, a[N], s1[N], s2[N]; ll s3[N];

inline int sqr(int x) { return (ll)x * x - (ll)x * x / mod * mod; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int calc(int s0, int s1, int s2) { return dec(s2, mul(sqr(s1), inv(s0))); }

struct frac {
	ll a; int b;
	inline frac() {}
	inline frac(ll x, int y) { a = x, b = y; }
	inline int v() const { return (a % mod * inv(b)) % mod; }
	inline bool operator<(const frac &other) const {
		return (__int128)a * other.b < (__int128)b * other.a;
	}
};

struct info {
	frac val;
	int l, r, cost;
	inline info() {}
	inline info(int _l, int _r) {
		l = _l, r = _r;
		val = frac(s3[r] - s3[l - 1], r - l + 1);
		cost = calc(r - l + 1, dec(s1[r], s1[l - 1]), dec(s2[r], s2[l - 1]));
	}
};

struct seg {
	static const int M = N * 30;
	int nod, flag, rt[N], top[N];
	struct node {
		int lc, rc, sum; info x;
	} p[M];
	inline seg(int _flag) { flag = _flag; }
	void build(int &u, int l = 1, int r = n) {
		u = ++nod;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(p[u].lc, l, mid);
		build(p[u].rc, mid + 1, r);
	}
	void modify(int &u, int v, int k, const info &x, int l = 1, int r = n) {
		p[u = ++nod] = p[v];
		if (l == r) { p[u].sum = (p[u].x = x).cost; return; }
		int mid = (l + r) >> 1;
		if (k <= mid) modify(p[u].lc, p[v].lc, k, x, l, mid);
		else modify(p[u].rc, p[v].rc, k, x, mid + 1, r);
		p[u].sum = inc(p[p[u].lc].sum, p[p[u].rc].sum);
	}
	info query(int u, int k, int l = 1, int r = n) {
		if (l == r) return p[u].x;
		int mid = (l + r) >> 1;
		if (k <= mid) return query(p[u].lc, k, l, mid);
		return query(p[u].rc, k, mid + 1, r);
	}
	int querySum(int u, int ql, int qr, int l = 1, int r = n) {
		if (ql == l && qr == r) return p[u].sum;
		int mid = (l + r) >> 1;
		if (qr <= mid) return querySum(p[u].lc, ql, qr, l, mid);
		if (ql > mid) return querySum(p[u].rc, ql, qr, mid + 1, r);
		return inc(querySum(p[u].lc, ql, mid, l, mid), querySum(p[u].rc, mid + 1, qr, mid + 1, r));
	}
	void add(int k) {
		info now(k, k);
		if (flag == 1) {
			rt[k] = rt[k - 1], top[k] = top[k - 1];
		} else {
			rt[k] = rt[k + 1], top[k] = top[k + 1];
		}
		modify(rt[k], rt[k], ++top[k], now);
		while (top[k] >= 2) {
			auto pre = query(rt[k], top[k] - 1);
			if (flag == 1) {
				if (now.val < pre.val) {
					now = info(pre.l, now.r);
					modify(rt[k], rt[k], --top[k], now);
				} else break;
			} else {
				if (pre.val < now.val) {
					now = info(now.l, pre.r);
					modify(rt[k], rt[k], --top[k], now);
				} else break;
			}
		}
		// printf("add(%d) => ", k);
		// for (int i = 1; i <= top[k]; i++) {
		// 	auto it = query(1, i);
		// 	printf("[%d %d : %d]%c", it.l, it.r, it.cost, " \n"[i == top[k]]);
		// }
	}
} t1(1), t2(2);

inline int solve(int l, int r, int nw, int od) {
	frac left(-1, 1), right(-1, 1), mid(s3[r] - s3[l - 1] + nw - od, r - l + 1);
	int cost = calc(r - l + 1, inc(dec(s1[r], s1[l - 1]), dec(nw, od)), inc(dec(s2[r], s2[l - 1]), dec(sqr(nw), sqr(od))));
	// printf("solve l=%d r=%d new=%d old=%d cost=%d\n", l, r, nw, od, cost);
	if (l > 1) {
		left = t1.query(t1.rt[l - 1], t1.top[l - 1]).val;
		// printf("left => %lld %d | mid => %lld %d\n", left.a, left.b, mid.a, mid.b);
		if (mid < left) return -1;
		cost = inc(cost, t1.querySum(t1.rt[l - 1], 1, t1.top[l - 1]));
	}
	if (r < n) {
		right = t2.query(t2.rt[r + 1], t2.top[r + 1]).val;
		// printf("mid => %lld %d | right => %lld %d\n", mid.a, mid.b, right.a, right.b);
		if (right < mid) return -1;
		cost = inc(cost, t2.querySum(t2.rt[r + 1], 1, t2.top[r + 1]));
	}
	// printf(">> %d %d %d : %d\n", left.v(), mid.v(), right.v(), cost);	
	return cost;
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		s3[i] = s3[i - 1] + a[i];
		s1[i] = inc(s1[i - 1], a[i]);
		s2[i] = inc(s2[i - 1], sqr(a[i]));
	}
	t1.build(t1.rt[0]), t2.build(t2.rt[n + 1]);
	for (int i = 1; i <= n; i++) t1.add(i);
	for (int i = n; i >= 1; i--) t2.add(i);
	print(t1.querySum(t1.rt[n], 1, t1.top[n]), '\n');
	// printf("t1: "); for (int i = 1; i <= n; i++) print(t1.querySum(t1.rt[i], 1, t1.top[i]), " \n"[i == n]);
	// printf("t2: "); for (int i = 1; i <= n; i++) print(t2.querySum(t2.rt[i], 1, t2.top[i]), " \n"[i == n]);
	for (int i = 1, x, y, lL, lR, rL, rR, mL, mR, now, ans, L, R; i <= m; i++) {
		read(x), read(y);
		ans = -1, lR = x, rR = n;
		while (lR <= rR) {
			mR = (lR + rR) >> 1;
			lL = 1, rL = x, L = -1;
			while (lL <= rL) {
				mL = (lL + rL) >> 1;
				now = solve(mL, mR, y, a[x]);
				if (~now) lL = mL + 1, L = mL, ans = now;
				else rL = mL - 1;
			}
			if (~L) rR = mR - 1, R = mR;
			else lR = mR + 1;
		}
		print(ans, '\n');
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}