// =================================
//   author: memset0
//   date: 2019.05.06 16:41:09
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
 
int n, m, x, a[2], b[2];
 
void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(x), ++a[x & 1];
	for (int i = 1; i <= m; i++) read(x), ++b[x & 1];
	print(std::min(a[0], b[1]) + std::min(a[1], b[0]), '\n');
}
 
} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}