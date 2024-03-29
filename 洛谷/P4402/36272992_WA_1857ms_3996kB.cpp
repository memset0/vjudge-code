// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i, l, r) for (int i = l; i <= r; ++i)
namespace ringo {

template < class T > il void read(T &x) {
	x = 0; rg char c = getc(); rg bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getc();
	while (isdigit(c)) x = x * 10 + c - '0', c = getc();
	if (f) x = -x;
}

template < class T > il void print(T x) {
	if (x < 0) putc('-'), x = -x;
	if (x > 9) print(x / 10);
	putc('0' + x % 10);
}

const int maxn = 1e5 + 10;
int n, m, x, y, z, t, rt, cnt;
int a[maxn], siz[maxn], rnd[maxn], val[maxn], min[maxn], way[maxn], ch[maxn][2];
bool rev[maxn];

void update(int u) {
	siz[u] = siz[ch[u][0]] + siz[ch[u][1]] + 1;
	min[u] = val[u], way[u] = 0;
	if (ch[u][0] && min[ch[u][0]] < min[u]) min[u] = min[ch[u][0]], way[u] = 1;
	if (ch[u][1] && min[ch[u][1]] < min[u]) min[u] = min[ch[u][1]], way[u] = 2;
}

void pushup(int u) {
	if (!u) return;
//	printf("pushup %d\n", u);
	rev[u] ^= 1;
	way[u] = way[u] ? 3 - way[u] : 0;
	std::swap(ch[u][0], ch[u][1]);
}

void pushdown(int u) {
	if (rev[u]) {
		pushup(ch[u][0]);
		pushup(ch[u][1]);
		rev[u] = 0;
	}
}

int build(int l, int r) {
	if (l > r) return 0;
	int u = ++cnt, mid = (l + r) >> 1;
	val[u] = a[mid], rnd[u] = rand();
	ch[u][0] = build(l, mid - 1);
	ch[u][1] = build(mid + 1, r);
	return update(u), u;
}

int locate(int u) {
	pushdown(u);
//	printf("locate %d : %d %d\n", u, val[u], way[u]);
	if (!way[u]) return siz[ch[u][0]] + 1;
	if (way[u] == 1) return locate(ch[u][0]);
	return siz[ch[u][0]] + 1 + locate(ch[u][1]);
}

void erase(int u) {
	pushdown(u);
	if (!ch[u][0]) val[u] = n + 1;
	else erase(ch[u][0]);
	update(u);
}

int merge(int x, int y) {
	if (!x || !y) return x | y;
	pushdown(x), pushdown(y);
	if (rnd[x] < rnd[y]) { ch[x][1] = merge(ch[x][1], y); return update(x), x; }
	else { ch[y][0] = merge(x, ch[y][0]); return update(y), y; }
}

void split(int u, int k, int &x, int &y) {
	if (!u) return (void)(x = y = 0);
	pushdown(u);
	if (k <= siz[ch[u][0]]) y = u, split(ch[y][0], k, x, ch[y][0]);
	else x = u, split(ch[x][1], k - siz[ch[u][0]] - 1, ch[x][1], y);
	update(u);
}

void dfs(int u) {
	pushdown(u);
	if (ch[u][0]) dfs(ch[u][0]);
 	print(val[u]), putc(' ');
//	printf("%d(%d : %d %d) ", val[u], way[u], siz[ch[u][0]], siz[ch[u][1]]);
	if (ch[u][1]) dfs(ch[u][1]);
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]);
	rt = build(1, n);
//	dfs(rt), putc('\n');
	for (int i = 1; i <= n; i++) {
		t = locate(rt);
		print(t), putc(i == n ? '\n' : ' ');
		split(rt, t, x, z), split(x, i - 1, x, y);
//		printf("> %d %d %d\n", x, y, z);
		pushup(y);
		erase(y);
//		dfs(x), putc('\n');
//		dfs(y), putc('\n');
//		dfs(z), putc('\n');
		rt = merge(x, merge(y, z));
//		dfs(rt), putc('\n');
//		printf(">>> %d : %d %d %d\n", t, x, y, z);
	}
}

} int main() { return ringo::main(), 0; }
