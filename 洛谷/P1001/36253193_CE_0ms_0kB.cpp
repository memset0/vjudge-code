// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.08.18 22:06:20
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define for_each(i, a) for (size_t i = 0, i##ed = a.size(); i < i##ed; ++i)
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
template <class T> inline void print(T a, int l, int r) { for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]); }

const int N = 60;
int n, m, res[N][N];

bool ask(int a, int b, int c, int d) {
	printf("? %d %d %d %d\n", a, b, c, d);
	int x; read(x); return x;
}

void dfs(int x, int y, int sx, int sy) {
	if (x < 1 || y < 1 || x > n || y > n) return;
	if (vis[x][y]) return;
	res[x][y] = res[sx][sy] ^ ask(std::min(sx, x), std::min(sy, y), std::max(sx, x), std::max(sy, y)) ^ 1;
	dfs(x - 2, y, x, y);
	dfs(x + 2, y, x, y);
	dfs(x, y - 2, x, y);
	dfs(x, y + 2, x, y);
}

void main() {
	read(n);
	for (int i = 3; i <= n; i++) {
		res[i][1] = res[i - 2][1] ^ ask(i - 2, 1, i, 1) ^ 1;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 3; j <= n; j++) {
			res[i][j] = res[i][j - 2] ^ ask(i, j, i, j - 2) ^ 1;
		}
	for (int i = 1; i <= n && !flag; i++)
		for (int j = 5; j <= n && !flag; j++) {
			if ((i + j) & 1 ^ 1) flag |= check(i, j - 4, i, j - 2, i, j);
		}
	for (int i = 5; i <= n && !flag; i++)
		for (int j = 1; j <= n && !flag; j++) {
			if ((i + j) & 1 ^ 1) flag |= check(i - 4, j, i - 2, j, i, j);
		}
	dfs(sx - 2, sy, sx, sy);
	dfs(sx + 2, sy, sx, sy);
	dfs(sx, sy - 2, sx, sy);
	dfs(sx, sy + 2, sx, sy);
	for (int i = 1; i <= n; i++) print(res[i], 1, n);
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);Â
	// freopen("1.out", "w", stdout);
#endif
	ringo::main();
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
}