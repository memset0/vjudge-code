// =================================
//   author: memset0
//   date: 2019.05.05 09:33:32
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

const int N = 1e5 + 10;
int n, m, ans, a[N], b[N], min[N], max[N];

void main() {
	memset(min, -1, sizeof min);
	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		read(a[i]), b[a[i]] = 1;
		max[a[i]] = i;
		if (!~min[a[i]]) min[a[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		if (!b[i]) {
			++ans;
			// printf("(%d,%d)\n", i, i);
		}
		if (i != 1) {
			if ((min[i] > max[i - 1]) || !b[i] || !b[i - 1]) {
				++ans;
				// printf("(%d,%d)\n", i, i - 1);
			}
		}
		if (i != n) {
			if ((min[i] > max[i + 1]) || !b[i] || !b[i + 1]) {
				++ans;
				// printf("(%d,%d)\n", i, i + 1);
			}
		}
	}
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}