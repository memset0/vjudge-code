#include <bits/stdc++.h>
#define il inline 
using namespace std;

int mrk; char chr;
il void _R(int &x) {
	x = 0, chr = getchar(), mrk = 1;
	while (!('0' <= chr && chr <= '9') && chr != '-') chr = getchar();
	if (chr == '-') mrk = -1, chr = getchar();
	while ('0' <= chr && chr <= '9') x = x * 10 + chr - '0', chr = getchar();
	x *= mrk;
}

const int maxn = 32, nxt[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, m, p, ans, tx, ty, ex, ey, sx, sy, a[maxn][maxn], vis[maxn][maxn][maxn][maxn];
struct Node {
	short ex, ey, sx, sy, step;
} q[10000000], u, v;

int i, j, l, r, k;

int main() {
//	freopen("puzzle.in", "r", stdin);
//	freopen("puzzle.out", "w", stdout);
//	cout << -1 << endl;
	_R(n), _R(m), _R(p);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j)
			_R(a[i][j]);
	for (i = 1; i <= p; ++i) {
		_R(ex), _R(ey), _R(sx), _R(sy), _R(tx), _R(ty);
		/*if (a[tx + 1][ty] + a[tx][ty + 1] + a[tx - 1][ty] + a[tx][ty - 1] <= 1) ans = -1;
		else */if (tx == sx && ty == sy) ans = 0;
		else {
//			cout << "!";
			ans = 0, l = r = vis[ex][ey][sx][sy] = 1;
			q[1] = {ex, ey, sx, sy, 1};
			while (l <= r && !ans) {
//				cout << l << " ";
				u = q[l++];
//				cout << u.ex << " " << u.ey << " " << u.sx << " " << u.sy << " " << vis[v.ex][v.ey][v.sx][v.sy] << endl;
				for (j = 0; j < 4; j++) {
					v.ex = u.ex + nxt[j][0];
					v.ey = u.ey + nxt[j][1];
					v.step = u.step + 1;
					if (v.ex < 1 || v.ey < 1 || v.ex > n || v.ey > m || !a[v.ex][v.ey]) continue;
					if (v.ex == u.sx && v.ey == u.sy) v.sx = u.ex, v.sy = u.ey;
					else v.sx = u.sx, v.sy = u.sy;
					if (vis[v.ex][v.ey][v.sx][v.sy]) continue;
//					cout << vis[v.ex][v.ey][v.sx][v.sy];
					if (v.sx == tx && v.sy == ty) {
						ans = v.step;
						break;
					}
					vis[v.ex][v.ey][v.sx][v.sy] = 1;
					q[++r] = v;
				}
			}
			ans--;
		}
		printf("%d\n", ans);
	}
	return 0;
}