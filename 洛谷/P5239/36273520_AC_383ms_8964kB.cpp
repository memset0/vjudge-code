// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.02 11:01:28
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

const int N = 1e3 + 10, mod = 19260817;
int n, m, q, c[N][N], s[N][N], fac[N], inv[N];

inline int dec(int x, int y) { x -= y; return x < 0 ? x + mod : x; }
inline int sub(int x, int y) { x += y; return x >= mod ? x - mod : x; }

void main() {
	read(q), fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i < N; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	for (int i = 2; i < N; i++) inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
	for (int i = 2; i < N; i++) inv[i] = (ll)inv[i - 1] * inv[i] % mod;
	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++) {
			if (i > j) c[i][j] = 0;
			else c[i][j] = (ll)fac[j] * inv[i] % mod * inv[j - i] % mod;
		}
	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++) {
			s[i][j] = c[i][j];
			if (i) s[i][j] = sub(s[i][j], s[i - 1][j]);
			if (j) s[i][j] = sub(s[i][j], s[i][j - 1]);
			if (i && j) s[i][j] = dec(s[i][j], s[i - 1][j - 1]);
		}
	// for (int i = 0; i <= 10; i++)
	// 	for (int j = 0; j <= 10; j++)
	// 		print(c[i][j], " \n"[j == 10]);
	// for (int i = 0; i <= 10; i++)
	// 	for (int j = 0; j <= 10; j++)
	// 		print(s[i][j], " \n"[j == 10]);
	for (int i = 1; i <= q; i++) {
		read(n), read(m);
		print(s[n][m], '\n');
	}
}

} signed main() { return ringo::main(), 0; }