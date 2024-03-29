#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
const int mov[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
int n, m, ui, uj, a[maxn][maxn], f[maxn][maxn];
void DFS(int i, int j, int k) {
	if (k <= f[i][j]) return ;
	else f[i][j] = k;
	// printf(">>> i = %d j = %d k = %d\n", i, j, k);
	for (int t = 0; t < 4; t++) {
		ui = i + mov[t][0];
		uj = j + mov[t][1];
		if (ui < 1 || uj < 1 || ui > n || uj > m) continue;
		if (a[i][j] > a[ui][uj]) {
			DFS(ui, uj, k + 1);
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			DFS(i, j, 1);
	int ans = -1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (f[i][j] > ans) ans = f[i][j];
	printf("%d\n", ans);
	return 0;
}