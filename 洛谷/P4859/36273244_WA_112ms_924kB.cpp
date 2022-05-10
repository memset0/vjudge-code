// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.16 22:16:34
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

const int N = 2e3 + 10, mod = 1e9 + 9;
int n, m, ans;
int a[N], b[N], l[N], inv[N], fac[N], f[2][N];

inline int C(int n, int m) { return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod; }

void main() {
	read(n), read(m);
	if ((n + m) & 1) return (void)(puts("0"));
	m = (n + m) >> 1, fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	for (int i = 2; i <= n; i++) inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
	for (int i = 2; i <= n; i++) inv[i] = (ll)inv[i - 1] * inv[i] % mod;
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1; i <= n; i++) read(b[i]);
	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
		l[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b - 1;
	// for (int i = 1; i <= n; i++) print(a[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(b[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(l[i], " \n"[i == n]);
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) f[i & 1][j] = f[i & 1 ^ 1][j];
		for (int j = 0; j < n; j++)
			f[i & 1][j + 1] = (f[i & 1][j + 1] + (ll)std::max(l[i] - j, 0) * f[i & 1 ^ 1][j]) % mod;
	}
	for (int i = m; i <= n; i++)
		ans = (ans + (ll)((i - m) & 1 ? mod - 1 : 1) * C(i, m) % mod * f[n & 1][i]) % mod;
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }