// luogu-judger-enable-o2
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

using std::vector;

const int maxn = 22;
const int mod = 998244353;

int n, m, x, u;
int v[1 << 20];
int f[1 << 20], c[1 << 20];
vector < int > g[1 << 20];

int main() {

	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		u = 0; char c;
		while (c = getc(), !isdigit(c));
		while (isdigit(c)) u = u << 1 | (c - '0'), c = getc();
		read(x);
		v[u] = x;
		// printf("%d %d\n", u, x);
	}
	c[0] = 1, f[0] = v[0];
	for (int x = 0; x < (1 << n); x++) {
		// printf("%d : %d %d\n", x, f[x], c[x]);
		for (int y = x; y < (1 << n); y++)
			if ((x | y) == y && x != y) {
				// printf("%d -> %d\n", x, y);
				c[y] += c[x];
				f[y] = (f[y] + f[x] + 1ll * c[x] * v[y]) % mod;
			}
	}
	print(f[(1 << n) - 1], '\n');

	return 0;
}