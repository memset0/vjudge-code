// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

template <typename T> inline void read(T &x) {
	x = 0; register char ch; register bool fl = 0;
	while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
	while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
	if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
	while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
	static int buf[40];
	if (x == 0) { putc('0'); putc(c); return; }
	if (x < 0) putc('-'), x = -x;
	for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
	while (buf[0]) putc((char) buf[buf[0]--]);
	putc(c);
}

const int maxn = 110, maxm = 15;
int n, m, x, ans;
int a[maxn][maxm], swp[2][1 << 10], g[maxn], f[maxn][1 << 10][1 << 10];

int change(int x) {
	int s = 0;
	while (x) {
		s = s * 10 + (x & 1);
		x >>= 1;
	}
	return s;
}

int main() {
//	freopen("INPUT", "r", stdin);
	read(n), read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			readc(x);
			a[i][j] = x == 'P' ? 1 : 0;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			g[i] |= a[i][j] << (j - 1);
//	for (int i = 1; i <= n; i++)
//		printf("%d\n", change(g[i]));
	f[0][0][0] = 0;
	for (int i = 1; i <= n; i++) {
//		printf("=== %d ===\n", i);
		for (int x = 0; x < 1 << m; x++)
			if ((!((x & (x >> 1)) || (x & (x >> 2)))) && ((x | g[i])== g[i])) {
//				printf("> %d %d %d %d\n", change(x), change(g[i]), change(x & g[i]), change(x | g[i]));
				for (int y = 0; y < 1 << m; y++)
					if (!(x & y) && ((y | g[i - 1]) == g[i - 1]))
						for (int z = 0; z < 1 << m; z++)
							if (!((x & z) || (y & z)) && ((z | g[i - 2]) == g[i - 2])) {
//								printf("(%d,%04d,%04d) => (%d,%04d,%04d)\n", i - 1, change(y), change(z), i, change(x), change(y));
								f[i][x][y] = std::max(f[i][x][y], f[i - 1][y][z] + __builtin_popcount(x));
							}
			}
	}
	for (int x = 0; x < 1 << m; x++)
		for (int y = 0; y < 1 << m; y++)
			ans = std::max(ans, f[n][x][y]);
//	for (int i = 1; i <= n; i++) {
//		int tmp = 0;
//		for (int x = 0; x < 1 << m; x++)
//			for (int y = 0; y < 1 << m; y++)
//				tmp = std::max(tmp, f[i][x][y]);
//		print(tmp, '\n');
//	}
	print(ans, '\n');
	return 0;
}
