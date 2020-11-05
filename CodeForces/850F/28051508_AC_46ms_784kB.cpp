// =================================
//   author: memset0
//   date: 2019.04.19 19:05:22
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

const int N = 1e5 + 10, mod = 1e9 + 7;
int n, s, max, ans, a[N], f[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }

void main() {
	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		s = inc(s, a[i]);
		max = std::max(max, a[i]); 
	}
	f[0] = 0, f[1] = mul(mul(dec(s, 1), dec(s, 1)), inv(s));
	for (int i = 1; i < max; i++) {
		f[i + 1] = dec(dec(inc(f[i], f[i]), f[i - 1]), mul(dec(s, 1), inv(dec(s, i))));
	}
	for (int i = 1; i <= n; i++) {
		ans = inc(ans, f[a[i]]);
	}
	// for (int i = 0; i <= max; i++) print(f[i], " \n"[i == max]);
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}