// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.17 20:59:48
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

const int N = 1e6 + 10;
int n;
ll ans;
char s[N];

struct samStruct {
	int clen, cnt, lst;
	int fa[N], len[N], siz[N], ch[N][26];
	std::vector <int> G[N];
	inline samStruct() { cnt = lst = 1; }
	inline void insert(int c) {
		int f = lst, u = ++cnt; len[lst = u] = ++clen, siz[u] = 1;
		// printf("%d => %c\n", u, c + 'a');
		while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
		if (!f) return (void)(fa[u] = 1);
		int s = ch[f][c];
		if (len[s] == len[f] + 1) return (void)(fa[u] = s);
		int p = ++cnt; len[p] = len[f] + 1, fa[p] = fa[s], fa[s] = fa[u] = p;
		for (register int i = 0; i < 26; i++) ch[p][i] = ch[s][i];
		while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
	}
	void dfs(int u, int depth) {
		// printf(">> dfs %d %d\n", u, depth);
		ll sum = 0;
		for (int i = 0, v; i < G[u].size(); ++i)
			v = G[u][i], dfs(v, depth + len[v] - len[u]), sum += siz[v];
		// printf(">>>> %d %d : %d %d\n", u, depth, sum, siz[u]);
		siz[u] += sum;
		for (int i = 0, v; i < G[u].size(); ++i) {
			v = G[u][i], ans += (ll)siz[v] * (sum - siz[v]) * depth;
			// printf("=> %d : %d %d %d\n", v, siz[v], sum - siz[v], depth);
		}
	}
	inline void solve() {
		for (int i = 2; i <= cnt; i++) G[fa[i]].push_back(i);
		// for (int i = 1; i <= cnt; i++) print(fa[i], " \n"[i == cnt]);
		// for (int i = 1; i <= cnt; i++) printf("%d %d\n", i, fa[i]);
		dfs(1, 0);
	}
} sam;

void main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	for (int i = n; i >= 1; i--) sam.insert(s[i] - 'a');
	sam.solve(); ans = ((ll)n * (n - 1) * (n + 1) >> 1) - ans;
	print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }