// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.08 17:50:05
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 1e5 + 10, mod = 998244353;
int n, m, a[N], b[N], fac[N], ifac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int C(int n, int m) { return n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m])); }

void main() {
	read(n), read(m);
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= n; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	for (int i = 1; i <= n; i++) read(a[i]), b[i] = a[i];
	std::sort(b + 1, b + n + 1);
	for (int _1, _2, _3, _4, i = 1; i <= n; i++) {
		_1 = std::lower_bound(b + 1, b + n + 1, (a[i] + 1) >> 1) - b - 1;
		_2 = n - (std::lower_bound(b + 1, b + n + 1, a[i]) - b);
		_3 = n - (std::lower_bound(b + 1, b + n + 1, a[i] << 1) - b) + 1 - (a[i] == 0);
		_4 = std::lower_bound(b + 1, b + n + 1, a[i]) - b - 1;
		// printf("%d %d : %d %d %d %d\n", i, a[i], _1, _2, _3, _4);
		print(sub(C(sub(_1, _2), m), m ? C(sub(_3, _4), n - m) : 0), '\n');
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}