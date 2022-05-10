#include <bits/stdc++.h> 
using namespace std;
const int maxn = 10010;
const int maxm = 500010;
int n, m, s, a[maxn][maxn], h[maxn], q[maxm];
int main() {
	memset(h, -1, sizeof(h));
	memset(a, -1, sizeof(a));
	int x, y, z;
	cin >> n >> m >> s;
	while (m--) {
		scanf("%d%d%d", &x, &y, &z);
		a[x][y] = z;
	}
	int l = 1, r = 1, u;
	q[r] = s, h[s] = 0;
	while (l <= r) {
		u = q[l++];
		for (int v = 1; v <= n; v++)
			if ((h[v] > h[u] + a[u][v] || h[v] == -1) && a[u][v] != -1) {
				h[v] = h[u] + a[u][v];
				q[++r] = v;
			}
	}
	for (int i = 1; i <= n; i++)
		if (h[i] == -1)	printf("2147483647 ");
		else printf("%d ", h[i]);
	puts("");
	return 0;
}