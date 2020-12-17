// =================================
//   author: memset0
//   date: 2019.07.01 20:07:42
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

const int N = 410, mod = 998244353;
int n, m, w[N], f[N][N], p[N][N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(w[i]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			p[i][j] = std::max(0, std::min(i, j + m - 1) - std::max(m, j) + 1);
	for (int i = 0; i < m; i++)
		for (int j = 1; j <= n; j++)
			f[i][j] = fpow(j, i);
	f[0][0] = 1;
	for (int i = m; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			f[i][j] = f[i][j - 1];
			// printf(">> %d %d %d\n", i, j, f[i][j]);
			for (int k = 1; k <= i; k++) {
				// printf(">> %d %d %d : %d %d %d\n", i, j, k, fpow(w[j], p[i][k]), f[k - 1][j - 1], f[i - k][j]);
				f[i][j] = inc(f[i][j], mul(fpow(w[j], p[i][k]), mul(f[k - 1][j - 1], f[i - k][j])));
			}
		}
	// for (int i = 1; i <= n; i++)
	// 	for (int j = 1; j <= n; j++)
	// 		print(p[i][j], " \n"[j == n]);
	// for (int i = 1; i <= n; i++)
	// 	for (int j = 1; j <= n; j++)
	// 		print(f[i][j], " \n"[j == n]);
	print(f[n][n], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}