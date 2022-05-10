// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.20 14:31:35
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

int n, L, G, x, y;

void main() {
	read(n), read(L), read(G);
	for (int i = 1; i <= n; i++) {
		read(x), read(y);
		while (x > G || y > G)
			x >>= 1, y >>= 1;
		if (x < L || y < L) {
			puts("Too Young");
		} else if (x != y) {
			puts("Too Simple");
		} else {
			puts("Sometimes Naive");
		}
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}