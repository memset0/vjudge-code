// =================================
//   author: memset0
//   date: 2019.04.30 14:25:19
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

const int N = 2e5 + 10;
int n, m;
char s[N];

#define U p[u]
#define L p[u << 1]
#define R p[u << 1 | 1]
struct node {
	int l, r, mid;
	int sum, ans, max, min, max1, max2;
	inline void init(int k, int w) {
		sum = w == '(' ? 1 : -1;
		max = min = sum;
		max1 = max2 = -sum;
		ans = -1e9;
	}
} p[N << 2];
// a, b, c => max(s_a + s_c - 2 s_b)

inline void maintain(int u) {
	U.sum = L.sum + R.sum;
	U.max = std::max(L.max, L.sum + R.max);
	U.min = std::min(L.min, L.sum + R.min);
	U.max1 = std::max(std::max(L.max1, R.max1 - L.sum), L.max - ((R.min + L.sum) << 1));
	U.max2 = std::max(std::max(L.max2, R.max2 - L.sum),	R.max + L.sum - (L.min << 1));
	U.ans = std::max(std::max(L.ans, R.ans), std::max(L.max1 + R.max + L.sum, R.max2 - L.sum + L.max));
}

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	if (l == r) return p[u].init(l, s[l]);
	build(u << 1, l, p[u].mid);
	build(u << 1 | 1, p[u].mid + 1, r);
	maintain(u);
}

void modify(int u, int k, int w) {
	if (p[u].l == p[u].r) return p[u].init(k, w);
	modify(k <= p[u].mid ? u << 1 : u << 1 | 1, k, w);
	maintain(u);
}

void main() {
	read(n), read(m), scanf("%s", s + 1);
	build(1, 1, (n - 1) << 1);
	print(p[1].ans, '\n');
	for (int l, r, i = 1; i <= m; i++) {
		read(l), read(r), std::swap(s[l], s[r]);
		modify(1, l, s[l]);
		modify(1, r, s[r]);
		// for (int i = 1; i <= (n - 1) << 1; i++)
		// 	putchar(s[i]);
		// putchar('\n');
		print(p[1].ans, '\n');
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
} // 12312312312312312