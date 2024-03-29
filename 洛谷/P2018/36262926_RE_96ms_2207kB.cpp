// ==============================
//  author: memset0
//  website: https://memset0.cn
//  date: 2018.08.06 18:51:21
// ==============================
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int read() {
	int x = 0; char c = getchar(); bool m = 0;
	while (!isdigit(c) && c != '-') c = getchar();
	if (c == '-') c = getchar(), m = 1;
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (m) return -x; else return x;
}

const int maxn = 1010;
int n, f[maxn], ans[maxn];
int tot = 2, hed[maxn], nxt[maxn << 1], to[maxn << 1];

void add_edge(int u, int v) {
	// printf("ADD EDGE %d %d\n", u, v);
	nxt[tot] = hed[u];
	to[tot] = v;
	hed[u] = tot++;
	nxt[tot] = hed[v];
	to[tot] = u;
	hed[v] = tot++;
}

void dfs(int u, int father) {
	// printf(">>> %d <= %d\n", u, father);
	set < int > s;
	s.insert(0);
	for (int i = hed[u]; i; i = nxt[i])
		if (to[i] != father) {
			dfs(to[i], u);
			while (s.count(f[to[i]])) f[to[i]]++;
			s.insert(f[to[i]]);
		}
	f[u] = (*--s.end()) + 1;
}

int main() {
	n = read();
	for (int i = 2; i <= n; i++)
		add_edge(i, read());
	for (int i = 1; i <= n; i++) {
		dfs(i, 0);
		ans[i] = f[i];
		// for (int i = 1; i <= n; i++)
		// 	printf("%d ", f[i]);
		// puts("");
	}
	// for (int i = 1; i <= n; i++)
	// 	printf("%d ", ans[i]);
	// puts("");
	int umin = ans[1];
	for (int i = 2; i <= n; i++)
		umin = min(umin, ans[i]);
	printf("%d\n", umin);
	for (int i = 1; i <= n; i++)
		if (umin == ans[i])
			printf("%d ", i);
	puts("");
	return 0;
}