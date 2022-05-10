// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.08 23:03:34
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

const int N = 1e3 + 10;
int n;
ll ans, dis[N][N];

struct node {
	int x, y;
} p[N];

inline bool dmin(int a, int b, int c) { return dis[a][b] + dis[b][c] > dis[a][c]; }
inline bool dmax(int a, int b, int c) { return dis[a][b] + dis[b][c] < dis[a][c]; }

bool solve(int a, int b, int c, int d, int e, int f) {
	std::set <int> set;
	set.insert(a), set.insert(b), set.insert(c), set.insert(d), set.insert(e), set.insert(f);
	if (set.size() < 6) return 0; // 有点重复
	if (dis[a][b] != dis[a][c] || dis[d][b] != dis[d][c] || dis[d][e] != dis[d][f]) return 0;
	// printf("%d %d %d %d %d %d | %d %d %d %d\n", a, b, c, d, e, f, dmin(b, a, d), dmin(b, d, a), dmin(c, a, d), dmin(c, d, a));
	if (!dmin(b, a, d) || !dmin(b, d, a) || !dmin(c, a, d) || !dmin(c, d, a)) return 0;
	if (!dmax(a, d, e) || !dmax(a, d, f)) return 0;
	return 1;
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(p[i].x), read(p[i].y);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			dis[i][j] = dis[j][i] = (ll)(p[i].x - p[j].x) * (p[i].x - p[j].x) + (ll)(p[i].y - p[j].y) * (p[i].y - p[j].y);
	for (int a = 1; a <= n; a++)
		for (int b = 1; b <= n; b++)
			for (int c = 1; c <= n; c++)
				for (int d = 1; d <= n; d++)
					for (int e = 1; e <= n; e++)
						for (int f = 1; f <= n; f++)
							ans += solve(a, b, c, d, e, f);
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}