// =================================
//   author: memset0
//   date: 2019.03.07 20:49:01
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#define debug(...) fprintf(stderr,__VA_ARGS__)
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

const unsigned int N = 4e5 + 10, K = 12;
unsigned int n, m, rt, nod, ch[N][2], rnd[N];
unsigned int a[N], siz[N], val[N], C[K][K], ans[N][K], pow[N][K];
std::vector <unsigned int> vet[N];

inline void update(unsigned int u) {
	siz[u] = siz[ch[u][0]] + 1 + siz[ch[u][1]];
	for (unsigned int k = 0; k <= 10; k++) {
		ans[u][k] = ans[ch[u][0]][k] + val[u] * pow[siz[ch[u][0]] + 1][k];
		for (unsigned int i = 0; i <= k; i++) ans[u][k] += C[k][i] * pow[siz[ch[u][0]] + 1][k - i] * ans[ch[u][1]][i];
	}
}

inline unsigned int newnode(unsigned int v) {
	val[++nod] = v, rnd[nod] = rand(), update(nod);
	return nod;
}

unsigned int merge(unsigned int x, unsigned int y) {
	if (!x || !y) return x | y;
	if (rnd[x] < rnd[y]) { ch[y][0] = merge(x, ch[y][0]), update(y); return y; }
	else { ch[x][1] = merge(ch[x][1], y), update(x); return x; }
}

void split(unsigned int u, unsigned int k, unsigned int &x, unsigned int &y) {
	if (!u) { x = y = 0; return; }
	if (k <= siz[ch[u][0]]) y = u, split(ch[y][0], k, x, ch[y][0]);
	else x = u, split(ch[x][1], k - siz[ch[u][0]] - 1, ch[x][1], y);
	update(u);
}

void main() {
	srand(20040725);
	for (unsigned int i = 0; i <= 10; i++)
		for (unsigned int j = 0; j <= 10; j++)
			if (i >= j) {
				C[i][j] = 1;
				for (unsigned int k = 1; k <= i; k++) C[i][j] *= k;
				for (unsigned int k = 1; k <= j; k++) C[i][j] /= k;
				for (unsigned int k = 1; k <= i - j; k++) C[i][j] /= k;
			}
	for (unsigned int i = 0; i <= 200000; i++) {
		pow[i][0] = 1;
		for (unsigned int k = 1; k <= 10; k++) pow[i][k] = pow[i][k - 1] * i;
	}
	read(n);
	for (unsigned int i = 1; i <= n; i++) read(a[i]), rt = merge(rt, newnode(a[i]));
	// dfs(rt), puts("");
	read(m);
	unsigned int v;
	for (unsigned int i = 1, c, l, r, k, x, y, z; i <= m; i++) {
		c = getchar(); while (!isupper(c)) c = getchar();
		if (c == 'I') {
			read(k), read(v), ++k, split(rt, k - 1, x, y);
			rt = merge(x, merge(newnode(v), y));
		} else if (c == 'D') {
			read(k), ++k, split(rt, k - 1, x, y), split(y, 1, y, z);
			rt = merge(x, z);
		} else if (c == 'R') {
			read(k), read(v), ++k, split(rt, k - 1, x, y), split(y, 1, y, z);
			val[y] = v, update(y), rt = merge(x, merge(y, z));
		} else {
			read(l), read(r), read(k), ++l, ++r, split(rt, l - 1, x, y), split(y, r - l + 1, y, z);
			print((unsigned int)ans[y][k], '\n'), rt = merge(x, merge(y, z));
		}
	}
}

} signed main() { return 0; }