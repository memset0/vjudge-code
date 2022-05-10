#include <bits/stdc++.h>
using namespace std;
const int maxn = 410;
const int maxl = maxn * maxn * 50;
const int mov[8][2] {{1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-1, -2}, {-2, -1}};
int n, m, l, r, f[maxn][maxn];
struct Str{
	int x, y, i;
} q[maxl + 10], u, v;
int main() {
	memset(f, -1, sizeof(f));
	cin >> n >> m >> q[1].x >> q[1].y;
	q[1].i = 0, l = r = 1;
	while (l <= r) {
		u = q[l % maxl], l++;
		f[u.x][u.y] = u.i;
		for (int i = 0; i < 8; i++) {
			v.x = u.x + mov[i][0];
			v.y = u.y + mov[i][1];
			v.i = u.i + 1;
			if (v.x < 1 || v.y < 1 || v.x > n || v.y > m)
				continue;
			if (f[v.x][v.y] == -1) {
				r++;
				q[(r % maxl)] = v;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			cout << setiosflags(ios :: left) << setw(5) << f[i][j];
		puts("");
	}
	return 0;
}