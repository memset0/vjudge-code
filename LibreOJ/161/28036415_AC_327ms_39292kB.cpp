// =================================
//   author: memset0
//   date: 2019.03.27 21:37:29
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

const int N = 5e6 + 10, mod = 1e9 + 7;
int n, sum, ans, tmp, a[N], s[N];

inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }

void main() {
	read(n), s[0] = tmp = 1;
	for (int i = 1; i <= n; i++) read(a[i]), s[i] = mul(s[i - 1], a[i]);
	sum = inv(s[n]);
	for (int i = n; i >= 1; i--) {
		// print(mul(sum, s[i - 1]), " \n"[i == 1]);
		ans = sub(ans, mul(tmp, mul(sum, s[i - 1])));
		sum = mul(sum, a[i]), tmp = mul(tmp, 998244353);
	}
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }
