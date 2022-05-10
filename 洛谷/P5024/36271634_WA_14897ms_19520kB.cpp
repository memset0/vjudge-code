#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

void openFile() { freopen("defense.in", "r", stdin); freopen("defense.out", "w", stdout); }
void closeFile() { fclose(stdin); fclose(stdout); }

inline int read() {
	char c = getchar(); int n = 0;
	while (c < '0' || c > '9') { c = getchar(); }
	while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
	return n;
}
inline char readLetter() {
	char c = getchar();
	while (c < 'A' || c > 'Z') { c = getchar(); }
	return c;
}

const int maxN = 200005;

typedef long long lol;

int n, m, s, t, x, y, val[maxN], fth[maxN];
lol ans, f[2][maxN], g[2][maxN];
bool used[maxN];
char opt;

struct List {
	int len, fst[maxN], nxt[maxN << 1], v[maxN << 1];
	
	List() { memset(fst, -1, sizeof(fst)); len = 0; }
	inline void insert(int u, int vv) { v[len] = vv; nxt[len] = fst[u]; fst[u] = len++; }
	inline void connect(int u, int vv) { insert(u, vv); insert(vv, u); }
} ls;

void dfs1(int u, int fa) {
	g[0][u] = 0; g[1][u] = val[u]; fth[u] = fa;
	for (int i = ls.fst[u]; ~i; i = ls.nxt[i]) {
		int v = ls.v[i];
		if (v != fa) {
			dfs1(v, u);
			g[0][u] += g[1][v]; g[1][u] += g[0][v] < g[1][v] ? g[0][v] : g[1][v];
		}
	}
}
void dfs2(int u) {
	if (!used[u]) { f[0][u] = g[0][u], f[1][u] = g[1][u]; return; }
	f[0][u] = 0; f[1][u] = val[u];
	for (int i = ls.fst[u]; ~i; i = ls.nxt[i]) {
		int v = ls.v[i];
		if (v != fth[u]) {
			dfs2(v);
			f[0][u] += f[1][v]; f[1][u] += f[0][v] < f[1][v] ? f[0][v] : f[1][v];
		}
	}
	if (f[0][u] > 1e12) { f[0][u] = 1e12; }
	if (f[1][u] > 1e12) { f[1][u] = 1e12; }
	if (s == u) { f[!x][u] = 1e12; }
	if (t == u) { f[!y][u] = 1e12; }
}

lol res[2][2];

inline lol min(lol xx, lol yy) { return xx < yy ? xx : yy; }

struct SegmentTree {
	lol c[2][2][maxN << 2];
	
	inline void pushUp(int u) {
		int ul = u << 1, ur = ul | 1;
		c[0][0][u] = min(min(c[0][1][ul] + c[0][0][ur], c[0][0][ul] + c[1][0][ur]), c[0][0][ul] + c[0][0][ur]);
		c[0][1][u] = min(min(c[0][1][ul] + c[0][1][ur], c[0][0][ul] + c[1][1][ur]), c[0][0][ul] + c[0][1][ur]);
		c[1][0][u] = min(min(c[1][1][ul] + c[0][0][ur], c[1][0][ul] + c[1][0][ur]), c[1][0][ul] + c[0][0][ur]);
		c[1][1][u] = min(min(c[1][1][ul] + c[0][1][ur], c[1][0][ul] + c[1][1][ur]), c[1][0][ul] + c[0][1][ur]);
	}
	void build(int u, int l, int r) {
		if (l == r) { c[1][1][u] = val[l]; c[0][0][u] = c[0][1][u] = c[1][0][u] = 1e12; return; }
		int mid = l + r >> 1;
		build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r); pushUp(u);
	}
	void query(int u, int l, int r, int pl, int pr) {
		if (l == pl && r == pr) {
			res[0][0] = min(min(res[0][1] + c[0][0][u], res[0][0] + c[1][0][u]), res[0][0] + c[0][0][u]);
			res[0][1] = min(min(res[0][1] + c[0][1][u], res[0][0] + c[1][1][u]), res[0][0] + c[0][1][u]);
			res[1][0] = min(min(res[1][1] + c[0][0][u], res[1][0] + c[1][0][u]), res[1][0] + c[0][0][u]);
			res[1][1] = min(min(res[1][1] + c[0][1][u], res[1][0] + c[1][1][u]), res[1][0] + c[0][1][u]);
			return;
		}
		int mid = l + r >> 1;
		if (pr <= mid) { query(u << 1, l, mid, pl, pr); }
		else if (pl > mid) { query(u << 1 | 1, mid + 1, r, pl, pr); }
		else { query(u << 1, l, mid, pl, mid); query(u << 1 | 1, mid + 1, r, mid + 1, pr); }
	}
} tr;

