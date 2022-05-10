// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i, l, r) for (int i = l; i <= r; ++i)
namespace ringo {

template < class T >
il void read(T &x) {
	x = 0; rg char c = getc(); rg bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getc();
	while (isdigit(c)) x = x * 10 + c - '0', c = getc();
	if (f) x = -x;
}
template < class T >
il void print(T x) {
	if (x < 0) putc('-'), x = -x;
	if (x > 9) print(x / 10);
	putc('0' + x % 10);
}
template < class T >
il void print(T x, char c) { print(x), putc(c); }

const int N = 5e4 + 10, M = 2e5 + 10;
int n, m, l, r, u, v, w, ans;
int q[N]; bool vis[N]; ll val[M], dis[N], f[63];
int tot = 2, hed[N], nxt[M], to[M];

int bfs(int s, int e) {
	q[l = r = 1] = s;
	while (l <= r) {
		u = q[l++];
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
			if (!vis[v]) {
				vis[v] = 1;
				dis[v] = dis[u] ^ val[i];
				q[++r] = v;
			}
	}
	return dis[e];
}

void insert(int x) {
	for (int i = 62; i >= 0; i--)
		if (x & (1 << i)) {
			if (f[i]) x ^= f[i];
			else { f[i] = x; break; }
		}
}

void dfs(int u) {
	vis[u] = 1;
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (vis[v]) {
			insert(dis[v] ^ dis[u] ^ val[i]);
		} else {
			dis[v] = dis[u] ^ val[i];
			dfs(v);
		}
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		read(u), read(v), read(w);
		nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, val[tot] = w, hed[v] = tot++;
	}
	ans = bfs(1, n);
	dfs(1);
	for (int i = 62; i >= 0; i--)
		if (!(ans & (1 << i)) && f[i])
			ans ^= f[i];
	print(ans), putc('\n');
}

} int main() { return ringo::main(), 0; }