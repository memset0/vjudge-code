// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.07 08:46:27
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

const int N = 3e4 + 10, M = 2e6 + 10;
int n, m, x, tot;
int cnt[M], dis[M];
char a[N];
bool vis[M], found[M];

struct node {
	int ch[2], fail;
	bool tag;
} e[M];

void insert(char *a) {
	int len = strlen(a), p = 1;
	for (int i = 0, x; i < len; i++) {
		x = a[i] == '0' ? 0 : 1;
		if (!e[p].ch[x]) e[p].ch[x] = ++tot;
		p = e[p].ch[x];
	}
	e[p].tag = 1;
}

void build_fail() {
	std::queue <int> q; int p, t;
	if (e[1].ch[0]) q.push(e[1].ch[0]), e[e[1].ch[0]].fail = 1;
	if (e[1].ch[1]) q.push(e[1].ch[1]), e[e[1].ch[1]].fail = 1;
	while (q.size()) {
		p = q.front(), q.pop();
		for (int i = 0; i < 2; i++)
			if (e[p].ch[i]) {
				q.push(e[p].ch[i]);
				t = e[p].fail;
				while (t != 1 && !e[t].ch[i]) t = e[t].fail;
				if (!e[t].ch[i]) e[e[t].ch[i]].fail = 1;
				else {
					e[e[p].ch[i]].fail = e[t].ch[i];
					e[e[p].ch[i]].tag |= e[e[t].ch[i]].tag;
				}
			} else e[p].ch[i] = e[e[p].fail].ch[i];
	}
}

void dfs(int u) {
	if (!u) return;
	printf("%d : ch %d %d\n", u, e[u].ch[0], e[u].ch[1]);
	for (int i = 0; i < 2; i++)	dfs(e[u].ch[i]);
}

void solve(int u) {
	vis[u] = 1;
	for (int i = 0; i < 2; i++) {
		if (!e[u].ch[i]) continue;
		if (vis[e[u].ch[i]]) {
			puts("TAK"), exit(0);
		} else if (!e[e[u].ch[i]].tag && !found[e[u].ch[i]]) {
			found[e[u].ch[i]] = 1;
			solve(e[u].ch[i]);
		}
	}
	vis[u] = 0;
}

void main() {
	read(n), tot = 1;
	for (int i = 1; i <= n; i++) scanf("%s", a), insert(a);
	build_fail();
	// for (int i = 1; i <= tot; i++)
	// 	printf("%d %d %d\n", e[i].ch[0], e[i].ch[1], e[i].fail);
	solve(1), puts("NIE");
}

} signed main() { return ringo::main(), 0; }