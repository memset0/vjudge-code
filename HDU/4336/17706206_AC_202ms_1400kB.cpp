// =================================
//   author: memset0
//   date: 2019.01.14 07:43:43
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

const int N = 25;
int n;
double ans, sum, p[N];

void main() {
	while (~scanf("%d", &n)) {
		ans = 0;
		for (int i = 1; i <= n; i++) scanf("%lf", &p[i]);
		for (int x = 1; x < (1 << n); x++) {
			sum = 0;
			for (int i = 1; i <= n; i++)
				if (x & (1 << (i - 1)))
					sum += p[i];
			ans += (__builtin_popcount(x) & 1 ? 1 : -1) / sum;
		}
		printf("%.6lf\n", ans);
	}
}

} signed main() { return ringo::main(), 0; }