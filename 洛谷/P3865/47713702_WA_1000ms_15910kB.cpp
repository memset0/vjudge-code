#include <bits/stdc++.h>
using namespace std;

int read() {
	int x = 0; bool m = 0; char c = getchar();
	while (!isdigit(c) && c != '-') c = getchar();
	if (c == '-') m = 1, c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (m) return -x; else return x;
}

const int maxn = 1e5 + 10, maxm = 1e6 + 10;
int n, m, x, y, dep, log_2[maxn], a[maxn], f[maxn][17][2];

int main() {

	n = read(), m = read();
	for (int i = 0, u = 1; i <= 16 && u <= n; i++) {
		u <<= 1;
		for (int j = (u >> 1); j + 1 <= u && j <= n; j++)
			log_2[j] = i;
	}

	for (int i = 1; i <= n; i++)
		f[i][0][0] = f[i][0][1] = a[i] = read();
	for (int i = 1; i <= 16; i++)
		for (int j = 1; j <= n; j++) {
			f[j][i][0] = max(f[j][i - 1][0], f[j + 1][i - 1][0]);
			f[j][i][1] = max(f[j][i - 1][1], f[j - 1][i - 1][1]);
		}

	while (m--) {
		x = read(), y = read();
		dep = log_2[y - x + 1];
		// printf("%d %d : %d\n", x, y, dep);
		printf("%d\n", max(f[x][dep][0], f[y][dep][1]));
	}

	return 0;
}