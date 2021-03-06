// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)
#define endl ('\n')

template <typename T> inline void read(T &x) {
	x = 0; register char ch; register bool fl = 0;
	while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
	while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
	if (fl) x = -x;
}
template <typename T> inline void print(T x, char c = ' ') {
	static int buf[40];
	if (x == 0) { putc('0'); putc(c); return; }
	if (x < 0) putc('-'), x = -x;
	for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
	while (buf[0]) putc((char) buf[buf[0]--]);
	putc(c);
}

const int maxn = 100010, maxm = 200010;

int n, m, u, v, ans, tot = 2;
int f[maxn], hed[maxn], nxt[maxm], to[maxm], out[maxn], in[maxn];

int dfs(int u) {
	if (f[u]) return f[u];
	if (!out[u] && in[u]) f[u] = 1;
	for (int i = hed[u]; i; i = nxt[i])
		f[u] += dfs(to[i]);
	return f[u];
}

int main() {

	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		read(u), read(v);
		nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
		out[u]++, in[v]++;
	}
	for (int i = 1; i <= n; i++)
		if (!in[i])
			ans += dfs(i);
	print(ans, endl);

	return 0;
}
