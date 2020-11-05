// =================================
//   author: memset0
//   date: 2019.05.04 09:33:28
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
template <class T> inline void print(T *a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 1e6 + 10;
int n, m, ans;
int a[N], b[N], f[N][3][3];

void main() {
	memset(f, -0x3f, sizeof f);
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(a[i]), ++b[a[i]];
	f[0][0][0] = 0;
	for (int i = 1; i <= m; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				for (int t = 0; t < 3 && j + k + t <= b[i]; t++)
					f[i][k][t] = std::max(f[i][k][t], f[i - 1][j][k] + j + (b[i] - j - k  - t) / 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ans = std::max(ans, f[m][i][j]);
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}