// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.26 21:22:47
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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

const int N = 1e6 + 10;
int n; char s[N];

struct SAM {
	static const int M = 2e6 + 10;
	int lst, nod, fa[M], len[M], siz[M], ch[M][26];
	ll ans; std::vector <int> son[M];
	SAM () { lst = nod = 1; }
	void append(int c) {
		int u = ++nod, f = lst; lst = u, len[u] = len[f] + 1, siz[u] = 1;
		while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
		if (!f) { fa[u] = 1; return; }
		int s = ch[f][c];
		if (len[s] == len[f] + 1) { fa[u] = f; return; }
		int p = ++nod; fa[p] = fa[s], fa[u] = fa[s] = p, len[p] = len[s];
		for (int i = 0; i < 26; i++) ch[p][i] = ch[s][i];
		while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
	}
	void dfs(int u) {
		for (auto v : son[u]) dfs(v), siz[u] += siz[v];
		if (siz[u] != 1) ans = std::max(ans, (ll)siz[u] * len[u]);
	}
	void build(int n, char *s) {
		for (int i = 1; i <= n; i++) append(s[i]);
		for (int i = 2; i <= nod; i++) son[fa[i]].push_back(i);
	}
	ll solve() { dfs(1); return ans; }
} sam;

void main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	sam.build(n, s);
	print(sam.solve(), '\n');
}

} signed main() { return ringo::main(), 0; }