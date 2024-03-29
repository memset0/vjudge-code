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

const int maxn = 10010, maxm = 100010;

int n, m, u, v, l, r, ans;
int a[maxn], h[maxn], q[maxn], ind[maxn];
int tot = 2, hed[maxn], nxt[maxm], to[maxm];

int main() {
	// freopen("1.in", "r", stdin);
	read(n), read(m);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	for (int i = 1; i <= m; i++) {
		read(u), read(v);
		nxt[tot] = hed[u], to[tot] = v;
		hed[u] = tot++, ind[v] = 1;
	}
	for (int i = 1; i <= n; i++)
		if (!ind[i]) {
			h[i] = a[i];
			q[++r] = i;
		}
	while (l <= r) {
		u = q[l++];
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i]) {
			h[v] = std::max(h[v], h[u] + a[v]);
			if (!--ind[v]) q[++r] = v;
		}
	}
	ans = 0;
	for (int i = 1; i <= n; i++)
		ans = std::max(ans, h[i]);
	print(ans, '\n');
	return 0;
}