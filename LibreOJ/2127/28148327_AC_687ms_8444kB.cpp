// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.14 08:44:30
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

const int N = 25, M = 1 << 20;
int n, lim;
double ans, a[M];

void fwt(double *a) {
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				double x = a[i + j], y = a[i + j + len];
				a[i + j + len] = x + y;
			}
}

void main() {
	read(n), lim = 1 << n;
	for (int i = 0; i < lim; i++) scanf("%lf", &a[i]);
	for (int i = lim - 1, t = 0; t != (lim - 1); i--) {
		if (i == -1) return (void)(puts("INF"));
		if (a[i] > 0) t |= i;
	}
	fwt(a);
	// for (int i = 0; i < lim; i++)
	// 	printf("%d : %.6lf\n", (__builtin_popcount(i) & 1 ? 1 : -1), 1 / (1 - a[(lim - 1) ^ i]));
	for (int i = 1; i < lim; i++)
		ans += (__builtin_popcount(i) & 1 ? 1 : -1) / (1 - a[(lim - 1) ^ i]);
	printf("%.9lf\n", ans);
}

} signed main() { return ringo::main(), 0; }
