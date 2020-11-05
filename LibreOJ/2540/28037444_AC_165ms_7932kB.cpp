// =================================
//   author: memset0
//   date: 2019.01.09 21:32:39
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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

const int N = 21, mod = 998244353;
int n, m, ans, base;
int map[N], f[N][1 << 20], A[N][N];
bool tag[N];
std::vector <int> G[N];
std::vector <std::pair <int, int> > E;

int inv(int x) { return !x || x == 1 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) map[i] = 1 << (i - 1);
	for (int i = 1, u, v; i <= m; i++) {
		read(u), read(v), G[u].push_back(v), G[v].push_back(u);
		map[u] |= 1 << (v - 1), map[v] |= 1 << (u - 1);
		E.push_back(std::make_pair(u, v));
	}
	for (int x = 0, flag; x < (1 << n); x++) {
		flag = 1;
		for (int i = 1; i <= n; i++) tag[i] = x & (1 << (i - 1));
		for (int i = 0; i < m && flag; i++) flag &= !(tag[E[i].first] && tag[E[i].second]);
		if (flag) base = std::max(base, __builtin_popcount(x));
	}
	for (int i = 0; i <= n; i++) {
		A[i][0] = 1;
		for (int j = 1; j <= i; j++)
			A[i][j] = (ll)A[i][j - 1] * (i - j + 1) % mod;
	}
	// for (int i = 1; i <= n; i++)
	// 	for (int j = 1; j <= i; j++)
	// 		print(A[i][j], " \n"[j == i]);
	f[0][0] = 1;
	for (int i = 0; i < base; i++)
		for (int x = 0, y, last, delta; x < (1 << n); x++)
			if (f[i][x]) {
				for (int j = 1; j <= n; j++)
					if (!(x & (1 << (j - 1)))) {
						y = x | map[j];
						last = n - __builtin_popcount(x) - 1;
						delta = __builtin_popcount(y) - __builtin_popcount(x) - 1;
						// printf("f[%d][%d] => f[%d][%d] : %d %d : %d %d %d\n", i, x, i + 1, y, j, map[j], last, delta, A[last][delta]);
						f[i + 1][y] = (f[i + 1][y] + (ll)f[i][x] * A[last][delta]) % mod;
					}
			}
	// std::cout << base << std::endl;
	// for (int i = 1; i <= base; i++) print(f[i][(1 << n) - 1], " \n"[i == base]);
	print((ll)f[base][(1 << n) - 1] * inv(A[n][n]) % mod, '\n');
}

} signed main() { return ringo::main(), 0; }
