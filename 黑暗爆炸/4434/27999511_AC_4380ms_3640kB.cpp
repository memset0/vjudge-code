// source: yhx
#include <bits/stdc++.h>
using std::cin;
using std::cout;

const int N = 540;

int r[N][N];

inline int min(const int x, const int y) {return x < y ? x : y;}
inline int max(const int x, const int y) {return x < y ? y : x;}
inline int sqr(int x) {return x * x;} 

int main() {
	int i, x, y, x1, y1, x2, y2, dx, dy, y_min, y_max, y_sup, n, q, U, D, D2, ans; double $;
	std::ios::sync_with_stdio(false), cin.tie(NULL);
	cin >> n;
	for (i = 0; i < n; ++i) cin >> x >> y >> $, r[x][y] = llround($ * 10);
	for (cin >> q; q; --q) {
		cin >> x1 >> y1 >> x2 >> y2, ans = 0;
		if (x1 > x2) std::swap(x1, x2), std::swap(y1, y2);
		if (x1 == x2) {
			if (y1 > y2) std::swap(y1, y2);
			for (y = y1; y <= y2; ++y) ans += !!r[x1][y];
		} else {
			dx = x2 - x1, dy = y2 - y1, U = dx * y1, D2 = dx * dx + dy * dy, D = sqrt(D2),
			std::tie(y_min, y_max) = std::minmax(y1, y2);
			for (x = x1; x <= x2; ++x, U += dy)
				for (y_sup = min((U + D) / dx, y_max), y = max((U - D + dx - 1) / dx, y_min); y <= y_sup; ++y)
					ans += r[x][y] && 100 * sqr((x1 - x) * (y2 - y) - (y1 - y) * (x2 - x)) <= sqr(r[x][y]) * D2;
		}
		cout << ans << '\n';
	}
	return 0;
}