inline lol query(int l, int r) {
	if (l > r) { return 0; }
	res[0][0] = 0; res[0][1] = res[1][0] = res[1][1] = 1e12;
	tr.query(1, 1, n, l, r);
	return min(min(res[0][0], res[0][1]), min(res[1][0], res[1][1]));
}

int main() {
	// openFile(); // 44 + ? pts.
	n = read(); m = read(); opt = readLetter(); read();
	for (int i = 1; i <= n; i++) { val[i] = read(); }
	if (n > 2000 && opt == 'A') {
		tr.build(1, 1, n);
		for (; m; m--) {
			s = read(); x = read(); t = read(); y = read();
			if (s > t) { s ^= t; t ^= s; s ^= t; x ^= y; y ^= x; x ^= y; }
			if (x == 1 && y == 1) { printf("%lld\n", val[s] + val[t] + query(1, s - 1) + query(s + 1, t - 1) + query(t + 1, n)); }
			else if (x == 0 && y == 1) {
				if (s + 1 == t) { printf("%lld\n", val[s - 1] + val[t] + query(1, s - 2) + query(t + 1, n)); }
				else { printf("%lld\n", val[s - 1] + val[s + 1] + val[t] + query(1, s - 2) + query(t + 1, n) + query(s + 2, t - 1)); }
			} else if (x == 1 && y == 0) {
				if (s + 1 == t) { printf("%lld\n", val[s] + val[t + 1] + query(1, s - 1) + query(t + 2, n)); }
				else { printf("%lld\n", val[s] + val[t - 1] + val[t + 1] + query(1, s - 1) + query(t + 2, n) + query(s + 1, t - 2)); }
			} else {
				if (s + 2 == t) { printf("%lld\n", val[s - 1] + val[s + 1] + val[t + 1] + query(1, s - 2) + query(t + 2, n)); }
				else if (s + 1 == t) { printf("%d\n", -1); }
				else { printf("%lld\n", val[s - 1] + val[s + 1] + val[t - 1] + val[t + 1] + query(1, s - 2) + query(t + 2, n) + query(s + 2, t - 2)); }
			}
		}
		closeFile();
		return 0;
	}
	for (int i = 2; i <= n; i++) { ls.connect(read(), read()); }
	dfs1(1, 0);
	for (; m; m--) {
		s = read(); x = read(); t = read(); y = read();
		if (s > t) { s ^= t; t ^= s; s ^= t; x ^= y; y ^= x; x ^= y; }
		for (int i = s; i; i = fth[i]) { used[i] = true; }
		for (int i = t; i; i = fth[i]) { used[i] = true; }
		dfs2(1);
		if (s == 1) { ans = f[x][1]; } else { ans = f[0][1] < f[1][1] ? f[0][1] : f[1][1]; }
		printf("%lld\n", ans > ((lol) 1e11) ? -1 : ans);
		for (int i = s; i; i = fth[i]) { used[i] = false; }
		for (int i = t; i; i = fth[i]) { used[i] = false; }
	}
	closeFile();
	return 0;
}
