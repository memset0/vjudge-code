// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.10 20:02:23
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

const int N = 3e3 + 10, mod = 998244353;
int T, n, m, k, ans;
int a[N], b[N], f[N][N], g[N][N], C[N][N];

inline bool cmp(int a, int b) { return a > b; }

inline int get_f(int x, int y) {
	if (!y) return C[n][x];
	int ans = 0;
	for (int i = y; i <= n; i++)
		ans = (ans + (ll)C[n - i][x - y] * f[i - 1][y - 1] % mod * a[i]) % mod;
	// printf("get_f %d %d => %d\n", x, y, ans);
	return ans;
}

inline int get_g(int x, int y) {
	if (!y) return 0;
	int ans = 0;
	for (int i = y; i <= n; i++)
		ans = (ans + (ll)C[n - i][x - y] * (g[i - 1][y - 1] + (ll)b[i] * C[i - 1][y - 1] % mod)) % mod;
	// printf("get_g %d %d => %d\n", sx, y, ans);
	return ans;
}

void main() {
	for (register int i = 0; i <= 3000; i++) {
		C[i][0] = 1;
		for (register int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	f[0][0] = 1, g[0][0] = 0;
	for (read(T); T--; ) {
		read(n), read(m), read(k), ans = 0;
		for (register int i = 1; i <= n; i++) read(a[i]);
		for (register int i = 1; i <= n; i++) read(b[i]);
		std::sort(a + 1, a + n + 1, cmp);
		std::sort(b + 1, b + n + 1, cmp);
		for (register int i = 1; i <= n; i++) {
			f[i][0] = f[i - 1][0], g[i][0] = g[i - 1][0];
			for (register int j = 1; j <= i; j++) {
				f[i][j] = (f[i - 1][j] + (ll)f[i - 1][j - 1] * a[i]) % mod;
				g[i][j] = (g[i - 1][j] + g[i - 1][j - 1] + (ll)C[i - 1][j - 1] * b[i]) % mod;
			}
		}
		for (register int i = std::max(0, m - n); i <= n && i <= m; i++) { 
			if (i < k) ans = (ans + (ll)get_f(i, i) * get_g(m - i, k - i)) % mod;
			else ans = (ans + (ll)get_f(i, k - 1) * get_g(m - i, 1)) % mod;
		}
		print(ans, '\n');
	}
}

} signed main() { return ringo::main(), 0; }