#include <bits/stdc++.h>
using namespace std;
const int maxn = 410;
const int mov[8][2] {{1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-1, -2}, {-2, -1}};
int n, m, l, r, f[maxn][maxn];
struct Str{
	int x, y, i;
} q[maxn * maxn * 10], u, v;
int main() {
	memset(f, -1, sizeof(f));
	cin >> n >> m >> q[1].x >> q[1].y;
	q[1].i = 0, l = r = 1;
	while (l <= r) {
		u = q[l++];
		if (u.x < 1 || u.y < 1 || u.x > n || u.y > m)
			continue;
		f[u.x][u.y] = u.i;
		for (int i = 0; i < 8; i++) {
			v.x = u.x + mov[i][0];
			v.y = u.y + mov[i][1];
			v.i = u.i + 1;
			if (f[v.x][v.y] == -1) q[++r] = v;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			printf("%5d", f[i][j]);
		puts("");
	}
	return 0;
}