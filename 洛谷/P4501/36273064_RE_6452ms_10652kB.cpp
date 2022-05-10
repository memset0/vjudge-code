// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.22 17:12:24
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

const int N = 2e5 + 10;
int n, m, k, cnt, lft, rit, ans;
int a[N], c[N], d[N], s[N];
ll f[N], g[N];

inline int dis(int a, int b) { return s[b] - s[a]; }

struct edge {
	int u, v, w;
} e[N << 1];

void main() {
	read(n), read(m);
	for (int i = 1; i < n; i++) {
		read(d[i]), s[i + 1] = s[i] + d[i];
		e[++cnt] = (edge){i, i + 1, d[i]};
		e[++cnt] = (edge){i + 1, i, d[i]};
	}
	for (int i = 1; i <= m; i++) {
		read(k), ans = 0;
		cnt = (n - 1) << 1;
		for (int i = 1; i <= k; i++) {
			read(a[i]), read(c[i]);
			e[++cnt] = (edge){0, a[i], c[i]};
		}
		for (int i = 1; i <= n; i++) f[i] = 1e18;
		while (true) {
			bool flag = false;
			for (int i = 0; i <= n; i++) g[i] = f[i];
			for (int i = 1; i <= cnt; i++) {
				if (g[e[i].u] + e[i].w < f[e[i].v])
					f[e[i].v] = g[e[i].u] + e[i].w;
			}
			for (int i = 0; i <= n; i++) if (f[i] != g[i])
				flag = true, ++ans;
			// for (int i = 1; i <= n; i++) print(f[i], " \n"[i == n]);
			if (!flag) break;
		}
		print(ans, '\n');
	}
}

} signed main() { return ringo::main(), 0; }