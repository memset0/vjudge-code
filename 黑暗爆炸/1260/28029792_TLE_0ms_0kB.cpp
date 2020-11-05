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

const int maxn = 1010, maxm = 6010;

int n, m, u, v, w, l, r;
int dis[maxn], cnt[maxn], inq[maxn], q[maxn];
int tot = 2, hed[maxn], nxt[maxm], to[maxm], val[maxm];

inline void add_edge(int u, int v, int w) {
	nxt[tot] = hed[u], to[tot] = v, val[tot] = w;
	hed[u] = tot++;
}

bool spfa(int s) {
	memset(dis, -63, sizeof(dis));
	memset(cnt, 0, sizeof(cnt));
	memset(inq, 0, sizeof(inq));
	l = r = 1, q[1] = s, dis[s] = 0, inq[s] = cnt[s] = 1;
	while (l <= r) {
		u = q[(l++) % n], inq[u] = 0;
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
			if (dis[v] < dis[u] + val[i]) {
				dis[v] = dis[u] + val[i];
				if (!inq[v]) {
					inq[v] = 1;
					q[(++r) % n] = v;
					if (++cnt[v] > n) {
						return false;
					}
				}
			}
	}
	return true;
}

int main() {
//	freopen("INPUT", "r", stdin);
	read(n), read(m);
	for (int i = n; i >= 1; i--)
		add_edge(0, i, 0);
	for (int i = 1; i <= m; i++) {
		read(u), read(v), read(w);
		add_edge(u, v, -w);
	}
	int ans = spfa(0);
	if (ans) {
		for (int i = 1; i <= n; i++)
			print(dis[i], '\n');
//		for (int i = 1; i <= n; i++)
//			print(cnt[i], '\n');
	} else {
		printf("NO SOLUTION\n");
	}
	return 0;
}
