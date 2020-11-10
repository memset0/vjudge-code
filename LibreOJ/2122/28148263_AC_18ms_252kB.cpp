// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.06 16:10:49
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

const int N = 100, mod = 1e9, mov[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, m, cnt, a[N][N], f[N][N], id[N][N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }

int gauss(int a[N][N], int n) {
	int ans = 1;
	// for (int i = 1; i <= n; i++)
	// 	for (int j = 1; j <= n; j++)
	// 		print(a[i][j], " \n"[j == n]);
	for (int d, j, i = 1; i <= n; i++) {
		// printf(">>> i = %d | %d\n", i, a[i][i]);
		// for (int j = i; j <= n; j++) print(a[j][i], " \n"[j == n]);
		for (j = i; j <= n; j++) if (a[j][i]) break;
		if (j > n) return 0;
		if (i != j) std::swap(a[i], a[j]), ans = dec(0, ans);
		for (int j = i + 1; j <= n; j++)
			while (a[j][i]) {
				d = a[i][i] / a[j][i];
				for (int k = i; k <= n; k++) {
					a[i][k] = dec(a[i][k], mul(a[j][k], d));
					std::swap(a[i][k], a[j][k]);
				}
				ans = dec(0, ans);
			}
	}
	for (int i = 1; i <= n; i++) ans = mul(ans, a[i][i]);
	return ans;
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c = getchar();
			while (c != '.' && c != '*') c = getchar();
			a[i][j] = c == '*'; if (!a[i][j]) id[i][j] = cnt++;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int t = 0; t < 4; t++) 
				if (!a[i][j]) {
					int x = i + mov[t][0], y = j + mov[t][1];
					if (1 <= x && x <= n && 1 <= y && y <= m && !a[x][y]) {
						++f[id[i][j]][id[i][j]], f[id[i][j]][id[x][y]] = dec(f[id[i][j]][id[x][y]], 1);
					}
				}
	print(gauss(f, cnt - 1), '\n');
}

} signed main() { return ringo::main(), 0; }
