// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.18 15:14:17
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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

const int N = 1e6 + 2e5 + 10, M = N * 30;
int Q, L, R, ans, cnt, lenS, lenT, c_dfn;
int rt[N], lim[N], bln[N], dfn[N], siz[N], sum[M], lc[M], rc[M];
char S[N], T[N];

struct SAM {
	int lst, nod, c_len, fa[N], len[N], end[N], key[N], ch[N][26];
	std::vector <int> son[N];
	void append(int c) {
		// printf("append %d\n", c);
		int u = ++nod, f = lst; end[u] = len[u] = key[u] = ++c_len, lst = u;
		while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
		if (!f) { fa[u] = 1; return; }
		int s = ch[f][c];
		if (len[s] == len[f] + 1) { fa[u] = s; return; }
		int p = ++nod; end[p] = end[s], fa[p] = fa[s], len[p] = len[f] + 1, fa[s] = fa[u] = p;
		for (int i = 0; i < 26; i++) ch[p][i] = ch[s][i];
		while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
	}
	void build(char *s) {
		lst = nod = 1; int len = strlen(s + 1);
		for (int i = 1; i <= len; i++) append(s[i] - 'a');
		for (int i = 2; i <= nod; i++) son[fa[i]].push_back(i);
	}
	void clear() {
		c_len = 0;
		for (int i = 1; i <= nod; i++) {
			fa[i] = len[i] = end[i] = key[i] = 0;
			for (int j = 0; j < 26; j++) ch[i][j] = 0;
		}
	}
	void print() {
		for (int i = 1; i <= nod; i++) {
			printf("i=%d fa=%d len=%d end=%d : ", i, fa[i], len[i], end[i]);
			for (int j = 0; j < 26; j++) ringo::print(ch[i][j], " \n"[j == 25]);
		}
	}
} samS, samT;

void build(int &u, int l, int r) {
	u = ++cnt;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(lc[u], l, mid);
	build(rc[u], mid + 1, r);
}

void modify(int &u, int v, int k, int l, int r) {
	u = ++cnt, lc[u] = lc[v], rc[u] = rc[v], sum[u] = sum[v];
	if (l == r) { ++sum[u]; return; }
	int mid = (l + r) >> 1;
	if (k <= mid) modify(lc[u], lc[v], k, l, mid);
	else modify(rc[u], rc[v], k, mid + 1, r);
	sum[u] = sum[lc[u]] + sum[rc[u]];
}

int query(int u, int v, int ql, int qr, int l, int r) {
	// printf("query %d %d %d %d %d %d | %d\n", u, v, ql, qr, l, r, sum[v] - sum[u]);
	if (ql > qr) return 0;
	if (l == ql && r == qr) return sum[v] - sum[u];
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(lc[u], lc[v], ql, qr, l, mid);
	if (ql > mid) return query(rc[u], rc[v], ql, qr, mid + 1, r);
	return query(lc[u], lc[v], ql, mid, l, mid) + query(rc[u], rc[v], mid + 1, qr, mid + 1, r);
}

void dfs(int u) {
	dfn[u] = ++c_dfn, bln[dfn[u]] = samS.key[u], siz[u] = 1;
	for (auto v : samS.son[u])
		dfs(v), siz[u] += siz[v];
}

void main() {
	scanf("%s", S + 1), lenS = strlen(S + 1), read(Q);
	samS.build(S), dfs(1), build(rt[0], 1, lenS);
	for (int i = 1; i <= samS.nod; i++)
		if (bln[i]) {
			// printf("insert %d => rt[%d]\n", bln[i], i);
			modify(rt[i], rt[i - 1], bln[i], 1, lenS);
		} else rt[i] = rt[i - 1];
	// samS.print();
	for (int i = 1; i <= Q; i++) {
		scanf("%s", T + 1), lenT = strlen(T + 1);
		ans = 0, samT.build(T), read(L), read(R);
		for (int i = 1, u = 1, c; c = T[i] - 'a', i <= lenT; i++) {
			debug("========================================\n");
			lim[i] = lim[i - 1];
			while (u) {
				debug("> %d[%d] : %d %d\n", u, samS.end[u], samS.ch[u][c], lim[i]);
				if (!samS.ch[u][c]) { u = samS.fa[u], lim[i] = std::min(lim[i], samS.len[u]); continue; }
				int from = u;
				u = samS.ch[u][c], ++lim[i];
				debug("u=%d from=%d lim=%d | %d %d | %d %d | %d %d\n", u, from, lim[i],
					dfn[u], dfn[u] + siz[u] - 1, rt[dfn[u] - 1], rt[dfn[u] + siz[u] - 1], L + lim[i] - 1, R);
				if (query(rt[dfn[u] - 1], rt[dfn[u] + siz[u] - 1], L + lim[i] - 1, R, 1, lenS)) break;
				u = samS.fa[from], lim[i] = std::min(lim[i] - 1, samS.len[u]);
			}
			if (!u) u = 1, lim[i] = 0;
			debug(">>> %d | %d %d\n", i, u, lim[i]);
		}
		for (int i = 2; i <= samT.nod; i++) {
			debug("=> i=%d lim=%d val=%d\n", i, lim[samT.end[i]], samT.len[i] - lim[samT.end[i]]);
			ans += std::max(0ll, std::min(samT.len[i] - samT.len[samT.fa[i]], samT.len[i] - lim[samT.end[i]]));
		}
		print(ans, '\n');
		samT.clear();
	}
}
} signed main() { return ringo::main(), 0; }