#include <bits/stdc++.h>
using namespace std;
const int maxn = 1 << 27;
int n, j, a[maxn];
int dfs(int u) {
	printf("%c", a[u]);
	if ('a' <= a[u * 2] && a[u * 2] <= 'z')
		dfs(u * 2);
	if ('a' <= a[u * 2 + 1] && a[u * 2 + 1] <= 'z')
		dfs(u * 2 + 1);
}
int main() {
	scanf("%d%*c", &n);
	int len = 1;
	char x, y, z;
	for (int i = 1; i <= n; i++) {
		scanf("%c%c%c%*c", &x, &y, &z);
		if (i == 1) a[1] = x, j = 1;
		else 
			for (int k = 1; k <= len; k++)
				if (a[k] == x) j = k;
		a[2 * j] = y;
		a[2 * j + 1] = z;
		len = max(len, 2 * j + 1);
	}
	dfs(1);
	puts("");
//	for (int i = 1; i <= len; i++) 
//		printf("%c", a[i]);
	return 0;
}