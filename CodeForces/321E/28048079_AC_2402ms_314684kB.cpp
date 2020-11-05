// =================================
//   author: memset0
//   date: 2019.04.18 08:35:30
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

const int N = 4e3 + 10;
int n, m, t[N][N], a[N][N], s[N][N], f[N][N], w[N][N];

void main() {
	memset(f, 0x3f, sizeof f);
	read(n), read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			read(a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			t[i][j] = t[i][j - 1] + a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			s[i][j] = s[i][j - 1] + t[j][j] - t[j][i - 1];
	f[0][0] = w[0][0] = 0;
	for (int i = 1; i <= m; i++) {
		w[i][n + 1] = n - 1;
		for (int j = n; j >= 1; j--) {
			for (int k = w[i - 1][j]; k <= w[i][j + 1]; k++)
				if (f[i - 1][k] + s[k + 1][j] < f[i][j]) {
					f[i][j] = f[i - 1][k] + s[k + 1][j];
					w[i][j] = k;
				}
		}
	}
	// for (int i = 1; i <= m; i++)
	// 	for (int j = 1; j <= n; j++)
	// 		print(f[i][j], " \n"[j == n]);
	// for (int i = 1; i <= m; i++)
	// 	for (int j = 1; j <= n; j++)
	// 		print(w[i][j], " \n"[j == n]);
	print(f[m][n], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("ferris3.in", "r", stdin);
	// freopen("ferris1.out", "w", stdout);
#else
	// freopen("ferris.in", "r", stdin);
	// freopen("ferris.out", "w", stdout);
#endif
	return ringo::main(), 0;
}