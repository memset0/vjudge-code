// =================================
//   author: memset0
//   date: 2019.06.24 14:31:07
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

const int N = 15;
ll tmp;
long double ans;
int n, T, A, B, a[N];

inline long double get(int x) {
	if (x < 0) return 0;
	long double res = 1;
	for (int i = 1; i <= n; i++)
		res *= x / (long double)i;
	return res;
}

void main() {
	for (read(T); T--; ) {
		tmp = 1, ans = 0;
		read(n), read(A), read(B);
		for (int i = 1; i <= n; i++) {
			read(a[i]);
			A += a[i], B += a[i], a[i] <<= 1, tmp *= a[i];
		}
		for (int S = 0; S < (1 << n); S++) {
			int sum = 0, cnt = 0;
			for (int i = 1; i <= n; i++)
				if ((S >> (i - 1)) & 1)
					sum += a[i], ++cnt;
			// printf(">> %d >> %d >> %.2lf %.2lf\n", S, sum, get(B - sum), get(A - sum));
			ans += (cnt & 1 ? -1 : 1) * (get(B - sum) - get(A - sum));
		}
		printf("%.9Lf\n", ans / tmp);
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	return ringo::main(), 0;
}
