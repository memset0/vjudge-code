#include <bits/stdc++.h>
#define x1 kk15454
#define x2 kk13344
#define y1 kk42542
#define y2 kk15241
using namespace std;
const int maxn = 1010;
int m, n, k, l, d, x1, y1, x2, y2, mark[2][maxn], rank[2][maxn], a[maxn][maxn];
bool my_sort0(int a, int b) {
	return mark[0][a] > mark[0][b];
}
bool my_sort1(int a, int b) {
	return mark[1][a] > mark[1][b];
}
int main() {
	cin >> m >> n >> k >> l >> d;
	for (int i = 1; i <= d; i++) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 == x2) mark[1][min(y1, y2)]++;
		if (y1 == y2) mark[0][min(x1, x2)]++;
	}
	for (int i = 1; i <= m; i++) rank[0][i] = i;
	for (int i = 1; i <= n; i++) rank[1][i] = i;
	sort(rank[0] + 1, rank[0] + 1 + m, my_sort0);
	sort(rank[1] + 1, rank[1] + 1 + n, my_sort1);
	for (int i = 1; i <= k; i++) {
		printf("%d", rank[0][i]);
		if (i != k) printf(" ");
	}
	puts("");
	for (int i = 1; i <= l; i++) {
		printf("%d", rank[1][i]);
		if (i != l) printf(" ");
	}
	return 0;
}