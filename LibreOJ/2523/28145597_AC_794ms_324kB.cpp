// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.06 11:34:37
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

#define gcd std::__gcd
const int N = 1e6 + 10, M = 1e4 + 10, mod = 1e9 + 7;
int n, m, p, id, cnt, ans, max_s;
int a[M], s[M], pow[N], f[2][M], g[M];

inline int find(int x) { return std::lower_bound(a + 1, a + cnt + 1, x) - a; }

void main() {
	read(n), read(m), read(p);
	for (int i = 1; i * i <= p; i++)
		if (p % i == 0) {
			a[++cnt] = i;
			if (i * i != p) a[++cnt] = p / i;
		}
	std::sort(a + 1, a + cnt + 1);
	for (int i = 1, w, id; i <= n; i++) {
		read(w), id = find(gcd(w, p));
		max_s = std::max(max_s, ++s[id]);
	}
	pow[0] = 1;
	for (int i = 1; i <= max_s; i++) pow[i] = (pow[i - 1] << 1) % mod;
	// for (int i = 1; i <= cnt; i++) print(a[i], " \n"[i == cnt]);
	// for (int i = 1; i <= cnt; i++) print(s[i], " \n"[i == cnt]);
	for (int i = 1, g = 1; i <= cnt; i++, g ^= 1) {
		for (int j = 1; j <= cnt; j++) f[g][j] = f[g ^ 1][j];
		f[g][i] = (f[g][i] + pow[s[i]] - 1) % mod;
		for (int j = 1, k; j <= cnt; j++) {
			k = find(gcd(a[i], a[j]));
			f[g][k] = (f[g][k] + (ll)f[g ^ 1][j] * (pow[s[i]] - 1)) % mod;
		}
	}
	for (int i = 1; i <= cnt; i++)
		for (int j = 1; j <= cnt; j++)
			if (a[i] % a[j] == 0) g[i] = (g[i] + f[n & 1][j]) % mod;
	for (int i = 1, w; i <= m; i++) read(w), print(g[find(gcd(w, p))], '\n');
}

} signed main() { return ringo::main(), 0; }