// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.11 15:23:57
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

const int N = 1e5 + 10, M = 20, mod = 1e9 + 7;
int n, m, ans, mrk[N], f[M][N];
std::vector <int> vet[N];

inline int find(int x, int *fa) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x], fa);
}

inline int fpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % mod)
		if (b & 1) s = (ll)s * a % mod;
	return s;
}

inline void merge(int u, int v, int k) {
	f[k][find(u, f[k])] = find(v, f[k]);
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < M; j++)
			f[j][i] = i;
	for (int i = 1, a, b, c, d, len; i <= m; i++) {
		read(a), read(b), read(c), read(d), len = b - a + 1;
		for (int i = 19, u = a, v = c; i >= 0; i--)
			if (len >= (1 << i)) {
				f[i][find(u, f[i])] = find(v, f[i]);
				u += 1 << i, v += 1 << i, len -= 1 << i;
			}
	}
	for (int k = M - 1; k >= 1; k--) {
		for (int i = 1; i <= n; i++) vet[i].clear();
		for (int i = 1; i <= n; i++)
			vet[find(i, f[k])].push_back(i);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j < vet[i].size(); j++) {
				merge(vet[i][j - 1], vet[i][j], k - 1);
				if (vet[i][j] + (1 << (k - 1)) <= n)
					merge(vet[i][j - 1] + (1 << (k - 1)), vet[i][j] + (1 << (k - 1)), k - 1);
			}
	}
	// for (int j = 0; j < M; j++)
	// 	for (int i = 1; i <= n; i++)
	// 		print(f[j][i], " \n"[i == n]);
	for (int i = 1; i <= n; i++) mrk[f[0][i]] = 1;
	for (int i = 1; i <= n; i++) ans += mrk[i];
	print(9ll * fpow(10, ans - 1) % mod, '\n');
}

} signed main() { return ringo::main(), 0; }