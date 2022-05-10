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
int n, m, lim, ans, l, r, tx, ty;
long long a[maxn], check[maxn], FULL_STACK;
bool vis[maxn], G[maxn][maxn];
map < long long, int > Map;
map < long long, int > ::iterator it;

void reader() {
	
	
	read(n);
	read(m);
	for (int i = 1; i <= n; i++)
		G[i][i] = 1;
	for (int i = 1; i <= m; i++) {
		read(tx);
		read(ty);
		G[tx][ty] = 1;
		G[ty][tx] = 1;
	}
	
}

void printer(long long x) {
	
	for (int i = 1; i <= n; i++)
		if (check[i] & x)
			putchar('1');
		else 
			putchar('0');
	printf("(%lld)", x);
	putchar('\n');
	
}

void DFS(long long pin, int step) {
	
	Map[pin] = step;
//	printf(">> STEP = %d | PIN = ", step);
//	printer(pin); 
	if (pin == FULL_STACK) {
		printf("%d\n", step);
		exit(0);
	}
	if (step <= lim) {
		for (int i = 1; i <= n; i++)
			if (!vis[i]) {
				vis[i] = 1;
				DFS(pin ^ a[i], step + 1);
				vis[i] = 0;
			}
	}
	
}

int main() {
	
	reader();
	
	for (int i = 1; i <= n; i++) {
		for (int j = n; j > 0; j--)
			if (G[i][j]) a[i] = a[i] << 1 | 1;
			else a[i] = a[i] << 1;
	}
	FULL_STACK = check[1] = 1;
	for (int i = 2; i <= n; i++) {
		FULL_STACK = FULL_STACK << 1 | 1;
		check[i] = (check[i - 1] << 1);
	}
	
	lim = (n + 1) >> 2;
	DFS(0, 0);
	
	ans = n;
//	for (it = Map.begin(); it != Map.end(); it++) { 
//		printf("|> ADDRESS = %d | STEP = %d | PIN = ", &it, it -> second);
//		printer(it -> first);
//	}
	for (it = Map.begin(); it != Map.end(); ++it) {
		if (Map.find((it -> first) ^ FULL_STACK) != Map.end()) {
			ans = min(ans, (it -> second) + Map[(it -> first) ^ FULL_STACK]);
//			printf("=== %d %d ===\n", it -> second, Map[(it -> first) ^ FULL_STACK]);
//			printer(it -> first);
//			printer((it -> first) ^ FULL_STACK);
		}
	}
//	for (it = Map.begin(); it != Map.end(); it++) { 
//		printf("|> ADDRESS = %d | STEP = %d | PIN = ", &it, it -> second);
//		printer(it -> first);
//	}
			
	printf("%d\n", ans);
	
	return 0;
}