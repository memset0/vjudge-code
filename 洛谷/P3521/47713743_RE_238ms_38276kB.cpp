// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.17 14:00:36
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
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

const int N = 4e5 + 10, M = 3e6 + 3e5;
int n, cnt, nod, root;
int lc[M], rc[M], rt[N], val[N], ch[N][2];
ll ans, now, limit, sum[M];

void reader(int &u) {
	u = ++cnt, read(val[u]);
	if (!val[u]) reader(ch[u][0]), reader(ch[u][1]);
}

void modify(int &u, int k, int l = 1, int r = n) {
	u = ++nod;
	if (l == r) { sum[u] = 1; return; }
	int mid = (l + r) >> 1;
	if (k <= mid) modify(lc[u], k, l, mid);
	else modify(rc[u], k, mid + 1, r);
	sum[u] = sum[lc[u]] + sum[rc[u]];
}

void merge(int &x, int y, int sumR, int l = 1, int r = n) {
	if (!y) return;
	else if (!x) { x = y, now += (ll)sumR * sum[y]; return ; }
	else {
		int mid = (l + r) >> 1;
		merge(lc[x], lc[y], sumR + sum[rc[x]], l, mid);
		merge(rc[x], rc[y], sumR, mid + 1, r);
		sum[x] = sum[lc[x]] + sum[rc[x]];
	}
}

void main() {
	read(n), reader(root);
	for (int i = 1; i <= cnt; i++)
		if (val[i]) modify(rt[i], val[i]);
	for (int u = cnt; u >= 1; u--)
		if (!val[u]) {
			limit = (ll)sum[rt[ch[u][0]]] * sum[rt[ch[u][1]]], now = 0;
			merge(rt[ch[u][0]], rt[ch[u][1]], 0, 0), rt[u] = rt[ch[u][0]];
			ans += std::min(now, limit - now);
		}
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }