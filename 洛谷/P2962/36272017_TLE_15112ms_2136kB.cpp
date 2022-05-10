#include <bits/stdc++.h>
#define isnum(c) ('0' <= c && c <= '9')
#define read(x) do {\
	R::c = getchar(); R::m = 0; x = 0;\
	while (!isnum(R::c) && R::c != '-') R::c = getchar();\
	if (R::c == '-') R::c = getchar(), R::m = 1;\
	while (isnum(R::c)) x = x * 10 + R::c - '0', R::c = getchar();\
	if (R::m) x = -x;\
} while(false)
namespace R { char c; bool m; }
using namespace std;

const int maxn = 40;
int n, m, ans = -1, l, r, tx, ty, a[maxn];
long long check[maxn], FULL_STEP;
bool vis[maxn], G[maxn][maxn];

void DFS(long long pin, int step) {
//	cout << pin << " " << step << endl;
	if (step >= ans && ans != -1) return ;
	if (pin == FULL_STEP) {
		ans = step;
		return ;
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i]) {
			vis[i] = 1;
			DFS(pin ^ a[i], step + 1);
			vis[i] = 0;
		}
}

int main() {
	
	
	read(n);
	read(m);
	for (int i = 1; i <= n; i++)
		G[i][i] = 1;
	for (int i = 1; i <= m; i++) {
		read(tx);
		read(ty);
//		cout << tx << " " << ty << endl;
		G[tx][ty] = 1;
		G[ty][tx] = 1;
	}
	
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= n; j++)
//			cout << G[i][j];
//		puts("");
//	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = n; j > 0; j--)
			if (G[i][j]) a[i] = a[i] << 1 | 1;
			else a[i] = a[i] << 1;
	}
	FULL_STEP = check[1] = 1;
	for (int i = 2; i <= n; i++) {
		FULL_STEP = FULL_STEP << 1 | 1;
		check[i] = (check[i - 1] << 1);
	}
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= n; j++)
//			if (check[j] & a[i]) cout << 1;
//			else cout << 0;
//		cout << endl;
//	}
	
	DFS(0, 0);
	printf("%d\n", ans);
	
	return 0;
}