// =================================
//   author: memset0
//   date: 2019.03.20 22:54:35
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

const int N = 1e5 + 10;
int n, m, k, ans, a[N], f[N];

void main() {
	memset(f, 0x3f, sizeof(f));
	read(n), read(m), read(k);
	for (int i = 1; i <= n; i++) read(a[i]);
	f[0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < i; j++) {
			// printf("[%d] -> [%d] : %d %d %d\n", j, i, f[j], a[i] - a[j], std::max((a[i] - a[j]) << 1, k));
			f[i] = std::min(f[i], f[j] + a[i] - a[j] + std::max((a[i] - a[j + 1]) << 1, k));
		}
	// for (int i = 1; i <= n; i++) print(f[i], " \n"[i == n]);
	ans = f[n] + m - a[n];
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }