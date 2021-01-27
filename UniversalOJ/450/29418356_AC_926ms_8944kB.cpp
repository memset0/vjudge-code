// =================================
//   author: memset0
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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

const int N = 5e6 + 10, mod = 19491001;
int n, k, d, w1, w2, ans, fac[N], ifac[N];

inline int sub(int a, int b) { return (a + b) % mod; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; } 
inline int C(int n, int m) { return mul(fac[n], mul(ifac[m], ifac[n - m])); }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int dec(int a, int b) { a = (a - b) % mod; return a < 0 ? a + mod : a; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void main() {
	read(n), read(k), read(d);
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= k; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= k; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= k; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	if (d == 1) {
		print(fpow(k, n), '\n');
	} else if (d == 2) {
		for (int i = 0; i <= k; i++)
			ans = sub(ans, mul(C(k, i), fpow(dec(sub(i, i), k), n)));
		print(mul(ans, inv(fpow(2, k))), '\n');
	} else {
		w1 = fpow(7, (mod - 1) / 3), w2 = mul(w1, w1);
		for (int i = 0; i <= k; i++)
			for (int j = 0; j <= k - i; j++)
				ans = sub(ans, mul(C(k, i), mul(C(k - i, j),
					fpow(sub(i, sub(mul(j, w1), mul(dec(k, sub(i, j)), w2))), n))));
		print(mul(ans, inv(fpow(3, k))), '\n');
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}