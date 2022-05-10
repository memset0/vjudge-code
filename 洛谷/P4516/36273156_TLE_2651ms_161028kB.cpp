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

const int maxn = 100001, maxm = 101;
const int mod = 1e9 + 7;

int n, m, u, v;
int siz[maxn];
int f[maxn][maxm][2][2], t[maxm][2][2];
ll ans;

int tot = 2, hed[maxn], nxt[maxn << 1], to[maxn << 1];

void dfs(int u, int father) {
	siz[u] = 1;
	f[u][0][0][0] = f[u][1][1][0] = 1;
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (v ^ father) {
			dfs(v, u);
			siz[u] += siz[v];
//			printf("%d <= %d\n", u, v);
			for (int i = 0; i <= std::min(m, siz[u]); i++) {
				t[i][0][0] = f[u][i][0][0], f[u][i][0][0] = 0;
				t[i][0][1] = f[u][i][0][1], f[u][i][0][1] = 0;
				t[i][1][0] = f[u][i][1][0], f[u][i][1][0] = 0;
				t[i][1][1] = f[u][i][1][1], f[u][i][1][1] = 0;
			}
			for (int i = 0; i <= std::min(m, siz[u]); i++) {
				for (int j = 0; j <= siz[v] && i + j <= std::min(m, siz[u]); j++) {
					(f[u][i + j][0][0] += 1ll * t[i][0][0] * f[v][j][0][1] % mod) %= mod;
					(f[u][i + j][0][1] += (1ll * t[i][0][0] * f[v][j][1][1] % mod + 1ll * t[i][0][1] * (f[v][j][1][1] + f[v][j][0][1]) % mod) % mod) %= mod;
					(f[u][i + j][1][0] += 1ll * t[i][1][0] * (f[v][j][0][0] + f[v][j][0][1]) % mod) %= mod;
					(f[u][i + j][1][1] += (1ll * t[i][1][0] * (f[v][j][1][0] + f[v][j][1][1]) % mod + 1ll * t[i][1][1] * ((f[v][j][0][0] + f[v][j][0][1]) % mod + (f[v][j][1][0] + f[v][j][1][1]) % mod) % mod) % mod) %= mod;
				}
			}
		}
}

int main() {
//	freopen("INPUT", "r", stdin);
	
	read(n), read(m);
	for (int i = 1; i < n; i++) {
		read(u), read(v);
		nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
	}
	
	dfs(1, 0);
//	for (int i = 1; i <= n; i++) {
//		for (int j = 0; j <= m; j++)
//			printf("%d %d %d %d\n", f[i][j][0][0], f[i][j][0][1], f[i][j][1][0], f[i][j][1][1]);
//		puts("");
//	}
	ans += f[1][m][0][1];
	ans += f[1][m][1][1];
	print(ans % mod, '\n');

	return 0;
}