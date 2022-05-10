#include <bits/stdc++.h>
using namespace std;
const int maxn = 360;
int n, ans, f[maxn][2];
char color, a[maxn], c[maxn][2];
int main() {
	scanf("%d%s", &n, a + 1);
	for (int i = 1; i <= n; i++) {
		color = 'w';
		for (int j = i; j >= 1; j--)
			if (color == 'w') {
				f[i][0]++;
				color = a[j];
			} else if (color == a[j] || a[j] == 'w') {
				f[i][0]++;
			} else {
				break;
			}
		for (int j = n; j > i; j--)
			if (color == 'w') {
				f[i][0]++;
				color = a[j];
			} else if (color == a[j] || a[j] == 'w') {
				f[i][0]++;
			} else {
				break;
			}
		c[i][0] = color;
		color = 'w';
		for (int j = i; j <= n; j++)
			if (color == 'w') {
				f[i][1]++;
				color = a[j];
			} else if (color == a[j] || a[j] == 'w') {
				f[i][1]++;
			} else {
				break;
			}
		for (int j = 1; j < i; j++)
			if (color == 'w') {
				f[i][1]++;
				color = a[j];
			} else if (color == a[j] || a[j] == 'w') {
				f[i][1]++;
			} else {
				break;
			}
		c[i][1] = color;
	}
	for (int i = 1; i < n; i++)
		ans = max(ans, f[i][0] + f[i + 1][1]);
	for (int i = 1; i <= n; i++) {
		// printf("%d %d")
	}
	printf("%d\n", ans - 2);
	return 0;
}