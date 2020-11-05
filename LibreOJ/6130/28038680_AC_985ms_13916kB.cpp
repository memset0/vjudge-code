// =================================
//   author: memset0
//   date: 2019.01.05 10:27:24
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>

#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")

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

const int N = 2e5 + 10;
int n, m, tn;
int a[N], b[N], s[N], f[N], g[N], q[N], tmp[N];

inline bool cmp(int x, int y) {
	return f[x] == f[y] ? x > y : f[x] > f[y];
}

inline int ask(int k) {
	int sum = 0;
	for (; k <= n; k += k & -k)
		sum += s[k];
	return sum;
}

inline void add(int k, int x) {
	for (; k; k -= k & -k)
		s[k] += x;
}

inline int ask2(int k) {
	int sum = 0;
	for (; k; k -= k & -k)
		sum += s[k];
	return sum;
}

inline void add2(int k, int x) {
	for (; k <= n; k += k & -k)
		s[k] += x;
}

struct node {
	int l, r, mid, sum;
} p[N << 2];

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1, p[u].sum = r - l + 1;
	if (l == r) return;
	build(u << 1, l, p[u].mid);
	build(u << 1 | 1, p[u].mid + 1, r);
}

void modify(int u, int k, int v) {
	if (p[u].l == p[u].r) { b[p[u].l] = v, p[u].sum = 0; return; }
	if (k <= p[u << 1].sum) modify(u << 1, k, v);
	else modify(u << 1 | 1, k - p[u << 1].sum, v);
	p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(a[i]), tmp[++tn] = a[i];
	std::sort(tmp + 1, tmp + tn + 1), tn = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + tn + 1, a[i]) - tmp;
	for (int i = 1; i <= n; i++) {
		f[i] = ask(a[i] + 1);
		f[i] = std::min(m, f[i]);
		add(a[i], 1);
	}
	for (int i = 1; i <= n; i++) q[i] = i;
	memset(s, 0, sizeof(s));
	std::sort(q + 1, q + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		g[q[i]] = q[i] - ask2(q[i] - 1) - f[q[i]];
		add2(q[i], 1);
	}
	build(1, 1, n);
	for (int i = 1; i <= n; i++)
		modify(1, g[q[i]], a[q[i]]);
	for (int i = 1; i <= n; i++) print(tmp[b[i]], '\n');
}

} signed main() { return ringo::main(), 0; }
