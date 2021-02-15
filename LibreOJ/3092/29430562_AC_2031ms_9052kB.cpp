// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.22 13:32:12
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

const int N = 110, M = 2e4 + 10;
std::vector<int> a[N];
int n, m, s, ans, f[N][M];

void main() {
	memset(f, -0x3f, sizeof(f));
	read(s), read(n), read(m);
	for (int i = 1; i <= s; i++) 
		for (int x, j = 1; j <= n; j++) {
			read(x);
			a[j].push_back(x << 1 | 1);
		}
	for (int i = 1; i <= n; i++)
		std::sort(a[i].begin(), a[i].end());
	f[0][0] = 0;
	for (int i = 1, cnt; i <= n; i++) {
		cnt = 0;
		for (int j = 0; j <= m; j++)
			f[i][j] = f[i - 1][j];
		for (std::vector<int>::iterator it = a[i].begin(); it != a[i].end(); it++) {
			++cnt;
			for (int j = 0; j + *it <= m; j++) {
				f[i][j + *it] = std::max(f[i][j + *it], f[i - 1][j] + cnt * i);
				// printf("f[%d][%d] -> f[%d][%d] : %d -> %d\n", i - 1, j, i, j + *it, f[i - 1][j], f[i][j + *it]);
			}
		}
	}
	for (int i = 0; i <= m; i++)
		ans = std::max(ans, f[n][i]);
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}