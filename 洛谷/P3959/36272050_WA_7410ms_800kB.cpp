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
bool vis[maxn];

void dfs(int u, int dep) {
//	printf("dfs %d %d %d %d\n", u, dep, cnt, sum);
	if (cnt == n) {
		if (sum < ans || ans == -1)
			ans = sum;
		return;
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i] && ~G[u][i]) {
			vis[i] = 1;
			cnt++;
			sum += G[u][i] * dep;
			dfs(u, dep);
			dfs(i, dep + 1);
			vis[i] = 0;
			cnt--;
			sum -= G[u][i] * dep;
		}
}

int main() {
	memset(G, -1, sizeof(G));

	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		u = read(), v = read(), w = read();
		G[u][v] = G[v][u] = ~G[u][v] && G[u][v] < w ? G[u][v] : w;
	}
	
	for (int i = 1; i <= n; i++) {
		vis[i] = 1, cnt = 1, sum = 0;
		dfs(i, 1);
		vis[i] = 0, cnt = 0, sum = 0;
//		puts("");
	}
	printf("%d\n", ans);

	return 0;
}
