// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.15 21:17:54
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
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

const int N = 1e6 + 10;
int n, t, k, lst = 1, cnt = 1, clen;
int siz[N], len[N], sum[N], fa[N], ch[N][26];
bool vis[N];
char s[N];
std::vector <int> G[N];

void insert(int c) {
	int f = lst, u = ++cnt; siz[lst = u] = 1, len[u] = ++clen;
	while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
	if (!f) return (void)(fa[u] = 1);
	int s = ch[f][c];
	if (len[s] == len[f] + 1) return (void)(fa[u] = s);
	int p = ++cnt; len[p] = len[f] + 1, fa[p] = fa[s], fa[s] = fa[u] = p;
	for (register int i = 0; i < 26; i++) ch[p][i] = ch[s][i];
	while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
}

void dfs(int u) {
	// siz[u] = 1;
	for (auto v : G[u]) dfs(v), siz[u] += siz[v];
	if (!t) siz[u] = 1;
}

void dfs2(int u) {
	sum[u] = siz[u], vis[u] = 1;
	for (int i = 0; i < 26; i++)
		if (ch[u][i]) {
			if (!vis[ch[u][i]]) dfs2(ch[u][i]);
			sum[u] += sum[ch[u][i]];
		}
}

void debug(int u) {
	for (register int i = 0; i < 26; i++)
		if (ch[u][i]) {
			printf("%d -> %d : %c\n", u, ch[u][i], 'a' + i);
			debug(ch[u][i]);
		}
}

void main() {
	scanf("%s", s + 1), n = strlen(s + 1), read(t), read(k);
	for (int i = 1; i <= n; i++) insert(s[i] - 'a');
	for (int i = 2; i <= cnt; i++) G[fa[i]].push_back(i);
	// for (int i = 1; i <= cnt; i++) print(fa[i], " \n"[i == cnt]);
	dfs(1), dfs2(1), siz[1] = 1;
	// for (int i = 1; i <= cnt; i++) print(sum[i], " \n"[i == cnt]);
	// debug(1);
	if (sum[1] < k) { puts("-1"); return; }
	for (int u = 1, p; k; u = ch[u][p]) {
		// printf(">> %d %d\n", u, k);
		// for (int i = 0; i < 26; i++)
		// 	if (sum[ch[u][i]])
		// 		printf("%d -> %d : %c : %d\n", u, ch[u][i], i + 'a', sum[ch[u][i]]);
		for (int i = 0; i < 26; i++)
			if (k > sum[ch[u][i]]) k -= sum[ch[u][i]];
			else { p = i; break; }
		putchar('a' + p), k -= siz[u];
	} putchar('\n');
}

} signed main() { return ringo::main(), 0; }
