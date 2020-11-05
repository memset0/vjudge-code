// =================================
//   author: memset0
//   date: 2018.12.26 13:46:49
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define rep(i, l, r) for (register int i = l; i <= r; i++)
namespace ringo {
typedef long long ll;
typedef unsigned long long ull;
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
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 2e5 + 10, p = 998244353;
int n, m, ans;
int v[N], pow[N], f[N][2][2][2];

template <class T> inline void sumd(int &a, const T &b) { a = (a + b) % p; }

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(v[i]);
	pow[0] = 1;
	for (int i = 1; i <= n; i++) pow[i] = (ll)pow[i - 1] * 2 % p;
	f[0][0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int a = 0; a < 2; a++) {
			if (v[i] == 0 && a == 1) continue;
			if (v[i] == 1 && a == 0) continue;
			for (int b = 0; b < 2; b++)
				for (int c = 0; c < 2; c++)
					for (int d = 0; d < 2; d++) {
						int from = f[i - 1][b][c][d];
						if (a == 0) {
							if (d) sumd(f[i][b][c][d], (ll)pow[d ? i - 2 : i - 1] * from);
							sumd(f[i][b ^ 1][1][d], (ll)pow[d ? i - 2 : i - 1] * from);
						} else {
							if (c) sumd(f[i][b][c][d], (ll)pow[c ? i - 2 : i - 1] * from);
							sumd(f[i][b ^ 1][c][1], (ll)pow[c ? i - 2 : i - 1] * from);
						}
					}
		}
	}
	ans = 0;
	// for (int i = 1; i <= n; i++) {
	// 	for (int b = 0; b < 2; b++)
	// 		for (int c = 0; c < 2; c++)
	// 			for (int d = 0; d < 2; d++)
	// 				printf("[%d %d %d] => %d ", b, c, d, f[i][b][c][d]);
	// 	puts("");
	// }
	for (int c = 0; c < 2; c++)
		for (int d = 0; d < 2; d++)
			sumd(ans, f[n][m][c][d]);
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }
