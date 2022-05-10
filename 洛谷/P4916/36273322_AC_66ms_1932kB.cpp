// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.14 12:34:53
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

const int N = 1e5 + 10, mod = 998244353;
int n, m, k, ans, f[N], fac[N << 1], ifac[N << 1];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }
inline int C(int n, int m) { return n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m])); }

inline int calc(int n, int m) {
	int ans = 0, sum = 0;
	for (int i = 0, j; j = m - (k + 1) * i, j >= 0; i++)
		sum = sub(sum, mul(i & 1 ? mod - 1 : 1, mul(C(n - m - 1, i), C(n - m + j, j))));
	ans = sub(ans, sum), sum = 0;
	for (int i = 0, j; j = m - k - 1 - (k + 1) * i, j >= 0; i++)
		sum = sub(sum, mul(i & 1 ? mod - 1 : 1, mul(C(n - m - 1, i), C(n - m + j, j))));
	ans = dec(ans, mul(sum, k + 2)), sum = 0;
	for (int i = 0, j; j = m - k - 2 - (k + 1) * i, j >= 0; i++)
		sum = sub(sum, mul(i & 1 ? mod - 1 : 1, mul(C(n - m - 1, i), C(n - m + j, j))));
	return sub(ans, mul(sum, k + 1));
}

void main() {
	read(n), read(m), read(k);
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= (n << 1); i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= (n << 1); i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= (n << 1); i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	for (int l = 1; l <= n; l++)
		if (n % l == 0 && m % l == 0)
			f[l] = calc(n / l, m / l);
	for (int i = 1; i <= n; i++) ans = sub(ans, f[n / std::__gcd(n, i)]);
	print(mul(ans, inv(n)), '\n');
}

} signed main() { return ringo::main(), 0; }