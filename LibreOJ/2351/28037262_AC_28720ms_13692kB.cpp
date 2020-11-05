// =================================
//   author: memset0
//   date: 2019.03.21 20:51:40
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

const int N = 1e6 + 1e5 + 10, M = 25;
int n, l, m, b0, b1, bx, c0, c1, cx, c_min, ans;
int a[N], b[N], f[N], g[N], a0[M], a1[M], ax[M];
char s[N];

inline void func_or(int &a, int &b) { b = a + b; }
inline void func_and(int &a, int &b) { a = a + b; }

void fwt(int *a, int *f, int lim, void func(int &a, int &b)) {
	for (int i = 0; i < lim; i++) f[i] = a[i];
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++)
				func(f[i + j], f[i + j + len]);
}

void main() {
	read(l), read(m), n = 1 << l, scanf("%s", s);
	for (int x = 0, y; y = 0, x < n; x++) {
		for (int i = 1; i <= l; i++)
			if ((x >> (i - 1)) & 1)
				y |= 1 << (l - i);
		a[x] = s[y] - '0';
	}
	fwt(a, f, n, func_or), fwt(a, g, n, func_and);
	// for (int i = 0; i < n; i++) print(a[i], " \n"[i == n - 1]);
	// for (int i = 0; i < n; i++) print(f[i], " \n"[i == n - 1]);
	// for (int i = 0; i < n; i++) print(g[i], " \n"[i == n - 1]);
	for (int i = 1; i <= m; i++) {
		scanf("%s", s + 1);
		c0 = c1 = cx = b0 = b1 = bx = 0;
		for (int i = 1; i <= l; i++)
			if (s[i] == '1') {
				a1[c1++] = i - 1;
				b1 |= 1 << (i - 1);
			} else if (s[i] == '0') {
				a0[c0++] = i - 1;
				b0 |= 1 << (i - 1);
			} else {
				ax[cx++] = i - 1;
				bx |= 1 << (i - 1);
			}
		c_min = std::min(cx, std::min(c0, c1));
		ans = 0;
		if (c1 == c_min) {
			int tmp = __builtin_popcount(b1 | bx) & 1 ^ 1;
			for (int x = 0, y; x < (1 << c1); x++) {
				y = b1 | bx;
				for (int i = 0; i < c1; i++)
					if ((x >> i) & 1)
						y ^= 1 << a1[i];
				ans += f[y] * (__builtin_popcount(y) & 1 ^ tmp ? 1 : -1);
				// printf("> %d : ", y);
				// for (int i = 1; i <= l; i++) print((y >> (i - 1)) & 1, " \n"[i == l]);
			}
		} else if (c0 == c_min) {
			for (int x = 0, y; x < (1 << c0); x++) {
				y = b1;
				for (int i = 0; i < c0; i++)
					if ((x >> i) & 1)
						y |= 1 << a0[i];
				ans += g[y] * (__builtin_popcount(x) & 1 ? -1 : 1);
				// printf("> %d : %d : %d * %d : ", y, ans, f[y], __builtin_popcount(x) & 1 ? -1 : 1);
				// for (int i = 1; i <= l; i++) print((y >> (i - 1)) & 1, " \n"[i == l]);
			}
		} else if (cx == c_min) {
			for (int x = 0, y; x < (1 << cx); x++) {
				y = b1;
				for (int i = 0; i < cx; i++)
					if ((x >> i) & 1)
						y |= 1 << ax[i];
				ans += a[y];
				// printf("> %d : ", y);
				// for (int i = 1; i <= l; i++) print((y >> (i - 1)) & 1, " \n"[i == l]);
			}
		}
		print(ans, '\n');
	}
}

} signed main() { return ringo::main(), 0; }
