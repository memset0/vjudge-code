// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.15 20:00:21
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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

const int N = 2e6 + 10;
int n, lst = 1, nod = 1, cnt;
int len[N], siz[N], fa[N], ch[N][26];
char s[N];
ll ans;
std::vector <int> G[N];

void insert(int c) {
	int f = lst, u = ++nod; len[lst = u] = ++cnt, siz[u] = 1;
	while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
	if (!f) return (void)(fa[u] = 1);
	int s = ch[f][c];
	if (len[s] == len[f] + 1) return (void)(fa[u] = s);
	int p = ++nod; fa[p] = fa[s], len[p] = len[f] + 1, fa[s] = fa[u] = p;
	for (register int i = 0; i < 26; i++) ch[p][i] = ch[s][i];
	while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
}

void dfs(int u) {
	for (auto v : G[u]) dfs(v), siz[u] += siz[v];
	// printf("dfs %d %d %d\n", u, siz[u], len[u]);
	if (siz[u] != 1) ans = std::max(ans, (ll)siz[u] * len[u]);
}

void main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	for (int i = 1; i <= n; i++) insert(s[i] - 'a');
	for (int i = 2; i <= nod; i++) G[fa[i]].push_back(i);
	dfs(1), print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }