#include <bits/stdc++.h>
using namespace std;
int t, n, m, h[101][101], ans, f[101][101];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int dfs(int x, int y)
{
	if (f[x][y]) return f[x][y];
	int t=1;
	for (int i = 0; i < 4; i++) {
		int vx = x + dx[i], vy = y + dy[i];
		if (vx >= 1 && vx <= n && vy >= 1 && vy <= m && h[x][y] < h[vx][vy])
			t = max(dfs(vx, vy) + 1, t);
	}
	return f[x][y] = t;
}
int main()
{
	read(n);read(m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			t=dfs(i,j);
			f[i][j]=t;
			ans=max(f[i][j],ans);
		}
	printf("%d\n", ans);
	return 0;
}