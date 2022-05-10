// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 15;

int n, m, u, v, w, sum, cnt, ans = -1;
int G[maxn][maxn];
int dep[maxn];
bool vis[maxn];

void dfs(int cur_u = 1, int cur_v = 1) {
//	printf("dfs %d %d\n", cur_u, cur_v);
	if (cnt == n) {
//		for (int i = 1; i <= n; i++)
//			printf("%d ", dep[i]);
//		puts("");
		if (sum < ans || ans == -1)
			ans = sum;
		return;
	}
	bool flag = 0;
	for (int u = cur_u; u <= n; u++)
		if (vis[u]) {
			for (int v = cur_v; v <= n; v++)
				if (!vis[v] && ~G[u][v]) {
					cnt++, sum += G[u][v] * (dep[u] + 1);
					vis[v] = 1, dep[v] = dep[u] + 1;
					dfs(u, v + 1);
					cnt--, sum -= G[u][v] * (dep[u] + 1);
					vis[v] = 0, dep[v] = 0;
					flag = 1;
				}
			cur_v = 1;
		}
	if (!flag)
		dfs(1, 1);
}

int main() {
//	freopen("INPUT", "r", stdin);
	memset(G, -1, sizeof(G));

	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		u = read(), v = read(), w = read();
		G[u][v] = G[v][u] = ~G[u][v] && G[u][v] < w ? G[u][v] : w;
	}
	
	for (int i = 1; i <= n; i++) {
		vis[i] = 1, cnt = 1, sum = 0, dep[i] = 0;
		dfs();
		vis[i] = 0, cnt = 0, sum = 0, dep[i] = 0;
//		puts("");
	}
	printf("%d\n", ans);

	return 0;
}