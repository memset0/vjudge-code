// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.07 15:40:11
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
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

const int N = 5e5 + 10, M = 2e7 + 10, L = 100;
int n, m, lim, end, rit, lst, c_pri, a[N], phi[M], pri[M], mod[L], ans[L];
bool flag[L], vis[M];

struct node {
	int l, r, mid, sum, fst;
} p[N << 2];

inline void push(ll x) {
	// printf(">>> push %d\n", x);
	while (~end)
		if (x >= phi[mod[end]]) flag[end--] = 1;
		else break;
}

inline int fpow(int a, int b, int p) {
	int s = 1; a %= p;
	for (; b; b >>= 1, a = (ll)a * a % p)
		if (b & 1) s = (ll)s * a % p;
	return s;
}

inline int fpow(int a, int b) {
	int s = 1;
	while (b) {
		if (b & 1) push((ll)s * a), s = (ll)s * a % mod[0];
		b >>= 1; if (b) push((ll)a * a), a = (ll)a * a % mod[0];
	} return s;
}

void build(int l, int r, int u = 1) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) { p[u].sum = a[l], p[u].fst = a[l] == 1 ? l : n + 1; return; }
	build(l, p[u].mid, u << 1), build(p[u].mid + 1, r, u << 1 | 1);
	p[u].fst = std::min(p[u << 1].fst, p[u << 1 | 1].fst);
}

void modify(int l, int r, int x, int u = 1) {
	if (p[u].l == l && p[u].r == r) { p[u].sum += x; return; }
	if (r <= p[u].mid) return modify(l, r, x, u << 1);
	if (l > p[u].mid) return modify(l, r, x, u << 1 | 1);
	modify(l, p[u].mid, x, u << 1), modify(p[u].mid + 1, r, x, u << 1 | 1);
}

int query(int k, int u = 1) {
	if (p[u].l == p[u].r) return p[u].sum;
	return p[u].sum + query(k, k <= p[u].mid ? u << 1 : u << 1 | 1);
}

int query_fst(int l, int r, int u = 1) {
	if (p[u].l == l && p[u].r == r) return p[u].fst;
	if (r <= p[u].mid) return query_fst(l, r, u << 1);
	if (l > p[u].mid) return query_fst(l, r, u << 1 | 1);
	return std::min(query_fst(l, p[u].mid, u << 1), query_fst(p[u].mid + 1, r, u << 1 | 1));
}

int solve(int l, int r, int p) {
	// printf("\nsolve %d %d %d\n", l, r, p);
	memset(flag, 0, sizeof(flag));
	mod[lim = 0] = p;
	for (int i = 1; mod[i - 1] != 1; i++)
		mod[i] = phi[mod[i - 1]], ++lim;
	end = lim, rit = query_fst(l, r) - 1, lst = 1;
	if (rit == n + 1) rit = r;
	lim = std::min(lim, rit);
	// printf("rit = %d\n", rit);
	while (rit >= l) {
		if (flag[0]) break;
		end = std::min(end, rit - l - 1);
		lst = fpow(query(rit--), lst);
	}

	if (l + lim < r) ans[lim] = 1;
	else lim = r - l, ans[lim] = query(r);
	ans[lim] %= mod[lim];
	for (int i = lim - 1; i >= 0; i--) {
		// printf("%d -> %d : %d %d %d\n", i, flag[i], query(l + i), ans[i + 1] + (flag[i] ? phi[mod[i]] : 0), mod[i]);
		ans[i] = fpow(query(l + i), ans[i + 1] + (flag[i] ? phi[mod[i]] : 0), mod[i]);
	}
	// for (int i = 0; i <= lim; i++) print(mod[i], " \n"[i == lim]);
	// for (int i = 0; i <= lim; i++) print(ans[i], " \n"[i == lim]);
	// for (int i = 0; i <= lim; i++) print((int)flag[i], " \n"[i == lim]);
	return ans[0] % mod[0];
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(a[i]);
	build(1, n);
	phi[1] = 1;
	for (int i = 2; i < M; i++) {
		if (!vis[i]) pri[++c_pri] = i, phi[i] = i - 1;
		for (int j = 1; j <= c_pri && i * pri[j] < M; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) { phi[i * pri[j]] = phi[i] * pri[j]; break; }
			else phi[i * pri[j]] = phi[i] * (pri[j] - 1);
		}
	}
	// for (int i = 1; i <= 100; i++) print(pri[i], " \n"[i == 100]);
	for (int i = 1, l, r, x, op; i <= m; i++) {
		read(op), read(l), read(r), read(x);
		op == 1 ? modify(l, r, x) : print(solve(l, r, x), '\n');
	}
}

} signed main() { return ringo::main(), 0; }