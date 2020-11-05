// =================================
//   author: memset0
//   date: 2019.03.06 19:02:37
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

const int N = 20, mod = 1e9 + 7;
int n, det, ans, m[N], a[N][N];
struct edge { int u, v; }; std::vector <edge> e[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }

void main() {
	read(n), --n;
	for (int i = 1; i <= n; i++) {
		read(m[i]), e[i].resize(m[i] + 1);
		for (int j = 1; j <= m[i]; j++)
			read(e[i][j].u), read(e[i][j].v);
	}
	for (int x = 0; x < (1 << n); x++) {
		// printf(">>> %d\n", x);
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n; i++)
			if ((x >> (i - 1)) & 1) {
				for (int j = 1, u, v; j <= m[i]; j++) {
					u = e[i][j].u, v = e[i][j].v;
					// printf("[%d %d]\n", u, v);
					++a[u][u], ++a[v][v], ++a[u][v], ++a[v][u];
				}
			}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i != j) a[i][j] = dec(0, a[i][j]);
		// for (int i = 1; i <= n; i++)
		// 	for (int j = 1; j <= n; j++)
		// 		print(a[i][j], " \n"[j == n]);
		det = 1;
		for (int i = 1, d, j; i <= n; i++) {
			for (j = i; j <= n; j++) if (a[j][i]) break;
			if (j > n) { det = 0; break; }
			if (i != j) std::swap(a[i], a[j]), det = dec(0, det);
			for (int j = i + 1; j <= n; j++) {
				d = mul(a[j][i], inv(a[i][i]));
				for (int k = i; k <= n; k++)
					a[j][k] = dec(a[j][k], mul(d, a[i][k]));
			}
			det = mul(det, a[i][i]);
		}
		ans = ((n - __builtin_popcount(x)) & 1) ? dec(ans, det) : inc(ans, det);
	} print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }
