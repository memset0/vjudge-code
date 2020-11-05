// =================================
//   author: memset0
//   date: 2019.06.26 12:44:20
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

const int N = 5e5 + 10;
std::vector<int> son[N];
int T, n, cnt, flag, p[N], nxt[N], max[N << 2];

void dfs(int u) {
	for (auto v : son[u]) dfs(v);
	if (u != n + 1) p[u] = ++cnt;
}

void build(int u, int l, int r) {
	// printf("build %d %d %d\n", u, l, r);
	if (l == r) { max[u] = nxt[l]; return; }
	int mid = (l + r) >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	max[u] = std::max(max[u << 1], max[u << 1 | 1]);
}

int query(int u, int ql, int qr, int l, int r) {
	// printf("query %d %d %d %d %d\n", u, ql, qr, l, r);
	if (ql == l && qr == r) return max[u];
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(u << 1, ql, qr, l, mid);
	if (ql > mid) return query(u << 1 | 1, ql, qr, mid + 1, r);
	return std::max(query(u << 1, ql, mid, l, mid), query(u << 1 | 1, mid + 1, qr, mid + 1, r));
}

void main() {
	for (read(T); T--; ) {
		read(n);
		for (int i = 1; i <= n + 1; i++) son[i].clear();
		for (int i = 1; i <= n; i++) read(nxt[i]);
		for (int i = n; i >= 1; i--) son[~nxt[i] ? nxt[i] : i + 1].push_back(i);
		build(1, 1, n);
		for (int i = 1; i <= n; i++)
			if (~nxt[i] && (nxt[i] <= i || query(1, i, nxt[i] - 1, 1, n) > nxt[i]))
				flag = 1;
		if (flag) { flag = 0; puts("-1"); continue; }
		cnt = 0, dfs(n + 1);
		for (int i = 1; i <= n; i++) print(p[i], " \n"[i == n]);
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}