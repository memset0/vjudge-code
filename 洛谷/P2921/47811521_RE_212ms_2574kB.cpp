#include <bits/stdc++.h>
#define isnum(c) ('0' <= c && c <= '9')
#define read(x) { \
		x = 0, rd::c = getchar(), rd::m = 0; \
		while (!isnum(rd::c) && rd::c != '-') rd::c = getchar(); \
		if (rd::c == '-') rd::m = 1, rd::c = getchar(); \
		while (isnum(rd::c)) x = x * 10 + rd::c - '0', rd::c = getchar(); \
		if (rd::m) x *= -1; \
	}
namespace rd {
	char c;
	bool m;
}
using namespace std;

const int maxn = 100010;
int n, g[maxn], vis[maxn];

int main() {

//	freopen("treat.in", "r", stdin);
//	freopen("treat.out", "w", stdout);

	read(n);
	for (int i = 1; i <= n; i++)
		read(g[i]);

	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		int ans = 0, u = i;
		while (!vis[u]) {
			vis[u] = 1;
			u = g[u];
			ans++;
		}
		printf("%d\n", ans);
	}

	return 0;
}