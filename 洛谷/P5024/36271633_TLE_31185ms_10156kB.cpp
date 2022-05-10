#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i,l,r) for (register int i = l; i <= r; ++i)
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
	putc(x % 10 + '0');
}

const int maxn = 100010;
const ll inf = 1e18;
int n, m, u, v, a, b, x, y, type1, type2;
int fa[maxn], tag[maxn], cst[maxn];
ll ans, f[maxn][2];
int tot = 2, hed[maxn], to[maxn << 1], nxt[maxn << 1];

void dfs(int u) {
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
		}
}

void dp(int u) {
	f[u][1] = cst[u], f[u][0] = 0;
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (v != fa[u]) {
			dp(v);
			f[u][0] += f[v][1];
			f[u][1] += std::min(f[v][0], f[v][1]);
		}
	if (~tag[u])
		 f[u][tag[u] ^ 1] = inf;
}

void main() {
	memset(tag, -1, sizeof(tag));
	read(n), read(m), type1 = getc(), type2 = getc();
//	printf("%c%c\n", type1, type2);
	for (int i = 1; i <= n; i++)
		read(cst[i]);
	for (int i = 1; i < n; i++) {
		read(u), read(v);
		nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
	}
	dfs(1);
	for (int i = 1; i <= m; i++) {
		read(a), read(x), read(b), read(y);
		tag[a] = x, tag[b] = y;
		dp(1);
		tag[a] = tag[b] = -1;
		ans = std::min(f[1][0], f[1][1]);
		if (ans >= inf) ans = -1;
		print(ans), putc('\n');
//		for (int i = 1; i <= n; i++) print(f[i][0] >= inf ? -1 : f[i][0]), putc(' '); putc('\n');
//		for (int i = 1; i <= n; i++) print(f[i][1] >= inf ? -1 : f[i][1]), putc(' '); putc('\n');
	}
}
	
} int main() { ringo::main(); return 0; }
