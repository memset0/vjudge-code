// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.25 11:03:23
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
	x = 0; char c = getchar(); bool f = 0;
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 2e6 + 10;
ll ans;
char s[N];
std::vector<int> son[N];
int n, m, nod = 1, lst = 1;
int fa[N], siz[N], len[N], ch[N][26];

void append(char c) {
	int u = ++nod, f = lst; lst = u, len[u] = len[lst] + 1, siz[u] = 1;
	while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
	if (!f) { fa[u] = 1; return; }
	int s = ch[f][c];
	if (len[s] == len[f] + 1) { fa[u] = s; return; }
	int p = ++nod; fa[p] = fa[s], fa[s] = fa[u] = p, len[p] = len[f] + 1;
	for (register int i = 0; i < 26; i++) ch[p][i] = ch[s][i];
	while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
}

void dfs(int u) {
	for (auto v : son[u]) {
		dfs(v);
		siz[u] += siz[v];
	}
	if (siz[u] > 1) ans = std::max(ans, (ll)siz[u] * len[u]);
}

void main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	for (int i = 1; i <= n; i++) append(s[i]);
	for (int i = 2; i <= nod; i++) son[fa[i]].push_back(i);
	dfs(1);
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}