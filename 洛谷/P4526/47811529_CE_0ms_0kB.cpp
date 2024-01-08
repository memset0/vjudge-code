// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.09 19:30:43
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

double a;
inline double f(double x) { return pow(x, a / x - x); }
inline double simpson(double l, double r) { return (f(l) + 4 * f((l + r) / 2) + f(r)) * (r - l) / 6; }
inline double asr(double l, double r, double eps, double ans) {
	double mid = (l + r) / 2, L = simpson(l, mid), R = simpson(mid, r);
	if (fabs(L + R - ans) < 15 * eps) return L + R + (L + R - ans) / 15;
	return asr(l, mid, eps / 2, L) + asr(mid, r, eps / 2, R);
}

void main() {0
	const double eps = 1e-7;
	scanf("%lf", &a); if (a < 0) { puts("orz"); return; }
	printf("%.5lf\n", asr(eps, 20, eps, simpson(eps, 20)));
}

} signed main() { return ringo::main(), 0; }