// =================================
//   author: memset0
//   date: 2019.01.25 09:20:32
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

const int N = 1010;
int n, m, a[N], b[N];
double l, r, mid, c[N];

inline bool cmp(double a, double b) { return a > b; }

bool check(double x) {
	double sum = 0;
	for (int i = 1; i <= n; i++) c[i] = a[i] - b[i] * x;
	std::sort(c + 1, c + n + 1, cmp);
	for (int i = 1; i <= m; i++) sum += c[i];
	return sum >= 0;
}

void main() {
	while (read(n), read(m), n || m) {
		m = n - m;
		for (int i = 1; i <= n; i++) read(a[i]);
		for (int i = 1; i <= n; i++) read(b[i]);
		double l = 0, r = 100000, mid;
		while (r - l > 1e-6) {
			mid = (l + r) / 2;
			if (check(mid)) l = mid;
			else r = mid;
		}
		printf("%.0lf\n", mid * 100);
	}
}

} signed main() { return ringo::main(), 0; }