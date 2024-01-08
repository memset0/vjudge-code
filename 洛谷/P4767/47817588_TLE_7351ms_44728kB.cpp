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

const int maxn = 3010, maxm = 310;
int n, m, a[maxn], dis[maxn][maxn], f[maxn][maxn];

int calc(int l, int r) {
	if (dis[l][r]) return dis[l][r];
	int mid = (l + r) >> 1, ans = 0;
	for (int i = l; i <= r; i++)
		ans += abs(a[i] - a[mid]);
	// printf(">>> %d => %d\n", l, r);
	// for (int i = l; i <= r; i++)
	// 	printf("%d ", a[i]);
	// puts("");
	// for (int i = l; i <= r; i++)
	// 	printf("%d ", abs(a[i] - a[mid]));
	// puts("");
	return dis[l][r] = ans;
}

int main() {
	// freopen("INPUT", "r", stdin);
	// freopen("OUTPUT", "w", stdout);

	memset(f, 0x3f, sizeof(f));

	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	sort(a + 1, a + n + 1);

	for (int i = 1; i <= n; i++)
		f[i][1] = calc(1, i);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 1; k < i; k++)
				f[i][j] = min(f[i][j], f[k][j - 1] + calc(k + 1, i));

	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= n; j++)
	// 		printf("%d ", dis[i][j]);
	// 	puts("");
	// }

	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= m; j++)
	// 		printf("%d ", f[i][j]);
	// 	puts("");
	// }

	printf("%d\n", f[n][m]);

	return 0;
}