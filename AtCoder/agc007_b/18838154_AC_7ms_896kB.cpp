// =================================
//   author: memset0
//   date: 2019.03.21 00:07:31
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

const int N = 2e4 + 10;
int n, a[N], b[N], p[N];

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(p[i]);
	for (int i = 1; i <= n; i++) a[i] = n * i + 1;
	for (int i = 1; i <= n; i++) b[i] = n * (n - i + 1) + 1;
	for (int i = 1; i <= n; i++) a[p[i]] += i, b[p[i]] += i;
	for (int i = 1; i <= n; i++) print(a[i], " \n"[i == n]);
	for (int i = 1; i <= n; i++) print(b[i], " \n"[i == n]);
}

} signed main() { return ringo::main(), 0; }